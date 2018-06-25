/********************************************************************************
** Form generated from reading UI file 'Target2PltDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARGET2PLTDLG_H
#define UI_TARGET2PLTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Target2PltDlg
{
public:
    QPushButton *pushButton_Tri;
    QPushButton *pushButton_Tmp;
    QPushButton *pushButton_OutPlt;
    QLineEdit *lineEdit_Tri;
    QLineEdit *lineEdit_Tmp;
    QLineEdit *lineEdit_OutPlt;
    QPushButton *pushButton_OK;

    void setupUi(QDialog *Target2PltDlg)
    {
        if (Target2PltDlg->objectName().isEmpty())
            Target2PltDlg->setObjectName(QStringLiteral("Target2PltDlg"));
        Target2PltDlg->resize(418, 240);
        pushButton_Tri = new QPushButton(Target2PltDlg);
        pushButton_Tri->setObjectName(QStringLiteral("pushButton_Tri"));
        pushButton_Tri->setGeometry(QRect(30, 40, 75, 23));
        pushButton_Tmp = new QPushButton(Target2PltDlg);
        pushButton_Tmp->setObjectName(QStringLiteral("pushButton_Tmp"));
        pushButton_Tmp->setGeometry(QRect(30, 90, 75, 23));
        pushButton_OutPlt = new QPushButton(Target2PltDlg);
        pushButton_OutPlt->setObjectName(QStringLiteral("pushButton_OutPlt"));
        pushButton_OutPlt->setGeometry(QRect(30, 140, 75, 23));
        lineEdit_Tri = new QLineEdit(Target2PltDlg);
        lineEdit_Tri->setObjectName(QStringLiteral("lineEdit_Tri"));
        lineEdit_Tri->setGeometry(QRect(120, 40, 271, 20));
        lineEdit_Tmp = new QLineEdit(Target2PltDlg);
        lineEdit_Tmp->setObjectName(QStringLiteral("lineEdit_Tmp"));
        lineEdit_Tmp->setGeometry(QRect(120, 90, 271, 20));
        lineEdit_OutPlt = new QLineEdit(Target2PltDlg);
        lineEdit_OutPlt->setObjectName(QStringLiteral("lineEdit_OutPlt"));
        lineEdit_OutPlt->setGeometry(QRect(120, 140, 271, 20));
        pushButton_OK = new QPushButton(Target2PltDlg);
        pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(300, 190, 75, 23));

        retranslateUi(Target2PltDlg);
        QObject::connect(pushButton_Tri, SIGNAL(clicked()), Target2PltDlg, SLOT(slotOpenTri()));
        QObject::connect(pushButton_Tmp, SIGNAL(clicked()), Target2PltDlg, SLOT(slotOpenTmp()));
        QObject::connect(pushButton_OutPlt, SIGNAL(clicked()), Target2PltDlg, SLOT(slotOpenOutputFile()));
        QObject::connect(pushButton_OK, SIGNAL(clicked()), Target2PltDlg, SLOT(slotOK()));

        QMetaObject::connectSlotsByName(Target2PltDlg);
    } // setupUi

    void retranslateUi(QDialog *Target2PltDlg)
    {
        Target2PltDlg->setWindowTitle(QApplication::translate("Target2PltDlg", "\347\233\256\346\240\207\350\275\254plt", 0));
        pushButton_Tri->setText(QApplication::translate("Target2PltDlg", "\346\211\223\345\274\200Tri\346\226\207\344\273\266", 0));
        pushButton_Tmp->setText(QApplication::translate("Target2PltDlg", "\346\211\223\345\274\200Tmp\346\226\207\344\273\266", 0));
        pushButton_OutPlt->setText(QApplication::translate("Target2PltDlg", "\351\200\211\346\213\251\350\276\223\345\207\272\350\267\257\345\276\204", 0));
        pushButton_OK->setText(QApplication::translate("Target2PltDlg", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class Target2PltDlg: public Ui_Target2PltDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARGET2PLTDLG_H
