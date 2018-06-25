/********************************************************************************
** Form generated from reading UI file 'earthglobal.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EARTHGLOBAL_H
#define UI_EARTHGLOBAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EarthGlobalClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EarthGlobalClass)
    {
        if (EarthGlobalClass->objectName().isEmpty())
            EarthGlobalClass->setObjectName(QStringLiteral("EarthGlobalClass"));
        EarthGlobalClass->resize(600, 400);
        menuBar = new QMenuBar(EarthGlobalClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        EarthGlobalClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EarthGlobalClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EarthGlobalClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EarthGlobalClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        EarthGlobalClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EarthGlobalClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EarthGlobalClass->setStatusBar(statusBar);

        retranslateUi(EarthGlobalClass);

        QMetaObject::connectSlotsByName(EarthGlobalClass);
    } // setupUi

    void retranslateUi(QMainWindow *EarthGlobalClass)
    {
        EarthGlobalClass->setWindowTitle(QApplication::translate("EarthGlobalClass", "EarthGlobal", 0));
    } // retranslateUi

};

namespace Ui {
    class EarthGlobalClass: public Ui_EarthGlobalClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EARTHGLOBAL_H
