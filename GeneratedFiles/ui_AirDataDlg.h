/********************************************************************************
** Form generated from reading UI file 'AirDataDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIRDATADLG_H
#define UI_AIRDATADLG_H

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

class Ui_AirDataDlg
{
public:
    QPushButton *pushButton_OpenData;
    QLabel *label_filePath;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_Lon;
    QLineEdit *lineEdit_Lat;
    QLabel *label_4;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AirDataDlg)
    {
        if (AirDataDlg->objectName().isEmpty())
            AirDataDlg->setObjectName(QStringLiteral("AirDataDlg"));
        AirDataDlg->resize(324, 232);
        pushButton_OpenData = new QPushButton(AirDataDlg);
        pushButton_OpenData->setObjectName(QStringLiteral("pushButton_OpenData"));
        pushButton_OpenData->setGeometry(QRect(20, 30, 75, 23));
        label_filePath = new QLabel(AirDataDlg);
        label_filePath->setObjectName(QStringLiteral("label_filePath"));
        label_filePath->setGeometry(QRect(110, 30, 191, 21));
        groupBox = new QGroupBox(AirDataDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 80, 261, 101));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 81, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 60, 81, 16));
        lineEdit_Lon = new QLineEdit(groupBox);
        lineEdit_Lon->setObjectName(QStringLiteral("lineEdit_Lon"));
        lineEdit_Lon->setGeometry(QRect(100, 30, 113, 20));
        lineEdit_Lat = new QLineEdit(groupBox);
        lineEdit_Lat->setObjectName(QStringLiteral("lineEdit_Lat"));
        lineEdit_Lat->setGeometry(QRect(100, 60, 113, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(220, 30, 54, 12));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(220, 60, 54, 12));
        buttonBox = new QDialogButtonBox(AirDataDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(160, 190, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(AirDataDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), AirDataDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AirDataDlg, SLOT(reject()));
        QObject::connect(pushButton_OpenData, SIGNAL(clicked()), AirDataDlg, SLOT(slotPushButtonAddData()));

        QMetaObject::connectSlotsByName(AirDataDlg);
    } // setupUi

    void retranslateUi(QDialog *AirDataDlg)
    {
        AirDataDlg->setWindowTitle(QApplication::translate("AirDataDlg", "\345\212\240\350\275\275\345\244\247\346\260\224\346\225\260\346\215\256", 0));
        pushButton_OpenData->setText(QApplication::translate("AirDataDlg", "\346\211\223\345\274\200", 0));
        label_filePath->setText(QString());
        groupBox->setTitle(QApplication::translate("AirDataDlg", "\345\210\206\350\276\250\347\216\207", 0));
        label_2->setText(QApplication::translate("AirDataDlg", "\347\273\217\345\272\246\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        label_3->setText(QApplication::translate("AirDataDlg", "\347\272\254\345\272\246\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        label_4->setText(QApplication::translate("AirDataDlg", "\345\272\246", 0));
        label_5->setText(QApplication::translate("AirDataDlg", "\345\272\246", 0));
    } // retranslateUi

};

namespace Ui {
    class AirDataDlg: public Ui_AirDataDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIRDATADLG_H
