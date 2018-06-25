/********************************************************************************
** Form generated from reading UI file 'CameraPostionDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAPOSTIONDLG_H
#define UI_CAMERAPOSTIONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraPostionDlg
{
public:
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_lon_s;
    QLabel *label_lon;
    QLabel *label_lat;
    QLineEdit *lineEdit_FanGunAngle;
    QLineEdit *lineEdit_lat_s;
    QLineEdit *lineEdit_hei;
    QLineEdit *lineEdit_lat;
    QLineEdit *lineEdit_lon;
    QLabel *label_height;
    QLineEdit *lineEdit_VerAngle;
    QLineEdit *lineEdit_hei_s;
    QLineEdit *lineEdit_horAngle;
    QLineEdit *lineEdit_hor_s;
    QLabel *label_4;
    QLineEdit *lineEdit_ver_s;
    QLabel *label_5;
    QLabel *label_22;
    QLabel *label_6;
    QLineEdit *lineEdit_Range;
    QLineEdit *lineEdit_range_s;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Trace;
    QPushButton *pushButton_SetRotateAngle;
    QPushButton *pushButton_copy;
    QPushButton *pushButton_set;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *doubleSpinBox_FocusHei;
    QPushButton *pushButton_Focus;
    QDoubleSpinBox *doubleSpinBox_FocusLat;
    QDoubleSpinBox *doubleSpinBox_FocusLon;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_27;
    QLabel *label_28;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_VerVP;
    QLabel *label_7;
    QLineEdit *lineEdit_HorVPCur;
    QLineEdit *lineEdit_VerVPCur;
    QLabel *label_8;
    QLabel *label_9;
    QGroupBox *groupBox_Target;
    QGroupBox *groupBox_4;
    QLineEdit *lineEdit_Lon;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineEdit_Hei;
    QLabel *label_14;
    QLineEdit *lineEdit_Lat;
    QLabel *label_15;
    QGroupBox *groupBox_5;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLineEdit *lineEdit_AngleX;
    QLineEdit *lineEdit_AngleY;
    QLineEdit *lineEdit_AngleZ;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QPushButton *pushButton_Set;
    QGroupBox *groupBox_3;
    QCheckBox *checkBox_Jet1;
    QCheckBox *checkBox_Jet2;
    QCheckBox *checkBox_Jet3;
    QCheckBox *checkBox_Jet4;
    QPushButton *pushButton_loadJet;
    QListWidget *listWidget;
    QGroupBox *groupBox_6;
    QLabel *label_26;
    QLineEdit *lineEdit_HorRes;
    QLineEdit *lineEdit_VerRes;
    QLabel *label_25;
    QTextEdit *textEdit_Info;
    QPushButton *pushButton_Win;

    void setupUi(QDialog *CameraPostionDlg)
    {
        if (CameraPostionDlg->objectName().isEmpty())
            CameraPostionDlg->setObjectName(QStringLiteral("CameraPostionDlg"));
        CameraPostionDlg->resize(521, 578);
        groupBox = new QGroupBox(CameraPostionDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 321, 291));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 301, 178));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_lon_s = new QLineEdit(gridLayoutWidget);
        lineEdit_lon_s->setObjectName(QStringLiteral("lineEdit_lon_s"));

        gridLayout->addWidget(lineEdit_lon_s, 0, 2, 1, 1);

        label_lon = new QLabel(gridLayoutWidget);
        label_lon->setObjectName(QStringLiteral("label_lon"));

        gridLayout->addWidget(label_lon, 0, 0, 1, 1);

        label_lat = new QLabel(gridLayoutWidget);
        label_lat->setObjectName(QStringLiteral("label_lat"));

        gridLayout->addWidget(label_lat, 1, 0, 1, 1);

        lineEdit_FanGunAngle = new QLineEdit(gridLayoutWidget);
        lineEdit_FanGunAngle->setObjectName(QStringLiteral("lineEdit_FanGunAngle"));

        gridLayout->addWidget(lineEdit_FanGunAngle, 5, 1, 1, 1);

        lineEdit_lat_s = new QLineEdit(gridLayoutWidget);
        lineEdit_lat_s->setObjectName(QStringLiteral("lineEdit_lat_s"));

        gridLayout->addWidget(lineEdit_lat_s, 1, 2, 1, 1);

        lineEdit_hei = new QLineEdit(gridLayoutWidget);
        lineEdit_hei->setObjectName(QStringLiteral("lineEdit_hei"));

        gridLayout->addWidget(lineEdit_hei, 2, 1, 1, 1);

        lineEdit_lat = new QLineEdit(gridLayoutWidget);
        lineEdit_lat->setObjectName(QStringLiteral("lineEdit_lat"));

        gridLayout->addWidget(lineEdit_lat, 1, 1, 1, 1);

        lineEdit_lon = new QLineEdit(gridLayoutWidget);
        lineEdit_lon->setObjectName(QStringLiteral("lineEdit_lon"));

        gridLayout->addWidget(lineEdit_lon, 0, 1, 1, 1);

        label_height = new QLabel(gridLayoutWidget);
        label_height->setObjectName(QStringLiteral("label_height"));

        gridLayout->addWidget(label_height, 2, 0, 1, 1);

        lineEdit_VerAngle = new QLineEdit(gridLayoutWidget);
        lineEdit_VerAngle->setObjectName(QStringLiteral("lineEdit_VerAngle"));

        gridLayout->addWidget(lineEdit_VerAngle, 4, 1, 1, 1);

        lineEdit_hei_s = new QLineEdit(gridLayoutWidget);
        lineEdit_hei_s->setObjectName(QStringLiteral("lineEdit_hei_s"));

        gridLayout->addWidget(lineEdit_hei_s, 2, 2, 1, 1);

        lineEdit_horAngle = new QLineEdit(gridLayoutWidget);
        lineEdit_horAngle->setObjectName(QStringLiteral("lineEdit_horAngle"));

        gridLayout->addWidget(lineEdit_horAngle, 3, 1, 1, 1);

        lineEdit_hor_s = new QLineEdit(gridLayoutWidget);
        lineEdit_hor_s->setObjectName(QStringLiteral("lineEdit_hor_s"));

        gridLayout->addWidget(lineEdit_hor_s, 3, 2, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_ver_s = new QLineEdit(gridLayoutWidget);
        lineEdit_ver_s->setObjectName(QStringLiteral("lineEdit_ver_s"));

        gridLayout->addWidget(lineEdit_ver_s, 4, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_22 = new QLabel(gridLayoutWidget);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout->addWidget(label_22, 5, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        lineEdit_Range = new QLineEdit(gridLayoutWidget);
        lineEdit_Range->setObjectName(QStringLiteral("lineEdit_Range"));

        gridLayout->addWidget(lineEdit_Range, 6, 1, 1, 1);

        lineEdit_range_s = new QLineEdit(gridLayoutWidget);
        lineEdit_range_s->setObjectName(QStringLiteral("lineEdit_range_s"));

        gridLayout->addWidget(lineEdit_range_s, 6, 2, 1, 1);

        horizontalLayoutWidget = new QWidget(groupBox);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 200, 301, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_Trace = new QPushButton(horizontalLayoutWidget);
        pushButton_Trace->setObjectName(QStringLiteral("pushButton_Trace"));

        horizontalLayout->addWidget(pushButton_Trace);

        pushButton_SetRotateAngle = new QPushButton(horizontalLayoutWidget);
        pushButton_SetRotateAngle->setObjectName(QStringLiteral("pushButton_SetRotateAngle"));

        horizontalLayout->addWidget(pushButton_SetRotateAngle);

        pushButton_copy = new QPushButton(horizontalLayoutWidget);
        pushButton_copy->setObjectName(QStringLiteral("pushButton_copy"));

        horizontalLayout->addWidget(pushButton_copy);

        pushButton_set = new QPushButton(horizontalLayoutWidget);
        pushButton_set->setObjectName(QStringLiteral("pushButton_set"));

        horizontalLayout->addWidget(pushButton_set);

        gridLayoutWidget_2 = new QWidget(groupBox);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 240, 301, 45));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_FocusHei = new QDoubleSpinBox(gridLayoutWidget_2);
        doubleSpinBox_FocusHei->setObjectName(QStringLiteral("doubleSpinBox_FocusHei"));

        gridLayout_2->addWidget(doubleSpinBox_FocusHei, 1, 3, 1, 1);

        pushButton_Focus = new QPushButton(gridLayoutWidget_2);
        pushButton_Focus->setObjectName(QStringLiteral("pushButton_Focus"));

        gridLayout_2->addWidget(pushButton_Focus, 1, 0, 1, 1);

        doubleSpinBox_FocusLat = new QDoubleSpinBox(gridLayoutWidget_2);
        doubleSpinBox_FocusLat->setObjectName(QStringLiteral("doubleSpinBox_FocusLat"));

        gridLayout_2->addWidget(doubleSpinBox_FocusLat, 1, 2, 1, 1);

        doubleSpinBox_FocusLon = new QDoubleSpinBox(gridLayoutWidget_2);
        doubleSpinBox_FocusLon->setObjectName(QStringLiteral("doubleSpinBox_FocusLon"));

        gridLayout_2->addWidget(doubleSpinBox_FocusLon, 1, 1, 1, 1);

        label_23 = new QLabel(gridLayoutWidget_2);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_2->addWidget(label_23, 0, 0, 1, 1);

        label_24 = new QLabel(gridLayoutWidget_2);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_2->addWidget(label_24, 0, 1, 1, 1);

        label_27 = new QLabel(gridLayoutWidget_2);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_2->addWidget(label_27, 0, 2, 1, 1);

        label_28 = new QLabel(gridLayoutWidget_2);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_2->addWidget(label_28, 0, 3, 1, 1);

        groupBox_2 = new QGroupBox(CameraPostionDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(340, 10, 171, 111));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 71, 16));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 71, 16));
        lineEdit_VerVP = new QLineEdit(groupBox_2);
        lineEdit_VerVP->setObjectName(QStringLiteral("lineEdit_VerVP"));
        lineEdit_VerVP->setGeometry(QRect(90, 80, 51, 20));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(150, 80, 16, 16));
        lineEdit_HorVPCur = new QLineEdit(groupBox_2);
        lineEdit_HorVPCur->setObjectName(QStringLiteral("lineEdit_HorVPCur"));
        lineEdit_HorVPCur->setGeometry(QRect(10, 30, 51, 20));
        lineEdit_VerVPCur = new QLineEdit(groupBox_2);
        lineEdit_VerVPCur->setObjectName(QStringLiteral("lineEdit_VerVPCur"));
        lineEdit_VerVPCur->setGeometry(QRect(10, 80, 51, 20));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(70, 30, 16, 16));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(70, 80, 16, 16));
        groupBox_Target = new QGroupBox(CameraPostionDlg);
        groupBox_Target->setObjectName(QStringLiteral("groupBox_Target"));
        groupBox_Target->setGeometry(QRect(10, 300, 321, 271));
        groupBox_4 = new QGroupBox(groupBox_Target);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 20, 171, 111));
        lineEdit_Lon = new QLineEdit(groupBox_4);
        lineEdit_Lon->setObjectName(QStringLiteral("lineEdit_Lon"));
        lineEdit_Lon->setGeometry(QRect(50, 20, 91, 20));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(150, 20, 54, 12));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(150, 50, 54, 12));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 20, 54, 12));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 50, 54, 12));
        lineEdit_Hei = new QLineEdit(groupBox_4);
        lineEdit_Hei->setObjectName(QStringLiteral("lineEdit_Hei"));
        lineEdit_Hei->setGeometry(QRect(50, 80, 91, 20));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(150, 80, 54, 12));
        lineEdit_Lat = new QLineEdit(groupBox_4);
        lineEdit_Lat->setObjectName(QStringLiteral("lineEdit_Lat"));
        lineEdit_Lat->setGeometry(QRect(50, 50, 91, 20));
        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 80, 54, 12));
        groupBox_5 = new QGroupBox(groupBox_Target);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 130, 171, 111));
        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 20, 54, 20));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 50, 54, 12));
        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 80, 54, 16));
        lineEdit_AngleX = new QLineEdit(groupBox_5);
        lineEdit_AngleX->setObjectName(QStringLiteral("lineEdit_AngleX"));
        lineEdit_AngleX->setGeometry(QRect(40, 20, 101, 20));
        lineEdit_AngleY = new QLineEdit(groupBox_5);
        lineEdit_AngleY->setObjectName(QStringLiteral("lineEdit_AngleY"));
        lineEdit_AngleY->setGeometry(QRect(40, 50, 101, 20));
        lineEdit_AngleZ = new QLineEdit(groupBox_5);
        lineEdit_AngleZ->setObjectName(QStringLiteral("lineEdit_AngleZ"));
        lineEdit_AngleZ->setGeometry(QRect(40, 80, 101, 20));
        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(150, 20, 54, 16));
        label_20 = new QLabel(groupBox_5);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(150, 50, 54, 16));
        label_21 = new QLabel(groupBox_5);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(150, 80, 54, 16));
        pushButton_Set = new QPushButton(groupBox_Target);
        pushButton_Set->setObjectName(QStringLiteral("pushButton_Set"));
        pushButton_Set->setGeometry(QRect(100, 240, 75, 23));
        groupBox_3 = new QGroupBox(groupBox_Target);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(190, 20, 121, 191));
        checkBox_Jet1 = new QCheckBox(groupBox_3);
        checkBox_Jet1->setObjectName(QStringLiteral("checkBox_Jet1"));
        checkBox_Jet1->setGeometry(QRect(30, 30, 71, 16));
        checkBox_Jet2 = new QCheckBox(groupBox_3);
        checkBox_Jet2->setObjectName(QStringLiteral("checkBox_Jet2"));
        checkBox_Jet2->setGeometry(QRect(30, 60, 71, 16));
        checkBox_Jet3 = new QCheckBox(groupBox_3);
        checkBox_Jet3->setObjectName(QStringLiteral("checkBox_Jet3"));
        checkBox_Jet3->setGeometry(QRect(30, 90, 71, 16));
        checkBox_Jet4 = new QCheckBox(groupBox_3);
        checkBox_Jet4->setObjectName(QStringLiteral("checkBox_Jet4"));
        checkBox_Jet4->setGeometry(QRect(30, 120, 71, 16));
        pushButton_loadJet = new QPushButton(groupBox_3);
        pushButton_loadJet->setObjectName(QStringLiteral("pushButton_loadJet"));
        pushButton_loadJet->setGeometry(QRect(30, 160, 75, 23));
        listWidget = new QListWidget(CameraPostionDlg);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(340, 320, 171, 231));
        groupBox_6 = new QGroupBox(CameraPostionDlg);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(340, 130, 171, 181));
        label_26 = new QLabel(groupBox_6);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(10, 120, 71, 16));
        lineEdit_HorRes = new QLineEdit(groupBox_6);
        lineEdit_HorRes->setObjectName(QStringLiteral("lineEdit_HorRes"));
        lineEdit_HorRes->setGeometry(QRect(80, 90, 81, 20));
        lineEdit_VerRes = new QLineEdit(groupBox_6);
        lineEdit_VerRes->setObjectName(QStringLiteral("lineEdit_VerRes"));
        lineEdit_VerRes->setGeometry(QRect(80, 120, 81, 21));
        label_25 = new QLabel(groupBox_6);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 90, 71, 21));
        textEdit_Info = new QTextEdit(groupBox_6);
        textEdit_Info->setObjectName(QStringLiteral("textEdit_Info"));
        textEdit_Info->setEnabled(false);
        textEdit_Info->setGeometry(QRect(10, 20, 151, 51));
        pushButton_Win = new QPushButton(groupBox_6);
        pushButton_Win->setObjectName(QStringLiteral("pushButton_Win"));
        pushButton_Win->setGeometry(QRect(80, 150, 75, 23));

        retranslateUi(CameraPostionDlg);
        QObject::connect(pushButton_copy, SIGNAL(clicked()), CameraPostionDlg, SLOT(slotCopy()));
        QObject::connect(pushButton_set, SIGNAL(clicked()), CameraPostionDlg, SLOT(slotSet()));
        QObject::connect(pushButton_Set, SIGNAL(clicked()), CameraPostionDlg, SLOT(slotSetNewPosition()));
        QObject::connect(pushButton_Trace, SIGNAL(clicked()), CameraPostionDlg, SLOT(slotTrace()));
        QObject::connect(checkBox_Jet1, SIGNAL(clicked(bool)), CameraPostionDlg, SLOT(slotJet1(bool)));
        QObject::connect(checkBox_Jet2, SIGNAL(clicked(bool)), CameraPostionDlg, SLOT(slotJet2(bool)));
        QObject::connect(checkBox_Jet3, SIGNAL(clicked(bool)), CameraPostionDlg, SLOT(slotJet3(bool)));
        QObject::connect(pushButton_loadJet, SIGNAL(clicked()), CameraPostionDlg, SLOT(slotLoadJet()));
        QObject::connect(checkBox_Jet4, SIGNAL(clicked(bool)), CameraPostionDlg, SLOT(slotJet4(bool)));
        QObject::connect(pushButton_SetRotateAngle, SIGNAL(clicked()), CameraPostionDlg, SLOT(slotSetRotateAngle()));
        QObject::connect(pushButton_Focus, SIGNAL(clicked()), CameraPostionDlg, SLOT(slotFocus()));
        QObject::connect(pushButton_Win, SIGNAL(clicked()), CameraPostionDlg, SLOT(slotSetWin()));

        QMetaObject::connectSlotsByName(CameraPostionDlg);
    } // setupUi

    void retranslateUi(QDialog *CameraPostionDlg)
    {
        CameraPostionDlg->setWindowTitle(QApplication::translate("CameraPostionDlg", "\344\274\240\346\204\237\345\231\250\345\217\202\346\225\260", 0));
        groupBox->setTitle(QApplication::translate("CameraPostionDlg", "\350\247\206\347\202\271", 0));
        label_lon->setText(QApplication::translate("CameraPostionDlg", "\347\273\217\345\272\246\357\274\232", 0));
        label_lat->setText(QApplication::translate("CameraPostionDlg", "\347\272\254\345\272\246\357\274\232", 0));
        label_height->setText(QApplication::translate("CameraPostionDlg", "\351\253\230\345\272\246\357\274\232", 0));
        label_4->setText(QApplication::translate("CameraPostionDlg", "\346\260\264\345\271\263\346\226\271\344\275\215\350\247\222\357\274\232", 0));
        label_5->setText(QApplication::translate("CameraPostionDlg", "\345\236\202\347\233\264\344\277\257\344\273\260\350\247\222\357\274\232", 0));
        label_22->setText(QApplication::translate("CameraPostionDlg", "\347\277\273\346\273\232\350\247\222:", 0));
        label_6->setText(QApplication::translate("CameraPostionDlg", "\347\204\246\350\267\235\357\274\232", 0));
        pushButton_Trace->setText(QApplication::translate("CameraPostionDlg", "\347\233\256\346\240\207\350\201\232\347\204\246", 0));
        pushButton_SetRotateAngle->setText(QApplication::translate("CameraPostionDlg", "\350\256\276\347\275\256\347\277\273\346\273\232\350\247\222", 0));
        pushButton_copy->setText(QApplication::translate("CameraPostionDlg", "\345\244\215\345\210\266", 0));
        pushButton_set->setText(QApplication::translate("CameraPostionDlg", "\350\256\276\347\275\256", 0));
        pushButton_Focus->setText(QApplication::translate("CameraPostionDlg", "\350\201\232\347\204\246", 0));
        label_23->setText(QString());
        label_24->setText(QApplication::translate("CameraPostionDlg", "\347\273\217\345\272\246", 0));
        label_27->setText(QApplication::translate("CameraPostionDlg", "\347\272\254\345\272\246", 0));
        label_28->setText(QApplication::translate("CameraPostionDlg", "\351\253\230\345\272\246", 0));
        groupBox_2->setTitle(QApplication::translate("CameraPostionDlg", "\350\247\206\345\234\272", 0));
        label->setText(QApplication::translate("CameraPostionDlg", "\346\260\264\345\271\263\350\247\206\345\234\272\350\247\222", 0));
        label_2->setText(QApplication::translate("CameraPostionDlg", "\345\236\202\347\233\264\350\247\206\345\234\272\350\247\222", 0));
        label_7->setText(QApplication::translate("CameraPostionDlg", "\345\272\246", 0));
        label_8->setText(QApplication::translate("CameraPostionDlg", "\345\272\246", 0));
        label_9->setText(QApplication::translate("CameraPostionDlg", "\345\272\246", 0));
        groupBox_Target->setTitle(QApplication::translate("CameraPostionDlg", "\347\233\256\346\240\207", 0));
        groupBox_4->setTitle(QApplication::translate("CameraPostionDlg", "\344\275\215\347\275\256", 0));
        label_10->setText(QApplication::translate("CameraPostionDlg", "\345\272\246", 0));
        label_11->setText(QApplication::translate("CameraPostionDlg", "\345\272\246", 0));
        label_12->setText(QApplication::translate("CameraPostionDlg", "\347\273\217\345\272\246\357\274\232", 0));
        label_13->setText(QApplication::translate("CameraPostionDlg", "\347\272\254\345\272\246\357\274\232", 0));
        label_14->setText(QApplication::translate("CameraPostionDlg", "\347\261\263", 0));
        label_15->setText(QApplication::translate("CameraPostionDlg", "\351\253\230\345\272\246\357\274\232", 0));
        groupBox_5->setTitle(QApplication::translate("CameraPostionDlg", "\350\247\222\345\272\246(\346\254\247\346\213\211\350\247\222)", 0));
        label_16->setText(QApplication::translate("CameraPostionDlg", "x \350\275\264\357\274\232", 0));
        label_17->setText(QApplication::translate("CameraPostionDlg", "y \350\275\264\357\274\232", 0));
        label_18->setText(QApplication::translate("CameraPostionDlg", "z \350\275\264\357\274\232", 0));
        label_19->setText(QApplication::translate("CameraPostionDlg", "\345\272\246", 0));
        label_20->setText(QApplication::translate("CameraPostionDlg", "\345\272\246", 0));
        label_21->setText(QApplication::translate("CameraPostionDlg", "\345\272\246", 0));
        pushButton_Set->setText(QApplication::translate("CameraPostionDlg", "\350\256\276\344\270\272\346\226\260\344\275\215\347\275\256", 0));
        groupBox_3->setTitle(QApplication::translate("CameraPostionDlg", "\345\260\276\347\204\260", 0));
        checkBox_Jet1->setText(QApplication::translate("CameraPostionDlg", "\345\260\276\347\204\2601", 0));
        checkBox_Jet2->setText(QApplication::translate("CameraPostionDlg", "\345\260\276\347\204\2602", 0));
        checkBox_Jet3->setText(QApplication::translate("CameraPostionDlg", "\345\260\276\347\204\2603", 0));
        checkBox_Jet4->setText(QApplication::translate("CameraPostionDlg", "\345\260\276\347\204\2604", 0));
        pushButton_loadJet->setText(QApplication::translate("CameraPostionDlg", "\345\212\240\350\275\275\345\260\276\347\204\260", 0));
        groupBox_6->setTitle(QApplication::translate("CameraPostionDlg", "\345\210\206\350\276\250\347\216\207", 0));
        label_26->setText(QApplication::translate("CameraPostionDlg", "\345\236\202\347\233\264\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        label_25->setText(QApplication::translate("CameraPostionDlg", "\346\260\264\345\271\263\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        pushButton_Win->setText(QApplication::translate("CameraPostionDlg", "\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class CameraPostionDlg: public Ui_CameraPostionDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPOSTIONDLG_H
