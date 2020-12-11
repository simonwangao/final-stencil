﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Databinding.h"
#include "Settings.h"
#include "SupportCanvas3D.h"
#include "scenegraph/SceneviewScene.h"
#include "camera/CamtransCamera.h"
#include "L_System/turtle.h"
#include "shapes/drawer.h"
#include <math.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QAction>

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
    QGridLayout *gridLayout = new QGridLayout(ui->canvas3D);
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

    SETUP_ACTION(BurningTreeDock,     "CTRL+1");


    ui->BurningTreeDock->raise();
#undef SETUP_ACTION

    dataBind();

    ui->BurningTreeDock->show();
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

    // Burning dock
    BIND(IntBinding::bindSliderAndTextbox(ui->SizeControl, ui->SizeInput, settings.size, 0, 8))
    BIND(FloatBinding::bindSliderAndTextbox(ui->AngleControl, ui->AngleInput, settings.branchingAngle, 0, 90))
    BIND(FloatBinding::bindSliderAndTextbox(ui->LengthControl, ui->LenInput, settings.branchingLen, 0, 4))
    BIND(FloatBinding::bindSliderAndTextbox(ui->BranchWidthControl, ui->BranchInput,settings.branchWidth, 0, 1))
    BIND(BoolBinding::bindCheckbox(ui->RandomCactus, settings.randomCactus))
    BIND(BoolBinding::bindCheckbox(ui->BurningButton, settings.burnTree))

    // Camtrans dock
    BIND(FloatBinding::bindSliderAndTextbox(
              ui->cameraFovSlider_2, ui->cameraFovTextbox_2, settings.cameraFov, 1, 179))
    BIND(FloatBinding::bindSliderAndTextbox(
              ui->cameraNearSlider_2, ui->cameraNearTextbox_2, settings.cameraNear, 0.1, 50))
    BIND(FloatBinding::bindSliderAndTextbox(
              ui->cameraFarSlider_2, ui->cameraFarTextbox_2, settings.cameraFar, 0.1, 100))
    initializeCamtransFrustum(); // always set the viewing frustum to reasonable settings when we start the program


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
    ui->cameraAspectRatio_2->setText(QString("Aspect ratio: %1").arg(aspectRatio));
}


void MainWindow::settingsChanged() {
    m_canvas3D->settingsChanged();
}

void MainWindow::setAllEnabled(bool enabled) {
    QList<QWidget *> widgets;
    widgets += ui->BurningTreeDock;

    QList<QAction *> actions;

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
    ui->cameraFovTextbox_2->setText(QString::number(55, 'f', 1));
    ui->cameraNearTextbox_2->setText(QString::number(.1, 'f', 1));
    ui->cameraFarTextbox_2->setText(QString::number(50, 'f', 1));
    QCoreApplication::processEvents();
    update();
}

void MainWindow::initializeCamtransFrustum() {
    ui->cameraFovTextbox_2->setText(QString::number(55, 'f', 1));
    ui->cameraNearTextbox_2->setText(QString::number(.1, 'f', 1));
    ui->cameraFarTextbox_2->setText(QString::number(80, 'f', 1));
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
