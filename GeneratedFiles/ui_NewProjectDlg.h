/********************************************************************************
** Form generated from reading UI file 'NewProjectDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTDLG_H
#define UI_NEWPROJECTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewProjectDlg
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_ProjectPath;
    QPushButton *pushButton_EarthRadio;
    QPushButton *pushButton_ProjectPath;
    QPushButton *pushButton_CameraPath;
    QPushButton *pushButton_TargetPath;
    QLineEdit *lineEdit_CameraTrack;
    QLineEdit *lineEdit_TargetTrack;
    QLineEdit *lineEdit_EarthRadio;
    QPushButton *pushButton_AirDir;
    QLineEdit *lineEdit_AirDir;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_HorVPCur;
    QLineEdit *lineEdit_VerVPCur;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_VerRes;
    QLineEdit *lineEdit_HorRes;
    QLabel *label_26;
    QLabel *label_25;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_4;
    QLabel *label_3;
    QLineEdit *lineEdit_RadioMax;
    QLineEdit *lineEdit_RadioMin;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_OK;
    QGroupBox *groupBox;
    QGroupBox *groupBox_ToRadio;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *lineEdit_start;
    QLineEdit *lineEdit_End;
    QLineEdit *lineEdit_fen;
    QLineEdit *lineEdit_fa;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QPushButton *pushButton_TRI;
    QPushButton *pushButton_tmp;
    QPushButton *pushButton_LoadJet;
    QLineEdit *lineEdit_tmp;
    QLineEdit *lineEdit_TRI;
    QLineEdit *lineEdit_LoadJet;
    QPushButton *pushButton_Plt;
    QLineEdit *lineEdit_Plt;
    QGroupBox *groupBox_CustomJet;
    QPushButton *pushButton_RemoveJet;
    QPushButton *pushButton_AddJet;
    QTableWidget *tableWidget_JetPara;

    void setupUi(QDialog *NewProjectDlg)
    {
        if (NewProjectDlg->objectName().isEmpty())
            NewProjectDlg->setObjectName(QStringLiteral("NewProjectDlg"));
        NewProjectDlg->resize(600, 709);
        gridLayoutWidget = new QWidget(NewProjectDlg);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 581, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_ProjectPath = new QLineEdit(gridLayoutWidget);
        lineEdit_ProjectPath->setObjectName(QStringLiteral("lineEdit_ProjectPath"));

        gridLayout->addWidget(lineEdit_ProjectPath, 0, 1, 1, 1);

        pushButton_EarthRadio = new QPushButton(gridLayoutWidget);
        pushButton_EarthRadio->setObjectName(QStringLiteral("pushButton_EarthRadio"));

        gridLayout->addWidget(pushButton_EarthRadio, 3, 0, 1, 1);

        pushButton_ProjectPath = new QPushButton(gridLayoutWidget);
        pushButton_ProjectPath->setObjectName(QStringLiteral("pushButton_ProjectPath"));

        gridLayout->addWidget(pushButton_ProjectPath, 0, 0, 1, 1);

        pushButton_CameraPath = new QPushButton(gridLayoutWidget);
        pushButton_CameraPath->setObjectName(QStringLiteral("pushButton_CameraPath"));

        gridLayout->addWidget(pushButton_CameraPath, 1, 0, 1, 1);

        pushButton_TargetPath = new QPushButton(gridLayoutWidget);
        pushButton_TargetPath->setObjectName(QStringLiteral("pushButton_TargetPath"));

        gridLayout->addWidget(pushButton_TargetPath, 2, 0, 1, 1);

        lineEdit_CameraTrack = new QLineEdit(gridLayoutWidget);
        lineEdit_CameraTrack->setObjectName(QStringLiteral("lineEdit_CameraTrack"));

        gridLayout->addWidget(lineEdit_CameraTrack, 1, 1, 1, 1);

        lineEdit_TargetTrack = new QLineEdit(gridLayoutWidget);
        lineEdit_TargetTrack->setObjectName(QStringLiteral("lineEdit_TargetTrack"));

        gridLayout->addWidget(lineEdit_TargetTrack, 2, 1, 1, 1);

        lineEdit_EarthRadio = new QLineEdit(gridLayoutWidget);
        lineEdit_EarthRadio->setObjectName(QStringLiteral("lineEdit_EarthRadio"));

        gridLayout->addWidget(lineEdit_EarthRadio, 3, 1, 1, 1);

        pushButton_AirDir = new QPushButton(gridLayoutWidget);
        pushButton_AirDir->setObjectName(QStringLiteral("pushButton_AirDir"));

        gridLayout->addWidget(pushButton_AirDir, 4, 0, 1, 1);

        lineEdit_AirDir = new QLineEdit(gridLayoutWidget);
        lineEdit_AirDir->setObjectName(QStringLiteral("lineEdit_AirDir"));

        gridLayout->addWidget(lineEdit_AirDir, 4, 1, 1, 1);

        groupBox_2 = new QGroupBox(NewProjectDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(310, 530, 181, 141));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 71, 16));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 71, 16));
        lineEdit_HorVPCur = new QLineEdit(groupBox_2);
        lineEdit_HorVPCur->setObjectName(QStringLiteral("lineEdit_HorVPCur"));
        lineEdit_HorVPCur->setGeometry(QRect(90, 20, 51, 20));
        lineEdit_VerVPCur = new QLineEdit(groupBox_2);
        lineEdit_VerVPCur->setObjectName(QStringLiteral("lineEdit_VerVPCur"));
        lineEdit_VerVPCur->setGeometry(QRect(90, 50, 51, 20));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(140, 20, 21, 16));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(140, 50, 54, 16));
        lineEdit_VerRes = new QLineEdit(groupBox_2);
        lineEdit_VerRes->setObjectName(QStringLiteral("lineEdit_VerRes"));
        lineEdit_VerRes->setGeometry(QRect(90, 110, 81, 20));
        lineEdit_HorRes = new QLineEdit(groupBox_2);
        lineEdit_HorRes->setObjectName(QStringLiteral("lineEdit_HorRes"));
        lineEdit_HorRes->setGeometry(QRect(90, 80, 81, 20));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(10, 110, 71, 16));
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 80, 71, 21));
        groupBox_3 = new QGroupBox(NewProjectDlg);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 530, 291, 141));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 20, 271, 81));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 20, 71, 16));
        lineEdit_RadioMax = new QLineEdit(groupBox_4);
        lineEdit_RadioMax->setObjectName(QStringLiteral("lineEdit_RadioMax"));
        lineEdit_RadioMax->setGeometry(QRect(82, 50, 131, 20));
        lineEdit_RadioMin = new QLineEdit(groupBox_4);
        lineEdit_RadioMin->setObjectName(QStringLiteral("lineEdit_RadioMin"));
        lineEdit_RadioMin->setGeometry(QRect(82, 20, 131, 20));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 50, 71, 16));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(220, 20, 51, 31));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(220, 50, 54, 12));
        pushButton_OK = new QPushButton(NewProjectDlg);
        pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(480, 680, 75, 23));
        groupBox = new QGroupBox(NewProjectDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 160, 581, 161));
        groupBox_ToRadio = new QGroupBox(groupBox);
        groupBox_ToRadio->setObjectName(QStringLiteral("groupBox_ToRadio"));
        groupBox_ToRadio->setGeometry(QRect(260, 10, 311, 141));
        groupBox_ToRadio->setCheckable(true);
        label_13 = new QLabel(groupBox_ToRadio);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(20, 20, 54, 12));
        label_14 = new QLabel(groupBox_ToRadio);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(20, 50, 54, 12));
        label_15 = new QLabel(groupBox_ToRadio);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(20, 80, 54, 12));
        label_16 = new QLabel(groupBox_ToRadio);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(20, 110, 54, 12));
        lineEdit_start = new QLineEdit(groupBox_ToRadio);
        lineEdit_start->setObjectName(QStringLiteral("lineEdit_start"));
        lineEdit_start->setGeometry(QRect(80, 20, 141, 20));
        lineEdit_End = new QLineEdit(groupBox_ToRadio);
        lineEdit_End->setObjectName(QStringLiteral("lineEdit_End"));
        lineEdit_End->setGeometry(QRect(80, 50, 141, 20));
        lineEdit_fen = new QLineEdit(groupBox_ToRadio);
        lineEdit_fen->setObjectName(QStringLiteral("lineEdit_fen"));
        lineEdit_fen->setGeometry(QRect(80, 80, 141, 20));
        lineEdit_fa = new QLineEdit(groupBox_ToRadio);
        lineEdit_fa->setObjectName(QStringLiteral("lineEdit_fa"));
        lineEdit_fa->setGeometry(QRect(80, 110, 141, 20));
        label_17 = new QLabel(groupBox_ToRadio);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(230, 20, 54, 12));
        label_18 = new QLabel(groupBox_ToRadio);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(230, 50, 54, 12));
        label_19 = new QLabel(groupBox_ToRadio);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(230, 80, 81, 16));
        pushButton_TRI = new QPushButton(groupBox);
        pushButton_TRI->setObjectName(QStringLiteral("pushButton_TRI"));
        pushButton_TRI->setGeometry(QRect(10, 60, 75, 23));
        pushButton_tmp = new QPushButton(groupBox);
        pushButton_tmp->setObjectName(QStringLiteral("pushButton_tmp"));
        pushButton_tmp->setGeometry(QRect(10, 30, 75, 23));
        pushButton_LoadJet = new QPushButton(groupBox);
        pushButton_LoadJet->setObjectName(QStringLiteral("pushButton_LoadJet"));
        pushButton_LoadJet->setGeometry(QRect(10, 120, 75, 23));
        lineEdit_tmp = new QLineEdit(groupBox);
        lineEdit_tmp->setObjectName(QStringLiteral("lineEdit_tmp"));
        lineEdit_tmp->setGeometry(QRect(100, 30, 151, 20));
        lineEdit_TRI = new QLineEdit(groupBox);
        lineEdit_TRI->setObjectName(QStringLiteral("lineEdit_TRI"));
        lineEdit_TRI->setGeometry(QRect(100, 60, 151, 20));
        lineEdit_LoadJet = new QLineEdit(groupBox);
        lineEdit_LoadJet->setObjectName(QStringLiteral("lineEdit_LoadJet"));
        lineEdit_LoadJet->setGeometry(QRect(100, 120, 151, 20));
        pushButton_Plt = new QPushButton(groupBox);
        pushButton_Plt->setObjectName(QStringLiteral("pushButton_Plt"));
        pushButton_Plt->setGeometry(QRect(10, 90, 75, 23));
        lineEdit_Plt = new QLineEdit(groupBox);
        lineEdit_Plt->setObjectName(QStringLiteral("lineEdit_Plt"));
        lineEdit_Plt->setGeometry(QRect(100, 90, 151, 20));
        groupBox_CustomJet = new QGroupBox(NewProjectDlg);
        groupBox_CustomJet->setObjectName(QStringLiteral("groupBox_CustomJet"));
        groupBox_CustomJet->setGeometry(QRect(30, 330, 531, 181));
        groupBox_CustomJet->setCheckable(true);
        pushButton_RemoveJet = new QPushButton(groupBox_CustomJet);
        pushButton_RemoveJet->setObjectName(QStringLiteral("pushButton_RemoveJet"));
        pushButton_RemoveJet->setGeometry(QRect(440, 150, 75, 23));
        pushButton_AddJet = new QPushButton(groupBox_CustomJet);
        pushButton_AddJet->setObjectName(QStringLiteral("pushButton_AddJet"));
        pushButton_AddJet->setGeometry(QRect(360, 150, 75, 23));
        tableWidget_JetPara = new QTableWidget(groupBox_CustomJet);
        tableWidget_JetPara->setObjectName(QStringLiteral("tableWidget_JetPara"));
        tableWidget_JetPara->setGeometry(QRect(10, 20, 509, 121));

        retranslateUi(NewProjectDlg);

        QMetaObject::connectSlotsByName(NewProjectDlg);
    } // setupUi

    void retranslateUi(QDialog *NewProjectDlg)
    {
        NewProjectDlg->setWindowTitle(QApplication::translate("NewProjectDlg", "\345\210\233\345\273\272\345\267\245\347\250\213", 0));
        pushButton_EarthRadio->setText(QApplication::translate("NewProjectDlg", "\345\234\260\350\241\250\350\276\220\345\260\204", 0));
        pushButton_ProjectPath->setText(QApplication::translate("NewProjectDlg", "\350\256\276\347\275\256\345\267\245\347\250\213\350\267\257\345\276\204", 0));
        pushButton_CameraPath->setText(QApplication::translate("NewProjectDlg", "\344\274\240\346\204\237\345\231\250\350\275\250\350\277\271\346\226\207\344\273\266", 0));
        pushButton_TargetPath->setText(QApplication::translate("NewProjectDlg", "\347\233\256\346\240\207\350\275\250\350\277\271\346\226\207\344\273\266", 0));
        pushButton_AirDir->setText(QApplication::translate("NewProjectDlg", "\345\244\247\346\260\224\350\267\257\345\276\204", 0));
        groupBox_2->setTitle(QApplication::translate("NewProjectDlg", "\350\247\206\345\234\272", 0));
        label->setText(QApplication::translate("NewProjectDlg", "\346\260\264\345\271\263\350\247\206\345\234\272\350\247\222", 0));
        label_2->setText(QApplication::translate("NewProjectDlg", "\345\236\202\347\233\264\350\247\206\345\234\272\350\247\222", 0));
        label_8->setText(QApplication::translate("NewProjectDlg", "\345\272\246", 0));
        label_9->setText(QApplication::translate("NewProjectDlg", "\345\272\246", 0));
        label_26->setText(QApplication::translate("NewProjectDlg", "\345\236\202\347\233\264\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        label_25->setText(QApplication::translate("NewProjectDlg", "\346\260\264\345\271\263\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        groupBox_3->setTitle(QApplication::translate("NewProjectDlg", "\346\213\211\344\274\270\345\217\202\346\225\260", 0));
        groupBox_4->setTitle(QApplication::translate("NewProjectDlg", "\350\276\220\345\260\204", 0));
        label_3->setText(QApplication::translate("NewProjectDlg", "\346\234\200\345\260\217\345\200\274\357\274\232", 0));
        label_4->setText(QApplication::translate("NewProjectDlg", "\346\234\200\345\244\247\345\200\274\357\274\232", 0));
        label_5->setText(QApplication::translate("NewProjectDlg", "W/sr/m^2\n"
"", 0));
        label_6->setText(QApplication::translate("NewProjectDlg", "W/sr/m^2\n"
"", 0));
        pushButton_OK->setText(QApplication::translate("NewProjectDlg", "\347\241\256\345\256\232", 0));
        groupBox->setTitle(QApplication::translate("NewProjectDlg", "\347\233\256\346\240\207", 0));
        groupBox_ToRadio->setTitle(QApplication::translate("NewProjectDlg", "\350\275\254\344\270\272\350\276\220\345\260\204\345\200\274", 0));
        label_13->setText(QApplication::translate("NewProjectDlg", "\350\265\267\345\247\213\346\263\242\351\225\277\357\274\232", 0));
        label_14->setText(QApplication::translate("NewProjectDlg", "\347\273\210\346\255\242\346\263\242\351\225\277\357\274\232", 0));
        label_15->setText(QApplication::translate("NewProjectDlg", "\350\260\261\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        label_16->setText(QApplication::translate("NewProjectDlg", "\345\217\221\345\260\204\347\216\207\357\274\232", 0));
        label_17->setText(QApplication::translate("NewProjectDlg", "um", 0));
        label_18->setText(QApplication::translate("NewProjectDlg", "um", 0));
        label_19->setText(QApplication::translate("NewProjectDlg", "\357\274\210\346\263\242\346\225\260\357\274\2111/cm", 0));
        pushButton_TRI->setText(QApplication::translate("NewProjectDlg", "\345\212\240\350\275\275TRI\346\225\260\346\215\256", 0));
        pushButton_tmp->setText(QApplication::translate("NewProjectDlg", "\345\212\240\350\275\275tmp\346\225\260\346\215\256", 0));
        pushButton_LoadJet->setText(QApplication::translate("NewProjectDlg", "\345\260\276\347\204\260\346\226\207\344\273\266", 0));
        pushButton_Plt->setText(QApplication::translate("NewProjectDlg", "\345\212\240\350\275\275Plt", 0));
        groupBox_CustomJet->setTitle(QApplication::translate("NewProjectDlg", "\345\260\276\347\204\260\350\207\252\345\256\232\344\271\211\344\275\215\347\275\256", 0));
        pushButton_RemoveJet->setText(QApplication::translate("NewProjectDlg", "\345\210\240\351\231\244\345\260\276\347\204\260", 0));
        pushButton_AddJet->setText(QApplication::translate("NewProjectDlg", "\346\267\273\345\212\240\345\260\276\347\204\260", 0));
    } // retranslateUi

};

namespace Ui {
    class NewProjectDlg: public Ui_NewProjectDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTDLG_H
