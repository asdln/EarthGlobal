/********************************************************************************
** Form generated from reading UI file 'ProgressNumberWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSNUMBERWIDGET_H
#define UI_PROGRESSNUMBERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgressNumberWidget
{
public:
    QLabel *label;

    void setupUi(QWidget *ProgressNumberWidget)
    {
        if (ProgressNumberWidget->objectName().isEmpty())
            ProgressNumberWidget->setObjectName(QStringLiteral("ProgressNumberWidget"));
        ProgressNumberWidget->resize(306, 122);
        label = new QLabel(ProgressNumberWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 261, 41));

        retranslateUi(ProgressNumberWidget);

        QMetaObject::connectSlotsByName(ProgressNumberWidget);
    } // setupUi

    void retranslateUi(QWidget *ProgressNumberWidget)
    {
        ProgressNumberWidget->setWindowTitle(QApplication::translate("ProgressNumberWidget", "ProgressNumberWidget", 0));
        label->setText(QApplication::translate("ProgressNumberWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class ProgressNumberWidget: public Ui_ProgressNumberWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSNUMBERWIDGET_H
