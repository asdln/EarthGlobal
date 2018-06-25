/********************************************************************************
** Form generated from reading UI file 'RenderModeDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERMODEDLG_H
#define UI_RENDERMODEDLG_H

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
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_RenderModeDlg
{
public:
    QGroupBox *groupBox;
    QRadioButton *radioButton_Gray;
    QRadioButton *radioButton_RGB;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QLabel *label;
    QLineEdit *lineEdit_RadioMax;
    QLineEdit *lineEdit_RadioMin;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QGroupBox *groupBox_4;
    QLineEdit *lineEdit_TemperatureMin;
    QLineEdit *lineEdit_TemperatureMax;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_8;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RenderModeDlg)
    {
        if (RenderModeDlg->objectName().isEmpty())
            RenderModeDlg->setObjectName(QStringLiteral("RenderModeDlg"));
        RenderModeDlg->resize(353, 385);
        groupBox = new QGroupBox(RenderModeDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 291, 51));
        radioButton_Gray = new QRadioButton(groupBox);
        radioButton_Gray->setObjectName(QStringLiteral("radioButton_Gray"));
        radioButton_Gray->setGeometry(QRect(30, 20, 89, 16));
        radioButton_RGB = new QRadioButton(groupBox);
        radioButton_RGB->setObjectName(QStringLiteral("radioButton_RGB"));
        radioButton_RGB->setGeometry(QRect(160, 20, 89, 16));
        groupBox_2 = new QGroupBox(RenderModeDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 90, 291, 241));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 30, 271, 91));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 71, 16));
        lineEdit_RadioMax = new QLineEdit(groupBox_3);
        lineEdit_RadioMax->setObjectName(QStringLiteral("lineEdit_RadioMax"));
        lineEdit_RadioMax->setGeometry(QRect(82, 50, 131, 20));
        lineEdit_RadioMin = new QLineEdit(groupBox_3);
        lineEdit_RadioMin->setObjectName(QStringLiteral("lineEdit_RadioMin"));
        lineEdit_RadioMin->setGeometry(QRect(82, 20, 131, 20));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 71, 16));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(220, 20, 51, 31));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(220, 50, 54, 12));
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 130, 271, 101));
        lineEdit_TemperatureMin = new QLineEdit(groupBox_4);
        lineEdit_TemperatureMin->setObjectName(QStringLiteral("lineEdit_TemperatureMin"));
        lineEdit_TemperatureMin->setGeometry(QRect(80, 30, 131, 20));
        lineEdit_TemperatureMax = new QLineEdit(groupBox_4);
        lineEdit_TemperatureMax->setObjectName(QStringLiteral("lineEdit_TemperatureMax"));
        lineEdit_TemperatureMax->setGeometry(QRect(80, 60, 131, 20));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 60, 51, 16));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 30, 51, 16));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(220, 30, 54, 12));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(220, 60, 54, 12));
        buttonBox = new QDialogButtonBox(RenderModeDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(160, 350, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(RenderModeDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), RenderModeDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RenderModeDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(RenderModeDlg);
    } // setupUi

    void retranslateUi(QDialog *RenderModeDlg)
    {
        RenderModeDlg->setWindowTitle(QApplication::translate("RenderModeDlg", "\346\270\262\346\237\223\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        groupBox->setTitle(QApplication::translate("RenderModeDlg", "\346\270\262\346\237\223\346\250\241\345\274\217", 0));
        radioButton_Gray->setText(QApplication::translate("RenderModeDlg", "\347\201\260\345\272\246\346\230\276\347\244\272", 0));
        radioButton_RGB->setText(QApplication::translate("RenderModeDlg", "\345\275\251\350\211\262\346\230\276\347\244\272", 0));
        groupBox_2->setTitle(QApplication::translate("RenderModeDlg", "\346\213\211\344\274\270\345\217\202\346\225\260", 0));
        groupBox_3->setTitle(QApplication::translate("RenderModeDlg", "\350\276\220\345\260\204", 0));
        label->setText(QApplication::translate("RenderModeDlg", "\346\234\200\345\260\217\345\200\274\357\274\232", 0));
        label_2->setText(QApplication::translate("RenderModeDlg", "\346\234\200\345\244\247\345\200\274\357\274\232", 0));
        label_5->setText(QApplication::translate("RenderModeDlg", "W/sr/m^2\n"
"", 0));
        label_6->setText(QApplication::translate("RenderModeDlg", "W/sr/m^2\n"
"", 0));
        groupBox_4->setTitle(QApplication::translate("RenderModeDlg", "\346\270\251\345\272\246", 0));
        label_3->setText(QApplication::translate("RenderModeDlg", "\346\234\200\345\244\247\345\200\274\357\274\232", 0));
        label_4->setText(QApplication::translate("RenderModeDlg", "\346\234\200\345\260\217\345\200\274\357\274\232", 0));
        label_7->setText(QApplication::translate("RenderModeDlg", "K", 0));
        label_8->setText(QApplication::translate("RenderModeDlg", "K", 0));
    } // retranslateUi

};

namespace Ui {
    class RenderModeDlg: public Ui_RenderModeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERMODEDLG_H
