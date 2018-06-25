/********************************************************************************
** Form generated from reading UI file 'SetParaDockWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPARADOCKWIDGET_H
#define UI_SETPARADOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetParaDockWidget
{
public:
    QWidget *widget;
    QPushButton *pushButton;

    void setupUi(QDockWidget *SetParaDockWidget)
    {
        if (SetParaDockWidget->objectName().isEmpty())
            SetParaDockWidget->setObjectName(QStringLiteral("SetParaDockWidget"));
        SetParaDockWidget->resize(339, 161);
        widget = new QWidget();
        widget->setObjectName(QStringLiteral("widget"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(210, 90, 75, 23));
        SetParaDockWidget->setWidget(widget);

        retranslateUi(SetParaDockWidget);

        QMetaObject::connectSlotsByName(SetParaDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *SetParaDockWidget)
    {
        SetParaDockWidget->setWindowTitle(QApplication::translate("SetParaDockWidget", "\350\256\276\347\275\256\350\265\267\345\247\213\345\270\247", 0));
        pushButton->setText(QApplication::translate("SetParaDockWidget", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class SetParaDockWidget: public Ui_SetParaDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPARADOCKWIDGET_H
