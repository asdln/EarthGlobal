/********************************************************************************
** Form generated from reading UI file 'TargetPosition.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARGETPOSITION_H
#define UI_TARGETPOSITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TargetPosition
{
public:
    QPushButton *pushButton_Set;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_Lon;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_Hei;
    QLabel *label_6;
    QLineEdit *lineEdit_Lat;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_AngleX;
    QLineEdit *lineEdit_AngleY;
    QLineEdit *lineEdit_AngleZ;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QWidget *TargetPosition)
    {
        if (TargetPosition->objectName().isEmpty())
            TargetPosition->setObjectName(QStringLiteral("TargetPosition"));
        TargetPosition->resize(242, 267);
        pushButton_Set = new QPushButton(TargetPosition);
        pushButton_Set->setObjectName(QStringLiteral("pushButton_Set"));
        pushButton_Set->setGeometry(QRect(150, 240, 75, 23));
        groupBox = new QGroupBox(TargetPosition);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 221, 111));
        lineEdit_Lon = new QLineEdit(groupBox);
        lineEdit_Lon->setObjectName(QStringLiteral("lineEdit_Lon"));
        lineEdit_Lon->setGeometry(QRect(70, 20, 113, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 20, 54, 12));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(190, 50, 54, 12));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 54, 12));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 54, 12));
        lineEdit_Hei = new QLineEdit(groupBox);
        lineEdit_Hei->setObjectName(QStringLiteral("lineEdit_Hei"));
        lineEdit_Hei->setGeometry(QRect(70, 80, 113, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(190, 80, 54, 12));
        lineEdit_Lat = new QLineEdit(groupBox);
        lineEdit_Lat->setObjectName(QStringLiteral("lineEdit_Lat"));
        lineEdit_Lat->setGeometry(QRect(70, 50, 113, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 80, 54, 12));
        groupBox_2 = new QGroupBox(TargetPosition);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 221, 111));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 20, 54, 20));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 50, 54, 12));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 80, 54, 16));
        lineEdit_AngleX = new QLineEdit(groupBox_2);
        lineEdit_AngleX->setObjectName(QStringLiteral("lineEdit_AngleX"));
        lineEdit_AngleX->setGeometry(QRect(70, 20, 113, 20));
        lineEdit_AngleY = new QLineEdit(groupBox_2);
        lineEdit_AngleY->setObjectName(QStringLiteral("lineEdit_AngleY"));
        lineEdit_AngleY->setGeometry(QRect(70, 50, 113, 20));
        lineEdit_AngleZ = new QLineEdit(groupBox_2);
        lineEdit_AngleZ->setObjectName(QStringLiteral("lineEdit_AngleZ"));
        lineEdit_AngleZ->setGeometry(QRect(70, 80, 113, 20));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(190, 20, 54, 16));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(190, 50, 54, 16));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(190, 80, 54, 16));

        retranslateUi(TargetPosition);
        QObject::connect(pushButton_Set, SIGNAL(clicked()), TargetPosition, SLOT(slotSetNewPosition()));

        QMetaObject::connectSlotsByName(TargetPosition);
    } // setupUi

    void retranslateUi(QWidget *TargetPosition)
    {
        TargetPosition->setWindowTitle(QApplication::translate("TargetPosition", "\347\233\256\346\240\207\345\247\277\346\200\201", 0));
        pushButton_Set->setText(QApplication::translate("TargetPosition", "\350\256\276\344\270\272\346\226\260\344\275\215\347\275\256", 0));
        groupBox->setTitle(QApplication::translate("TargetPosition", "\344\275\215\347\275\256", 0));
        label_4->setText(QApplication::translate("TargetPosition", "\345\272\246", 0));
        label_5->setText(QApplication::translate("TargetPosition", "\345\272\246", 0));
        label->setText(QApplication::translate("TargetPosition", "\347\273\217\345\272\246\357\274\232", 0));
        label_2->setText(QApplication::translate("TargetPosition", "\347\272\254\345\272\246\357\274\232", 0));
        label_6->setText(QApplication::translate("TargetPosition", "\347\261\263", 0));
        label_3->setText(QApplication::translate("TargetPosition", "\351\253\230\345\272\246\357\274\232", 0));
        groupBox_2->setTitle(QApplication::translate("TargetPosition", "\350\247\222\345\272\246(\346\254\247\346\213\211\350\247\222)", 0));
        label_7->setText(QApplication::translate("TargetPosition", "x \350\275\264\357\274\232", 0));
        label_8->setText(QApplication::translate("TargetPosition", "y \350\275\264\357\274\232", 0));
        label_9->setText(QApplication::translate("TargetPosition", "z \350\275\264\357\274\232", 0));
        label_10->setText(QApplication::translate("TargetPosition", "\345\272\246", 0));
        label_11->setText(QApplication::translate("TargetPosition", "\345\272\246", 0));
        label_12->setText(QApplication::translate("TargetPosition", "\345\272\246", 0));
    } // retranslateUi

};

namespace Ui {
    class TargetPosition: public Ui_TargetPosition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARGETPOSITION_H
