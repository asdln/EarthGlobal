/********************************************************************************
** Form generated from reading UI file 'DirectManipulatorDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRECTMANIPULATORDLG_H
#define UI_DIRECTMANIPULATORDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DirectManipulatorDlg
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_EyeLon;
    QLineEdit *lineEdit_EyeLat;
    QLineEdit *lineEdit_EyeHei;
    QLineEdit *lineEdit_Angle;
    QLineEdit *lineEdit_TargetLon;
    QLineEdit *lineEdit_TargetLat;
    QLineEdit *lineEdit_TargetHei;
    QPushButton *pushButton_Set;
    QPushButton *pushButton_Revert;

    void setupUi(QWidget *DirectManipulatorDlg)
    {
        if (DirectManipulatorDlg->objectName().isEmpty())
            DirectManipulatorDlg->setObjectName(QStringLiteral("DirectManipulatorDlg"));
        DirectManipulatorDlg->resize(273, 275);
        gridLayoutWidget = new QWidget(DirectManipulatorDlg);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 221, 191));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        lineEdit_EyeLon = new QLineEdit(gridLayoutWidget);
        lineEdit_EyeLon->setObjectName(QStringLiteral("lineEdit_EyeLon"));

        gridLayout->addWidget(lineEdit_EyeLon, 0, 1, 1, 1);

        lineEdit_EyeLat = new QLineEdit(gridLayoutWidget);
        lineEdit_EyeLat->setObjectName(QStringLiteral("lineEdit_EyeLat"));

        gridLayout->addWidget(lineEdit_EyeLat, 1, 1, 1, 1);

        lineEdit_EyeHei = new QLineEdit(gridLayoutWidget);
        lineEdit_EyeHei->setObjectName(QStringLiteral("lineEdit_EyeHei"));

        gridLayout->addWidget(lineEdit_EyeHei, 2, 1, 1, 1);

        lineEdit_Angle = new QLineEdit(gridLayoutWidget);
        lineEdit_Angle->setObjectName(QStringLiteral("lineEdit_Angle"));

        gridLayout->addWidget(lineEdit_Angle, 3, 1, 1, 1);

        lineEdit_TargetLon = new QLineEdit(gridLayoutWidget);
        lineEdit_TargetLon->setObjectName(QStringLiteral("lineEdit_TargetLon"));

        gridLayout->addWidget(lineEdit_TargetLon, 4, 1, 1, 1);

        lineEdit_TargetLat = new QLineEdit(gridLayoutWidget);
        lineEdit_TargetLat->setObjectName(QStringLiteral("lineEdit_TargetLat"));

        gridLayout->addWidget(lineEdit_TargetLat, 5, 1, 1, 1);

        lineEdit_TargetHei = new QLineEdit(gridLayoutWidget);
        lineEdit_TargetHei->setObjectName(QStringLiteral("lineEdit_TargetHei"));

        gridLayout->addWidget(lineEdit_TargetHei, 6, 1, 1, 1);

        pushButton_Set = new QPushButton(DirectManipulatorDlg);
        pushButton_Set->setObjectName(QStringLiteral("pushButton_Set"));
        pushButton_Set->setGeometry(QRect(30, 230, 75, 23));
        pushButton_Revert = new QPushButton(DirectManipulatorDlg);
        pushButton_Revert->setObjectName(QStringLiteral("pushButton_Revert"));
        pushButton_Revert->setGeometry(QRect(150, 230, 75, 23));

        retranslateUi(DirectManipulatorDlg);

        QMetaObject::connectSlotsByName(DirectManipulatorDlg);
    } // setupUi

    void retranslateUi(QWidget *DirectManipulatorDlg)
    {
        DirectManipulatorDlg->setWindowTitle(QApplication::translate("DirectManipulatorDlg", "DirectManipulatorDlg", 0));
        label->setText(QApplication::translate("DirectManipulatorDlg", "\350\247\206\347\202\271\347\273\217\345\272\246", 0));
        label_2->setText(QApplication::translate("DirectManipulatorDlg", "\350\247\206\347\202\271\347\272\254\345\272\246", 0));
        label_3->setText(QApplication::translate("DirectManipulatorDlg", "\350\247\206\347\202\271\351\253\230\345\272\246", 0));
        label_7->setText(QApplication::translate("DirectManipulatorDlg", "\346\227\213\350\275\254\350\247\222\345\272\246", 0));
        label_4->setText(QApplication::translate("DirectManipulatorDlg", "\347\233\256\346\240\207\347\273\217\345\272\246", 0));
        label_5->setText(QApplication::translate("DirectManipulatorDlg", "\347\233\256\346\240\207\347\272\254\345\272\246", 0));
        label_6->setText(QApplication::translate("DirectManipulatorDlg", "\347\233\256\346\240\207\351\253\230\345\272\246", 0));
        pushButton_Set->setText(QApplication::translate("DirectManipulatorDlg", "\350\256\276\347\275\256", 0));
        pushButton_Revert->setText(QApplication::translate("DirectManipulatorDlg", "\346\201\242\345\244\215", 0));
    } // retranslateUi

};

namespace Ui {
    class DirectManipulatorDlg: public Ui_DirectManipulatorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRECTMANIPULATORDLG_H
