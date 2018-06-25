/********************************************************************************
** Form generated from reading UI file 'AnimationSettingsDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATIONSETTINGSDLG_H
#define UI_ANIMATIONSETTINGSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AnimationSettingsDlg
{
public:
    QPushButton *pushButton_SetPath;
    QLineEdit *lineEdit_Path;

    void setupUi(QDialog *AnimationSettingsDlg)
    {
        if (AnimationSettingsDlg->objectName().isEmpty())
            AnimationSettingsDlg->setObjectName(QStringLiteral("AnimationSettingsDlg"));
        AnimationSettingsDlg->resize(366, 219);
        pushButton_SetPath = new QPushButton(AnimationSettingsDlg);
        pushButton_SetPath->setObjectName(QStringLiteral("pushButton_SetPath"));
        pushButton_SetPath->setGeometry(QRect(20, 20, 81, 23));
        lineEdit_Path = new QLineEdit(AnimationSettingsDlg);
        lineEdit_Path->setObjectName(QStringLiteral("lineEdit_Path"));
        lineEdit_Path->setGeometry(QRect(120, 20, 231, 20));
        lineEdit_Path->setReadOnly(true);

        retranslateUi(AnimationSettingsDlg);
        QObject::connect(pushButton_SetPath, SIGNAL(clicked()), AnimationSettingsDlg, SLOT(slotSetSavePath()));

        QMetaObject::connectSlotsByName(AnimationSettingsDlg);
    } // setupUi

    void retranslateUi(QDialog *AnimationSettingsDlg)
    {
        AnimationSettingsDlg->setWindowTitle(QApplication::translate("AnimationSettingsDlg", "AnimationSettingsDlg", 0));
        pushButton_SetPath->setText(QApplication::translate("AnimationSettingsDlg", "\350\256\276\347\275\256\344\277\235\345\255\230\350\267\257\345\276\204", 0));
    } // retranslateUi

};

namespace Ui {
    class AnimationSettingsDlg: public Ui_AnimationSettingsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONSETTINGSDLG_H
