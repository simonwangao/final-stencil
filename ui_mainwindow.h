/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *canvas3D;
    QDockWidget *BurningTreeDock;
    QWidget *burningDockContents;
    QCheckBox *BurningButton;
    QLabel *burningTreeLabel;
    QLabel *CactusControlsLabel;
    QSlider *SizeControl;
    QLabel *SizeLabel;
    QLabel *AngleLabel;
    QSlider *AngleControl;
    QLabel *LengthALabel;
    QSlider *LengthControl;
    QLabel *BranchWidthLabel;
    QSlider *BranchWidthControl;
    QCheckBox *RandomCactus;
    QLineEdit *SizeInput;
    QLineEdit *AngleInput;
    QLineEdit *LenInput;
    QLineEdit *BranchInput;
    QWidget *cameraDockEmptySpace_2;
    QLabel *label_2;
    QLabel *cameraAspectRatio_2;
    QWidget *cameraFrustum_2;
    QGridLayout *gridLayout_6;
    QLabel *cameraFovLabel_2;
    QLineEdit *cameraFovTextbox_2;
    QSlider *cameraFovSlider_2;
    QLabel *cameraNearLabel_2;
    QLineEdit *cameraNearTextbox_2;
    QLabel *cameraFarLabel_2;
    QLineEdit *cameraFarTextbox_2;
    QSlider *cameraNearSlider_2;
    QSlider *cameraFarSlider_2;
    QPushButton *resetSliders_2;
    QLabel *ParticlesLabel;
    QSlider *NumParticlesSlider;
    QLineEdit *NumParticlesInput;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 873);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        canvas3D = new QWidget(centralWidget);
        canvas3D->setObjectName(QString::fromUtf8("canvas3D"));

        horizontalLayout->addWidget(canvas3D);

        MainWindow->setCentralWidget(centralWidget);
        BurningTreeDock = new QDockWidget(MainWindow);
        BurningTreeDock->setObjectName(QString::fromUtf8("BurningTreeDock"));
        burningDockContents = new QWidget();
        burningDockContents->setObjectName(QString::fromUtf8("burningDockContents"));
        BurningButton = new QCheckBox(burningDockContents);
        BurningButton->setObjectName(QString::fromUtf8("BurningButton"));
        BurningButton->setGeometry(QRect(10, 270, 100, 20));
        burningTreeLabel = new QLabel(burningDockContents);
        burningTreeLabel->setObjectName(QString::fromUtf8("burningTreeLabel"));
        burningTreeLabel->setGeometry(QRect(10, 240, 211, 16));
        CactusControlsLabel = new QLabel(burningDockContents);
        CactusControlsLabel->setObjectName(QString::fromUtf8("CactusControlsLabel"));
        CactusControlsLabel->setGeometry(QRect(10, 10, 101, 16));
        SizeControl = new QSlider(burningDockContents);
        SizeControl->setObjectName(QString::fromUtf8("SizeControl"));
        SizeControl->setGeometry(QRect(110, 50, 160, 22));
        SizeControl->setOrientation(Qt::Horizontal);
        SizeLabel = new QLabel(burningDockContents);
        SizeLabel->setObjectName(QString::fromUtf8("SizeLabel"));
        SizeLabel->setGeometry(QRect(10, 50, 58, 16));
        AngleLabel = new QLabel(burningDockContents);
        AngleLabel->setObjectName(QString::fromUtf8("AngleLabel"));
        AngleLabel->setGeometry(QRect(10, 90, 101, 16));
        AngleControl = new QSlider(burningDockContents);
        AngleControl->setObjectName(QString::fromUtf8("AngleControl"));
        AngleControl->setGeometry(QRect(110, 90, 160, 22));
        AngleControl->setOrientation(Qt::Horizontal);
        LengthALabel = new QLabel(burningDockContents);
        LengthALabel->setObjectName(QString::fromUtf8("LengthALabel"));
        LengthALabel->setGeometry(QRect(10, 130, 91, 16));
        LengthControl = new QSlider(burningDockContents);
        LengthControl->setObjectName(QString::fromUtf8("LengthControl"));
        LengthControl->setGeometry(QRect(110, 130, 160, 22));
        LengthControl->setOrientation(Qt::Horizontal);
        BranchWidthLabel = new QLabel(burningDockContents);
        BranchWidthLabel->setObjectName(QString::fromUtf8("BranchWidthLabel"));
        BranchWidthLabel->setGeometry(QRect(10, 170, 91, 16));
        BranchWidthControl = new QSlider(burningDockContents);
        BranchWidthControl->setObjectName(QString::fromUtf8("BranchWidthControl"));
        BranchWidthControl->setGeometry(QRect(110, 170, 160, 22));
        BranchWidthControl->setOrientation(Qt::Horizontal);
        RandomCactus = new QCheckBox(burningDockContents);
        RandomCactus->setObjectName(QString::fromUtf8("RandomCactus"));
        RandomCactus->setGeometry(QRect(10, 200, 86, 20));
        SizeInput = new QLineEdit(burningDockContents);
        SizeInput->setObjectName(QString::fromUtf8("SizeInput"));
        SizeInput->setGeometry(QRect(270, 50, 61, 21));
        AngleInput = new QLineEdit(burningDockContents);
        AngleInput->setObjectName(QString::fromUtf8("AngleInput"));
        AngleInput->setGeometry(QRect(270, 90, 61, 21));
        LenInput = new QLineEdit(burningDockContents);
        LenInput->setObjectName(QString::fromUtf8("LenInput"));
        LenInput->setGeometry(QRect(270, 130, 61, 21));
        BranchInput = new QLineEdit(burningDockContents);
        BranchInput->setObjectName(QString::fromUtf8("BranchInput"));
        BranchInput->setGeometry(QRect(270, 170, 61, 21));
        cameraDockEmptySpace_2 = new QWidget(burningDockContents);
        cameraDockEmptySpace_2->setObjectName(QString::fromUtf8("cameraDockEmptySpace_2"));
        cameraDockEmptySpace_2->setGeometry(QRect(6, 605, 230, 175));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraDockEmptySpace_2->sizePolicy().hasHeightForWidth());
        cameraDockEmptySpace_2->setSizePolicy(sizePolicy);
        label_2 = new QLabel(burningDockContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(false);
        label_2->setGeometry(QRect(6, 565, 230, 32));
        label_2->setWordWrap(true);
        cameraAspectRatio_2 = new QLabel(burningDockContents);
        cameraAspectRatio_2->setObjectName(QString::fromUtf8("cameraAspectRatio_2"));
        cameraAspectRatio_2->setGeometry(QRect(6, 541, 230, 16));
        cameraFrustum_2 = new QWidget(burningDockContents);
        cameraFrustum_2->setObjectName(QString::fromUtf8("cameraFrustum_2"));
        cameraFrustum_2->setGeometry(QRect(6, 417, 230, 76));
        gridLayout_6 = new QGridLayout(cameraFrustum_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setVerticalSpacing(5);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        cameraFovLabel_2 = new QLabel(cameraFrustum_2);
        cameraFovLabel_2->setObjectName(QString::fromUtf8("cameraFovLabel_2"));

        gridLayout_6->addWidget(cameraFovLabel_2, 0, 0, 1, 1);

        cameraFovTextbox_2 = new QLineEdit(cameraFrustum_2);
        cameraFovTextbox_2->setObjectName(QString::fromUtf8("cameraFovTextbox_2"));
        cameraFovTextbox_2->setMinimumSize(QSize(60, 0));
        cameraFovTextbox_2->setMaximumSize(QSize(60, 16777215));

        gridLayout_6->addWidget(cameraFovTextbox_2, 0, 3, 1, 1);

        cameraFovSlider_2 = new QSlider(cameraFrustum_2);
        cameraFovSlider_2->setObjectName(QString::fromUtf8("cameraFovSlider_2"));
        cameraFovSlider_2->setMinimumSize(QSize(100, 0));
        cameraFovSlider_2->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(cameraFovSlider_2, 0, 1, 1, 1);

        cameraNearLabel_2 = new QLabel(cameraFrustum_2);
        cameraNearLabel_2->setObjectName(QString::fromUtf8("cameraNearLabel_2"));

        gridLayout_6->addWidget(cameraNearLabel_2, 1, 0, 1, 1);

        cameraNearTextbox_2 = new QLineEdit(cameraFrustum_2);
        cameraNearTextbox_2->setObjectName(QString::fromUtf8("cameraNearTextbox_2"));
        cameraNearTextbox_2->setMinimumSize(QSize(60, 0));
        cameraNearTextbox_2->setMaximumSize(QSize(60, 16777215));

        gridLayout_6->addWidget(cameraNearTextbox_2, 1, 3, 1, 1);

        cameraFarLabel_2 = new QLabel(cameraFrustum_2);
        cameraFarLabel_2->setObjectName(QString::fromUtf8("cameraFarLabel_2"));

        gridLayout_6->addWidget(cameraFarLabel_2, 2, 0, 1, 1);

        cameraFarTextbox_2 = new QLineEdit(cameraFrustum_2);
        cameraFarTextbox_2->setObjectName(QString::fromUtf8("cameraFarTextbox_2"));
        cameraFarTextbox_2->setMinimumSize(QSize(60, 0));
        cameraFarTextbox_2->setMaximumSize(QSize(60, 16777215));

        gridLayout_6->addWidget(cameraFarTextbox_2, 2, 3, 1, 1);

        cameraNearSlider_2 = new QSlider(cameraFrustum_2);
        cameraNearSlider_2->setObjectName(QString::fromUtf8("cameraNearSlider_2"));
        cameraNearSlider_2->setMinimumSize(QSize(100, 0));
        cameraNearSlider_2->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(cameraNearSlider_2, 1, 1, 1, 1);

        cameraFarSlider_2 = new QSlider(cameraFrustum_2);
        cameraFarSlider_2->setObjectName(QString::fromUtf8("cameraFarSlider_2"));
        cameraFarSlider_2->setMinimumSize(QSize(100, 0));
        cameraFarSlider_2->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(cameraFarSlider_2, 2, 1, 1, 1);

        resetSliders_2 = new QPushButton(burningDockContents);
        resetSliders_2->setObjectName(QString::fromUtf8("resetSliders_2"));
        resetSliders_2->setGeometry(QRect(0, 503, 242, 32));
        ParticlesLabel = new QLabel(burningDockContents);
        ParticlesLabel->setObjectName(QString::fromUtf8("ParticlesLabel"));
        ParticlesLabel->setGeometry(QRect(10, 310, 61, 16));
        NumParticlesSlider = new QSlider(burningDockContents);
        NumParticlesSlider->setObjectName(QString::fromUtf8("NumParticlesSlider"));
        NumParticlesSlider->setGeometry(QRect(110, 310, 160, 22));
        NumParticlesSlider->setOrientation(Qt::Horizontal);
        NumParticlesInput = new QLineEdit(burningDockContents);
        NumParticlesInput->setObjectName(QString::fromUtf8("NumParticlesInput"));
        NumParticlesInput->setGeometry(QRect(270, 310, 61, 21));
        BurningTreeDock->setWidget(burningDockContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, BurningTreeDock);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "A CS123 Final", nullptr));
        BurningButton->setText(QCoreApplication::translate("MainWindow", "Burning", nullptr));
        burningTreeLabel->setText(QCoreApplication::translate("MainWindow", "Let's make this cactus burn!", nullptr));
        CactusControlsLabel->setText(QCoreApplication::translate("MainWindow", "Cactus Controls", nullptr));
        SizeLabel->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        AngleLabel->setText(QCoreApplication::translate("MainWindow", "Branching Angle", nullptr));
        LengthALabel->setText(QCoreApplication::translate("MainWindow", "Branch Length", nullptr));
        BranchWidthLabel->setText(QCoreApplication::translate("MainWindow", "Branch Width", nullptr));
        RandomCactus->setText(QCoreApplication::translate("MainWindow", "Random", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Resize the window to change the aspect ratio.", nullptr));
        cameraAspectRatio_2->setText(QCoreApplication::translate("MainWindow", "Aspect ratio:", nullptr));
        cameraFovLabel_2->setText(QCoreApplication::translate("MainWindow", "FOV", nullptr));
        cameraNearLabel_2->setText(QCoreApplication::translate("MainWindow", "Near", nullptr));
        cameraFarLabel_2->setText(QCoreApplication::translate("MainWindow", "Far", nullptr));
        resetSliders_2->setText(QCoreApplication::translate("MainWindow", "Reset FOV / Near / Far", nullptr));
        ParticlesLabel->setText(QCoreApplication::translate("MainWindow", "Particles", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
