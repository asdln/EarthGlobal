/********************************************************************************
** Form generated from reading UI file 'targetdatadlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARGETDATADLG_H
#define UI_TARGETDATADLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TargetDataDlg
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_tmp;
    QLabel *label_TRI;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditX;
    QLabel *label_2;
    QLineEdit *lineEditY;
    QLabel *label_3;
    QLineEdit *lineEditZ;
    QLabel *label;
    QLabel *label_13;
    QLabel *label_12;
    QLabel *label_11;
    QGroupBox *groupBox_ToRadio;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_fen;
    QLabel *label_4;
    QLineEdit *lineEdit_fa;
    QLabel *label_5;
    QLabel *label_7;
    QLineEdit *lineEdit_start;
    QLabel *label_6;
    QLineEdit *lineEdit_End;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *pushButton_LoadJet;
    QLabel *label_LoadJet;
    QPushButton *pushButton_Plt;
    QLabel *label_Plt;
    QGroupBox *groupBox_CustomJet;
    QPushButton *pushButton_RemoveJet;
    QPushButton *pushButton_AddJet;
    QTableWidget *tableWidget_JetPara;

    void setupUi(QDialog *TargetDataDlg)
    {
        if (TargetDataDlg->objectName().isEmpty())
            TargetDataDlg->setObjectName(QStringLiteral("TargetDataDlg"));
        TargetDataDlg->resize(566, 537);
        pushButton = new QPushButton(TargetDataDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 10, 75, 23));
        pushButton_2 = new QPushButton(TargetDataDlg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 40, 75, 23));
        label_tmp = new QLabel(TargetDataDlg);
        label_tmp->setObjectName(QStringLiteral("label_tmp"));
        label_tmp->setGeometry(QRect(110, 10, 321, 21));
        label_TRI = new QLabel(TargetDataDlg);
        label_TRI->setObjectName(QStringLiteral("label_TRI"));
        label_TRI->setGeometry(QRect(110, 40, 321, 16));
        buttonBox = new QDialogButtonBox(TargetDataDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(350, 490, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(TargetDataDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(320, 330, 241, 111));
        gridLayoutWidget_2 = new QWidget(groupBox);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 20, 221, 80));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEditX = new QLineEdit(gridLayoutWidget_2);
        lineEditX->setObjectName(QStringLiteral("lineEditX"));

        gridLayout_2->addWidget(lineEditX, 0, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lineEditY = new QLineEdit(gridLayoutWidget_2);
        lineEditY->setObjectName(QStringLiteral("lineEditY"));

        gridLayout_2->addWidget(lineEditY, 1, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lineEditZ = new QLineEdit(gridLayoutWidget_2);
        lineEditZ->setObjectName(QStringLiteral("lineEditZ"));

        gridLayout_2->addWidget(lineEditZ, 2, 1, 1, 1);

        label = new QLabel(gridLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_13 = new QLabel(gridLayoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 0, 2, 1, 1);

        label_12 = new QLabel(gridLayoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 1, 2, 1, 1);

        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 2, 2, 1, 1);

        groupBox_ToRadio = new QGroupBox(TargetDataDlg);
        groupBox_ToRadio->setObjectName(QStringLiteral("groupBox_ToRadio"));
        groupBox_ToRadio->setGeometry(QRect(20, 320, 291, 141));
        groupBox_ToRadio->setCheckable(true);
        gridLayoutWidget = new QWidget(groupBox_ToRadio);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 261, 111));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_fen = new QLineEdit(gridLayoutWidget);
        lineEdit_fen->setObjectName(QStringLiteral("lineEdit_fen"));

        gridLayout->addWidget(lineEdit_fen, 2, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        lineEdit_fa = new QLineEdit(gridLayoutWidget);
        lineEdit_fa->setObjectName(QStringLiteral("lineEdit_fa"));

        gridLayout->addWidget(lineEdit_fa, 3, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        lineEdit_start = new QLineEdit(gridLayoutWidget);
        lineEdit_start->setObjectName(QStringLiteral("lineEdit_start"));

        gridLayout->addWidget(lineEdit_start, 0, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        lineEdit_End = new QLineEdit(gridLayoutWidget);
        lineEdit_End->setObjectName(QStringLiteral("lineEdit_End"));

        gridLayout->addWidget(lineEdit_End, 1, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 1, 2, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 2, 2, 1, 1);

        pushButton_LoadJet = new QPushButton(TargetDataDlg);
        pushButton_LoadJet->setObjectName(QStringLiteral("pushButton_LoadJet"));
        pushButton_LoadJet->setGeometry(QRect(20, 100, 75, 23));
        label_LoadJet = new QLabel(TargetDataDlg);
        label_LoadJet->setObjectName(QStringLiteral("label_LoadJet"));
        label_LoadJet->setGeometry(QRect(120, 100, 321, 20));
        pushButton_Plt = new QPushButton(TargetDataDlg);
        pushButton_Plt->setObjectName(QStringLiteral("pushButton_Plt"));
        pushButton_Plt->setGeometry(QRect(20, 70, 75, 23));
        label_Plt = new QLabel(TargetDataDlg);
        label_Plt->setObjectName(QStringLiteral("label_Plt"));
        label_Plt->setGeometry(QRect(110, 70, 321, 16));
        groupBox_CustomJet = new QGroupBox(TargetDataDlg);
        groupBox_CustomJet->setObjectName(QStringLiteral("groupBox_CustomJet"));
        groupBox_CustomJet->setGeometry(QRect(20, 130, 531, 181));
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

        retranslateUi(TargetDataDlg);
        QObject::connect(pushButton, SIGNAL(clicked()), TargetDataDlg, SLOT(slotButtonClicked_tmp()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), TargetDataDlg, SLOT(slotButtonClicked_TRI()));
        QObject::connect(buttonBox, SIGNAL(accepted()), TargetDataDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TargetDataDlg, SLOT(reject()));
        QObject::connect(pushButton_LoadJet, SIGNAL(clicked()), TargetDataDlg, SLOT(slotButtonClicked_LoadJet()));
        QObject::connect(pushButton_Plt, SIGNAL(clicked()), TargetDataDlg, SLOT(slotButtonClicked_LoadPlt()));

        QMetaObject::connectSlotsByName(TargetDataDlg);
    } // setupUi

    void retranslateUi(QDialog *TargetDataDlg)
    {
        TargetDataDlg->setWindowTitle(QApplication::translate("TargetDataDlg", "\345\212\240\350\275\275\347\233\256\346\240\207\346\225\260\346\215\256", 0));
        pushButton->setText(QApplication::translate("TargetDataDlg", "\345\212\240\350\275\275tmp\346\225\260\346\215\256", 0));
        pushButton_2->setText(QApplication::translate("TargetDataDlg", "\345\212\240\350\275\275TRI\346\225\260\346\215\256", 0));
        label_tmp->setText(QString());
        label_TRI->setText(QString());
        groupBox->setTitle(QApplication::translate("TargetDataDlg", "\345\216\237\347\202\271\345\235\220\346\240\207\357\274\210\347\273\217\347\272\254\345\272\246\345\235\220\346\240\207\357\274\211", 0));
        label_2->setText(QApplication::translate("TargetDataDlg", "\347\272\254\345\272\246\357\274\232", 0));
        label_3->setText(QApplication::translate("TargetDataDlg", "\351\253\230\345\272\246\357\274\232", 0));
        label->setText(QApplication::translate("TargetDataDlg", "\347\273\217\345\272\246\357\274\232", 0));
        label_13->setText(QApplication::translate("TargetDataDlg", "\345\272\246", 0));
        label_12->setText(QApplication::translate("TargetDataDlg", "\345\272\246", 0));
        label_11->setText(QApplication::translate("TargetDataDlg", "\347\261\263", 0));
        groupBox_ToRadio->setTitle(QApplication::translate("TargetDataDlg", "\350\275\254\344\270\272\350\276\220\345\260\204\345\200\274", 0));
        label_4->setText(QApplication::translate("TargetDataDlg", "\350\265\267\345\247\213\346\263\242\351\225\277\357\274\232", 0));
        label_5->setText(QApplication::translate("TargetDataDlg", "\347\273\210\346\255\242\346\263\242\351\225\277\357\274\232", 0));
        label_7->setText(QApplication::translate("TargetDataDlg", "\345\217\221\345\260\204\347\216\207\357\274\232", 0));
        label_6->setText(QApplication::translate("TargetDataDlg", "\350\260\261\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        label_8->setText(QApplication::translate("TargetDataDlg", "um", 0));
        label_9->setText(QApplication::translate("TargetDataDlg", "um", 0));
        label_10->setText(QApplication::translate("TargetDataDlg", "\357\274\210\346\263\242\346\225\260\357\274\2111/cm", 0));
        pushButton_LoadJet->setText(QApplication::translate("TargetDataDlg", "\345\260\276\347\204\260\346\226\207\344\273\266", 0));
        label_LoadJet->setText(QString());
        pushButton_Plt->setText(QApplication::translate("TargetDataDlg", "\345\212\240\350\275\275Plt", 0));
        label_Plt->setText(QString());
        groupBox_CustomJet->setTitle(QApplication::translate("TargetDataDlg", "\345\260\276\347\204\260\350\207\252\345\256\232\344\271\211\344\275\215\347\275\256", 0));
        pushButton_RemoveJet->setText(QApplication::translate("TargetDataDlg", "\345\210\240\351\231\244\345\260\276\347\204\260", 0));
        pushButton_AddJet->setText(QApplication::translate("TargetDataDlg", "\346\267\273\345\212\240\345\260\276\347\204\260", 0));
    } // retranslateUi

};

namespace Ui {
    class TargetDataDlg: public Ui_TargetDataDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARGETDATADLG_H
