/********************************************************************************
** Form generated from reading UI file 'SetStartFrameDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSTARTFRAMEDLG_H
#define UI_SETSTARTFRAMEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SetStartFrameDlg
{
public:
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *SetStartFrameDlg)
    {
        if (SetStartFrameDlg->objectName().isEmpty())
            SetStartFrameDlg->setObjectName(QStringLiteral("SetStartFrameDlg"));
        SetStartFrameDlg->resize(332, 161);
        spinBox = new QSpinBox(SetStartFrameDlg);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(170, 50, 121, 22));
        pushButton = new QPushButton(SetStartFrameDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(220, 100, 75, 23));
        label = new QLabel(SetStartFrameDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 50, 54, 21));

        retranslateUi(SetStartFrameDlg);
        QObject::connect(pushButton, SIGNAL(clicked()), SetStartFrameDlg, SLOT(accept()));

        QMetaObject::connectSlotsByName(SetStartFrameDlg);
    } // setupUi

    void retranslateUi(QDialog *SetStartFrameDlg)
    {
        SetStartFrameDlg->setWindowTitle(QApplication::translate("SetStartFrameDlg", "\350\256\276\347\275\256\350\265\267\345\247\213\345\270\247", 0));
        pushButton->setText(QApplication::translate("SetStartFrameDlg", "OK", 0));
        label->setText(QApplication::translate("SetStartFrameDlg", "\350\265\267\345\247\213\345\270\247\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class SetStartFrameDlg: public Ui_SetStartFrameDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSTARTFRAMEDLG_H
