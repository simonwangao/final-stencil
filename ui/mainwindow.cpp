/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Databinding.h"
#include "Settings.h"
#include "SupportCanvas3D.h"
#include "scenegraph/SceneviewScene.h"
#include "camera/CamtransCamera.h"
#include <math.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Make sure the settings are loaded before the UI
    settings.loadSettingsOrDefaults();

    QGLFormat qglFormat;
    qglFormat.setVersion(4, 3);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(ui->centralWidget);
    m_canvas3D = new SupportCanvas3D(qglFormat, this);
    gridLayout->addWidget(m_canvas3D, 0, 1);

    // Restore the UI settings
    QSettings qtSettings("CS123", "CS123");
    restoreGeometry(qtSettings.value("geometry").toByteArray());
    restoreState(qtSettings.value("windowState").toByteArray());

    // Resize the window because the window is huge since all docks were visible.
    resize(1000, 600);

    // Bind the UI elements to their properties in the global Settings object, using binding
    // objects to simplify the code.  Each binding object connects to its UI elements and keeps
    // the UI and its setting in sync.

    QList<QAction*> actions;

#define SETUP_ACTION(dock, key) \
    actions.push_back(ui->dock->toggleViewAction()); \
    actions.back()->setShortcut(QKeySequence(key));

    SETUP_ACTION(,     "CTRL+1");

    ui->menuToolbars->addActions(actions);
#undef SETUP_ACTION

    dataBind();

    // Reset the contents of both canvas widgets (make a new 500x500 image for the 2D one)
    fileNew();

    // Make certain radio buttons switch to the 2D canvas when clicked.
    QList<QRadioButton*> a;
    a += ui->brushTypeLinear;

    foreach (QRadioButton *rb, a)
        connect(rb, SIGNAL(clicked()), this, SLOT(activateCanvas3D()));

    show();

}

MainWindow::~MainWindow()
{
    foreach (DataBinding *b, m_bindings)
        delete b;
    foreach (QButtonGroup *bg, m_buttonGroups)
        delete bg;
    delete ui;
}

void MainWindow::dataBind() {
    // Brush dock
#define BIND(b) { \
    DataBinding *_b = (b); \
    m_bindings.push_back(_b); \
    assert(connect(_b, SIGNAL(dataChanged()), this, SLOT(settingsChanged()))); \
}
    QButtonGroup *brushButtonGroup = new QButtonGroup;
    QButtonGroup *shapesButtonGroup = new QButtonGroup;
    QButtonGroup *filterButtonGroup = new QButtonGroup;
    m_buttonGroups.push_back(brushButtonGroup);
    m_buttonGroups.push_back(shapesButtonGroup);
    m_buttonGroups.push_back(filterButtonGroup);

    BIND(ChoiceBinding::bindRadioButtons(
            brushButtonGroup,
            NUM_BRUSH_TYPES,
            settings.brushType,
            ui->brushTypeConstant,
            ui->brushTypeLinear,
            ui->brushTypeQuadratic,
            ui->brushTypeSmudge,
            ui->brushTypeSpecial1,
            ui->brushTypeSpecial2))

    BIND(IntBinding::bindSliderAndTextbox(
        ui->brushRadiusSlider, ui->brushRadiusTextbox, settings.brushRadius, 0, 96))
    BIND(UCharBinding::bindSliderAndTextbox(
        ui->brushColorSliderRed, ui->brushColorTextboxRed, settings.brushColor.r, 0, 255))
    BIND(UCharBinding::bindSliderAndTextbox(
        ui->brushColorSliderGreen, ui->brushColorTextboxGreen, settings.brushColor.g, 0, 255))
    BIND(UCharBinding::bindSliderAndTextbox(
        ui->brushColorSliderBlue, ui->brushColorTextboxBlue, settings.brushColor.b, 0, 255))
    BIND(UCharBinding::bindSliderAndTextbox(
        ui->brushColorSliderAlpha, ui->brushColorTextboxAlpha, settings.brushColor.a, 0, 255))
    BIND(BoolBinding::bindCheckbox(ui->brushAlphaBlendingCheckbox, settings.fixAlphaBlending))


    // Camtrans dock
    BIND(BoolBinding::bindCheckbox(ui->cameraOrbitCheckbox, settings.useOrbitCamera))
    BIND(FloatBinding::bindDial(ui->transX, settings.cameraPosX, -2, 2, true))
    BIND(FloatBinding::bindDial(ui->transY, settings.cameraPosY, -2, 2, true))
    BIND(FloatBinding::bindDial(ui->transZ, settings.cameraPosZ, -2, 2, true))
    BIND(FloatBinding::bindDial(ui->rotU,   settings.cameraRotU, -20, 20, true))
    BIND(FloatBinding::bindDial(ui->rotV,   settings.cameraRotV, -20, 20, true))
    BIND(FloatBinding::bindDial(ui->rotW,   settings.cameraRotN, -180, 180, false))
    BIND(FloatBinding::bindSliderAndTextbox(
              ui->cameraFovSlider, ui->cameraFovTextbox, settings.cameraFov, 1, 179))
    BIND(FloatBinding::bindSliderAndTextbox(
              ui->cameraNearSlider, ui->cameraNearTextbox, settings.cameraNear, 0.1, 50))
    BIND(FloatBinding::bindSliderAndTextbox(
              ui->cameraFarSlider, ui->cameraFarTextbox, settings.cameraFar, 0.1, 50))
    initializeCamtransFrustum(); // always set the viewing frustum to reasonable settings when we start the program

    BIND(ChoiceBinding::bindTabs(ui->tabWidget, settings.currentTab))

#undef BIND

    // make sure the aspect ratio updates when m_canvas3D changes size
    connect(m_canvas3D, SIGNAL(aspectRatioChanged()), this, SLOT(updateAspectRatio()));
}

void MainWindow::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e); // allow the superclass to handle this for the most part...

    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // Save the settings before we quit
    settings.saveSettings();
    QSettings qtSettings("CS123", "CS123");
    qtSettings.setValue("geometry", saveGeometry());
    qtSettings.setValue("windowState", saveState());


    QMainWindow::closeEvent(event);
}

void MainWindow::updateAspectRatio() {
    // Update the aspect ratio text so the aspect ratio will be correct even if the
    // 3D canvas isn't visible (the 3D canvas isn't resized when it isn't visible)
    QSize activeTabSize = ui->centralWidget->size();
    float aspectRatio = static_cast<float>(activeTabSize.width()) / static_cast<float>(activeTabSize.height());
    ui->cameraAspectRatio->setText(QString("Aspect ratio: %1").arg(aspectRatio));
}


void MainWindow::settingsChanged() {
    m_canvas3D->settingsChanged();
}

void MainWindow::setAllEnabled(bool enabled) {
    QList<QWidget *> widgets;
    widgets += ui->brushDock;
    widgets += ui->camtransDock;

    QList<QAction *> actions;
    actions += ui->actionNew;
    actions += ui->actionOpen;
    actions += ui->actionSave;
    actions += ui->actionRevert;
    actions += ui->actionCopy3Dto2D;
    actions += ui->actionClear;
    actions += ui->actionQuit;

    foreach (QWidget *widget, widgets)
        widget->setEnabled(enabled);
    foreach (QAction *action, actions)
        action->setEnabled(enabled);
}

void MainWindow::setCameraAxisX() {
    m_canvas3D->setCameraAxisX();
}

void MainWindow::setCameraAxisY() {
    m_canvas3D->setCameraAxisY();
}

void MainWindow::setCameraAxisZ() {
    m_canvas3D->setCameraAxisZ();
}

void MainWindow::updateCameraTranslation() {
    m_canvas3D->updateCameraTranslation();
}

void MainWindow::updateCameraRotationN() {
    m_canvas3D->updateCameraRotationN();
}

void MainWindow::updateCameraRotationV() {
    m_canvas3D->updateCameraRotationV();
}

void MainWindow::updateCameraRotationU() {
    m_canvas3D->updateCameraRotationU();
}

void MainWindow::resetUpVector() {
    m_canvas3D->resetUpVector();
}

void MainWindow::resetSliders() {
    ui->cameraFovTextbox->setText(QString::number(55, 'f', 1));
    ui->cameraNearTextbox->setText(QString::number(.1, 'f', 1));
    ui->cameraFarTextbox->setText(QString::number(50, 'f', 1));
    QCoreApplication::processEvents();
    update();
}

void MainWindow::initializeCamtransFrustum() {
    ui->cameraFovTextbox->setText(QString::number(55, 'f', 1));
    ui->cameraNearTextbox->setText(QString::number(.1, 'f', 1));
    ui->cameraFarTextbox->setText(QString::number(50, 'f', 1));
    update();
}

void MainWindow::updateCameraClip() {
    m_canvas3D->updateCameraClip();
}

void MainWindow::updateCameraHeightAngle() {
    m_canvas3D->updateCameraHeightAngle();
}

void MainWindow::setCameraAxonometric() {
    m_canvas3D->setCameraAxonometric();
}
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include <QGLFormat>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
