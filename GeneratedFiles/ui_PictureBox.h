/********************************************************************************
** Form generated from reading UI file 'PictureBox.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTUREBOX_H
#define UI_PICTUREBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PictureBox
{
public:

    void setupUi(QWidget *PictureBox)
    {
        if (PictureBox->objectName().isEmpty())
            PictureBox->setObjectName(QStringLiteral("PictureBox"));
        PictureBox->resize(400, 300);

        retranslateUi(PictureBox);

        QMetaObject::connectSlotsByName(PictureBox);
    } // setupUi

    void retranslateUi(QWidget *PictureBox)
    {
        PictureBox->setWindowTitle(QApplication::translate("PictureBox", "PictureBox", 0));
    } // retranslateUi

};

namespace Ui {
    class PictureBox: public Ui_PictureBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREBOX_H
