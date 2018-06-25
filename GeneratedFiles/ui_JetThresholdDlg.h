/********************************************************************************
** Form generated from reading UI file 'JetThresholdDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JETTHRESHOLDDLG_H
#define UI_JETTHRESHOLDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_JetThresholdDlg
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Cancel;
    QLabel *label_6;

    void setupUi(QDialog *JetThresholdDlg)
    {
        if (JetThresholdDlg->objectName().isEmpty())
            JetThresholdDlg->setObjectName(QStringLiteral("JetThresholdDlg"));
        JetThresholdDlg->resize(320, 162);
        label = new QLabel(JetThresholdDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 70, 71, 16));
        lineEdit = new QLineEdit(JetThresholdDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 70, 113, 20));
        pushButton_OK = new QPushButton(JetThresholdDlg);
        pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(130, 120, 75, 23));
        pushButton_Cancel = new QPushButton(JetThresholdDlg);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(220, 120, 75, 23));
        label_6 = new QLabel(JetThresholdDlg);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(230, 70, 54, 31));

        retranslateUi(JetThresholdDlg);

        QMetaObject::connectSlotsByName(JetThresholdDlg);
    } // setupUi

    void retranslateUi(QDialog *JetThresholdDlg)
    {
        JetThresholdDlg->setWindowTitle(QApplication::translate("JetThresholdDlg", "JetThresholdDlg", 0));
        label->setText(QApplication::translate("JetThresholdDlg", "\345\260\276\347\204\260\351\230\210\345\200\274\357\274\232", 0));
        pushButton_OK->setText(QApplication::translate("JetThresholdDlg", "\347\241\256\345\256\232", 0));
        pushButton_Cancel->setText(QApplication::translate("JetThresholdDlg", "\345\217\226\346\266\210", 0));
        label_6->setText(QApplication::translate("JetThresholdDlg", "W/sr/m^2\n"
"", 0));
    } // retranslateUi

};

namespace Ui {
    class JetThresholdDlg: public Ui_JetThresholdDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JETTHRESHOLDDLG_H
