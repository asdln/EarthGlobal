/********************************************************************************
** Form generated from reading UI file 'PltTempDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLTTEMPDLG_H
#define UI_PLTTEMPDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PltTempDlg
{
public:
    QGroupBox *groupBox_ToRadio;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_start;
    QLineEdit *lineEdit_End;
    QLineEdit *lineEdit_fen;
    QLineEdit *lineEdit_fa;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton_Path;
    QLabel *label_Path;

    void setupUi(QDialog *PltTempDlg)
    {
        if (PltTempDlg->objectName().isEmpty())
            PltTempDlg->setObjectName(QStringLiteral("PltTempDlg"));
        PltTempDlg->resize(400, 294);
        groupBox_ToRadio = new QGroupBox(PltTempDlg);
        groupBox_ToRadio->setObjectName(QStringLiteral("groupBox_ToRadio"));
        groupBox_ToRadio->setGeometry(QRect(10, 90, 371, 151));
        groupBox_ToRadio->setCheckable(false);
        label_4 = new QLabel(groupBox_ToRadio);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 30, 54, 12));
        label_5 = new QLabel(groupBox_ToRadio);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 60, 54, 12));
        label_6 = new QLabel(groupBox_ToRadio);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 90, 54, 12));
        label_7 = new QLabel(groupBox_ToRadio);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 120, 54, 12));
        lineEdit_start = new QLineEdit(groupBox_ToRadio);
        lineEdit_start->setObjectName(QStringLiteral("lineEdit_start"));
        lineEdit_start->setGeometry(QRect(130, 30, 141, 20));
        lineEdit_End = new QLineEdit(groupBox_ToRadio);
        lineEdit_End->setObjectName(QStringLiteral("lineEdit_End"));
        lineEdit_End->setGeometry(QRect(130, 60, 141, 20));
        lineEdit_fen = new QLineEdit(groupBox_ToRadio);
        lineEdit_fen->setObjectName(QStringLiteral("lineEdit_fen"));
        lineEdit_fen->setGeometry(QRect(130, 90, 141, 20));
        lineEdit_fa = new QLineEdit(groupBox_ToRadio);
        lineEdit_fa->setObjectName(QStringLiteral("lineEdit_fa"));
        lineEdit_fa->setGeometry(QRect(130, 120, 141, 20));
        label_8 = new QLabel(groupBox_ToRadio);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(280, 30, 54, 12));
        label_9 = new QLabel(groupBox_ToRadio);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(280, 60, 54, 12));
        label_10 = new QLabel(groupBox_ToRadio);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(280, 90, 81, 16));
        buttonBox = new QDialogButtonBox(PltTempDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(230, 250, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        pushButton_Path = new QPushButton(PltTempDlg);
        pushButton_Path->setObjectName(QStringLiteral("pushButton_Path"));
        pushButton_Path->setGeometry(QRect(10, 30, 75, 23));
        label_Path = new QLabel(PltTempDlg);
        label_Path->setObjectName(QStringLiteral("label_Path"));
        label_Path->setGeometry(QRect(100, 30, 281, 21));

        retranslateUi(PltTempDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), PltTempDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PltTempDlg, SLOT(reject()));
        QObject::connect(pushButton_Path, SIGNAL(clicked()), PltTempDlg, SLOT(slotPushButtonPath()));

        QMetaObject::connectSlotsByName(PltTempDlg);
    } // setupUi

    void retranslateUi(QDialog *PltTempDlg)
    {
        PltTempDlg->setWindowTitle(QApplication::translate("PltTempDlg", "PltTempDlg", 0));
        groupBox_ToRadio->setTitle(QApplication::translate("PltTempDlg", "\350\275\254\344\270\272\350\276\220\345\260\204\345\200\274", 0));
        label_4->setText(QApplication::translate("PltTempDlg", "\350\265\267\345\247\213\346\263\242\351\225\277\357\274\232", 0));
        label_5->setText(QApplication::translate("PltTempDlg", "\347\273\210\346\255\242\346\263\242\351\225\277\357\274\232", 0));
        label_6->setText(QApplication::translate("PltTempDlg", "\350\260\261\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        label_7->setText(QApplication::translate("PltTempDlg", "\345\217\221\345\260\204\347\216\207\357\274\232", 0));
        label_8->setText(QApplication::translate("PltTempDlg", "um", 0));
        label_9->setText(QApplication::translate("PltTempDlg", "um", 0));
        label_10->setText(QApplication::translate("PltTempDlg", "\357\274\210\346\263\242\346\225\260\357\274\2111/cm", 0));
        pushButton_Path->setText(QApplication::translate("PltTempDlg", "\346\226\207\344\273\266\350\267\257\345\276\204", 0));
        label_Path->setText(QApplication::translate("PltTempDlg", "\"\"", 0));
    } // retranslateUi

};

namespace Ui {
    class PltTempDlg: public Ui_PltTempDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLTTEMPDLG_H
