/********************************************************************************
** Form generated from reading UI file 'TransDataToRadioDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSDATATORADIODLG_H
#define UI_TRANSDATATORADIODLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransDataToRadioDlg
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_TempFile;
    QLabel *label_5;
    QLineEdit *lineEdit_Output;
    QLineEdit *lineEdit_TransRatio;
    QLabel *label_3;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox_StartWave;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_EndWave;
    QLabel *label_4;
    QPushButton *pushButton_Temp;
    QPushButton *pushButton_TransRatio;
    QPushButton *pushButton_Output;
    QPushButton *pushButton_Do;
    QLabel *label_Progress;

    void setupUi(QDialog *TransDataToRadioDlg)
    {
        if (TransDataToRadioDlg->objectName().isEmpty())
            TransDataToRadioDlg->setObjectName(QStringLiteral("TransDataToRadioDlg"));
        TransDataToRadioDlg->resize(410, 254);
        gridLayoutWidget = new QWidget(TransDataToRadioDlg);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 361, 162));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        lineEdit_TempFile = new QLineEdit(gridLayoutWidget);
        lineEdit_TempFile->setObjectName(QStringLiteral("lineEdit_TempFile"));

        gridLayout->addWidget(lineEdit_TempFile, 0, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        lineEdit_Output = new QLineEdit(gridLayoutWidget);
        lineEdit_Output->setObjectName(QStringLiteral("lineEdit_Output"));

        gridLayout->addWidget(lineEdit_Output, 2, 1, 1, 1);

        lineEdit_TransRatio = new QLineEdit(gridLayoutWidget);
        lineEdit_TransRatio->setObjectName(QStringLiteral("lineEdit_TransRatio"));

        gridLayout->addWidget(lineEdit_TransRatio, 1, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 2, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        doubleSpinBox_StartWave = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_StartWave->setObjectName(QStringLiteral("doubleSpinBox_StartWave"));

        gridLayout->addWidget(doubleSpinBox_StartWave, 3, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        doubleSpinBox_EndWave = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_EndWave->setObjectName(QStringLiteral("doubleSpinBox_EndWave"));

        gridLayout->addWidget(doubleSpinBox_EndWave, 4, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 2, 1, 1);

        pushButton_Temp = new QPushButton(gridLayoutWidget);
        pushButton_Temp->setObjectName(QStringLiteral("pushButton_Temp"));

        gridLayout->addWidget(pushButton_Temp, 0, 2, 1, 1);

        pushButton_TransRatio = new QPushButton(gridLayoutWidget);
        pushButton_TransRatio->setObjectName(QStringLiteral("pushButton_TransRatio"));

        gridLayout->addWidget(pushButton_TransRatio, 1, 2, 1, 1);

        pushButton_Output = new QPushButton(gridLayoutWidget);
        pushButton_Output->setObjectName(QStringLiteral("pushButton_Output"));

        gridLayout->addWidget(pushButton_Output, 2, 2, 1, 1);

        pushButton_Do = new QPushButton(TransDataToRadioDlg);
        pushButton_Do->setObjectName(QStringLiteral("pushButton_Do"));
        pushButton_Do->setGeometry(QRect(290, 210, 75, 23));
        label_Progress = new QLabel(TransDataToRadioDlg);
        label_Progress->setObjectName(QStringLiteral("label_Progress"));
        label_Progress->setGeometry(QRect(50, 210, 54, 12));

        retranslateUi(TransDataToRadioDlg);

        QMetaObject::connectSlotsByName(TransDataToRadioDlg);
    } // setupUi

    void retranslateUi(QDialog *TransDataToRadioDlg)
    {
        TransDataToRadioDlg->setWindowTitle(QApplication::translate("TransDataToRadioDlg", "TransDataToRadioDlg", 0));
        label_6->setText(QApplication::translate("TransDataToRadioDlg", "\345\217\221\345\260\204\347\216\207\346\226\207\344\273\266\357\274\232", 0));
        label_7->setText(QApplication::translate("TransDataToRadioDlg", "\350\276\223\345\207\272\346\226\207\344\273\266\357\274\232", 0));
        label_5->setText(QApplication::translate("TransDataToRadioDlg", "\346\270\251\345\272\246\346\226\207\344\273\266\357\274\232", 0));
        label_3->setText(QApplication::translate("TransDataToRadioDlg", "um", 0));
        label->setText(QApplication::translate("TransDataToRadioDlg", "\350\265\267\345\247\213\346\263\242\351\225\277\357\274\232", 0));
        label_2->setText(QApplication::translate("TransDataToRadioDlg", "\347\273\210\346\255\242\346\263\242\351\225\277\357\274\232", 0));
        label_4->setText(QApplication::translate("TransDataToRadioDlg", "um", 0));
        pushButton_Temp->setText(QApplication::translate("TransDataToRadioDlg", "\351\200\211\346\213\251", 0));
        pushButton_TransRatio->setText(QApplication::translate("TransDataToRadioDlg", "\351\200\211\346\213\251", 0));
        pushButton_Output->setText(QApplication::translate("TransDataToRadioDlg", "\351\200\211\346\213\251", 0));
        pushButton_Do->setText(QApplication::translate("TransDataToRadioDlg", "\346\211\247\350\241\214", 0));
        label_Progress->setText(QApplication::translate("TransDataToRadioDlg", "\350\277\233\345\272\246: 0%", 0));
    } // retranslateUi

};

namespace Ui {
    class TransDataToRadioDlg: public Ui_TransDataToRadioDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSDATATORADIODLG_H
