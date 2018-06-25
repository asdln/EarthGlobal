/********************************************************************************
** Form generated from reading UI file 'AirDataParaWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIRDATAPARAWIDGET_H
#define UI_AIRDATAPARAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AirDataParaWidget
{
public:
    QLabel *label;
    QLineEdit *lineEdit_trans;
    QLabel *label_2;
    QPushButton *pushButton_set;

    void setupUi(QWidget *AirDataParaWidget)
    {
        if (AirDataParaWidget->objectName().isEmpty())
            AirDataParaWidget->setObjectName(QStringLiteral("AirDataParaWidget"));
        AirDataParaWidget->resize(241, 262);
        label = new QLabel(AirDataParaWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 71, 20));
        lineEdit_trans = new QLineEdit(AirDataParaWidget);
        lineEdit_trans->setObjectName(QStringLiteral("lineEdit_trans"));
        lineEdit_trans->setGeometry(QRect(72, 30, 141, 20));
        label_2 = new QLabel(AirDataParaWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 91, 16));
        pushButton_set = new QPushButton(AirDataParaWidget);
        pushButton_set->setObjectName(QStringLiteral("pushButton_set"));
        pushButton_set->setGeometry(QRect(140, 100, 75, 23));

        retranslateUi(AirDataParaWidget);
        QObject::connect(pushButton_set, SIGNAL(clicked()), AirDataParaWidget, SLOT(slotSet()));

        QMetaObject::connectSlotsByName(AirDataParaWidget);
    } // setupUi

    void retranslateUi(QWidget *AirDataParaWidget)
    {
        AirDataParaWidget->setWindowTitle(QApplication::translate("AirDataParaWidget", "\345\244\247\346\260\224\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        label->setText(QApplication::translate("AirDataParaWidget", "\351\200\217\346\230\216\345\272\246\357\274\232", 0));
        label_2->setText(QApplication::translate("AirDataParaWidget", "(\345\200\274\345\237\2370.0-1.0)", 0));
        pushButton_set->setText(QApplication::translate("AirDataParaWidget", "\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class AirDataParaWidget: public Ui_AirDataParaWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIRDATAPARAWIDGET_H
