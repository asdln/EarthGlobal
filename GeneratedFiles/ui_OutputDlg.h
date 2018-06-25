/********************************************************************************
** Form generated from reading UI file 'OutputDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTPUTDLG_H
#define UI_OUTPUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutputDlg
{
public:
    QPushButton *pushButton_FilePath;
    QLineEdit *lineEdit_OutputPath;
    QPushButton *pushButton_Open;
    QGroupBox *groupBox;
    QRadioButton *radioButton_Right;
    QRadioButton *radioButton_Left;
    QCheckBox *checkBox_OutputFloat;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QComboBox *comboBox_OutputLevel;
    QLabel *label;
    QPushButton *pushButton_Look;

    void setupUi(QWidget *OutputDlg)
    {
        if (OutputDlg->objectName().isEmpty())
            OutputDlg->setObjectName(QStringLiteral("OutputDlg"));
        OutputDlg->resize(390, 195);
        pushButton_FilePath = new QPushButton(OutputDlg);
        pushButton_FilePath->setObjectName(QStringLiteral("pushButton_FilePath"));
        pushButton_FilePath->setGeometry(QRect(20, 30, 75, 23));
        lineEdit_OutputPath = new QLineEdit(OutputDlg);
        lineEdit_OutputPath->setObjectName(QStringLiteral("lineEdit_OutputPath"));
        lineEdit_OutputPath->setGeometry(QRect(110, 30, 261, 20));
        pushButton_Open = new QPushButton(OutputDlg);
        pushButton_Open->setObjectName(QStringLiteral("pushButton_Open"));
        pushButton_Open->setGeometry(QRect(30, 150, 91, 23));
        groupBox = new QGroupBox(OutputDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(200, 60, 120, 80));
        radioButton_Right = new QRadioButton(groupBox);
        radioButton_Right->setObjectName(QStringLiteral("radioButton_Right"));
        radioButton_Right->setGeometry(QRect(10, 50, 89, 16));
        radioButton_Left = new QRadioButton(groupBox);
        radioButton_Left->setObjectName(QStringLiteral("radioButton_Left"));
        radioButton_Left->setGeometry(QRect(10, 20, 89, 16));
        checkBox_OutputFloat = new QCheckBox(OutputDlg);
        checkBox_OutputFloat->setObjectName(QStringLiteral("checkBox_OutputFloat"));
        checkBox_OutputFloat->setGeometry(QRect(30, 70, 111, 16));
        layoutWidget = new QWidget(OutputDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 100, 107, 22));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        comboBox_OutputLevel = new QComboBox(layoutWidget);
        comboBox_OutputLevel->setObjectName(QStringLiteral("comboBox_OutputLevel"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox_OutputLevel);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        pushButton_Look = new QPushButton(OutputDlg);
        pushButton_Look->setObjectName(QStringLiteral("pushButton_Look"));
        pushButton_Look->setGeometry(QRect(140, 150, 75, 23));
        layoutWidget->raise();
        pushButton_FilePath->raise();
        lineEdit_OutputPath->raise();
        pushButton_Open->raise();
        groupBox->raise();
        checkBox_OutputFloat->raise();
        pushButton_Look->raise();

        retranslateUi(OutputDlg);
        QObject::connect(pushButton_FilePath, SIGNAL(clicked()), OutputDlg, SLOT(slotSetPath()));
        QObject::connect(pushButton_Open, SIGNAL(clicked()), OutputDlg, SLOT(slotShowLastPic()));
        QObject::connect(comboBox_OutputLevel, SIGNAL(currentIndexChanged(int)), OutputDlg, SLOT(slotOutputLevel(int)));
        QObject::connect(radioButton_Left, SIGNAL(clicked()), OutputDlg, SLOT(slotLeftAliment()));
        QObject::connect(radioButton_Right, SIGNAL(clicked()), OutputDlg, SLOT(slotRightAliment()));
        QObject::connect(checkBox_OutputFloat, SIGNAL(clicked(bool)), OutputDlg, SLOT(slotOutputFloat(bool)));
        QObject::connect(pushButton_Look, SIGNAL(clicked()), OutputDlg, SLOT(slotSelectAndOpen()));

        QMetaObject::connectSlotsByName(OutputDlg);
    } // setupUi

    void retranslateUi(QWidget *OutputDlg)
    {
        OutputDlg->setWindowTitle(QApplication::translate("OutputDlg", "\345\257\274\345\207\272\345\233\276\347\211\207", 0));
        pushButton_FilePath->setText(QApplication::translate("OutputDlg", "\350\256\276\347\275\256\350\267\257\345\276\204", 0));
        pushButton_Open->setText(QApplication::translate("OutputDlg", "\346\265\217\350\247\210\346\234\200\350\277\221\344\270\200\345\274\240", 0));
        groupBox->setTitle(QApplication::translate("OutputDlg", "\345\257\271\351\275\220\346\226\271\345\274\217", 0));
        radioButton_Right->setText(QApplication::translate("OutputDlg", "\345\217\263\345\257\271\351\275\220", 0));
        radioButton_Left->setText(QApplication::translate("OutputDlg", "\345\267\246\345\257\271\351\275\220", 0));
        checkBox_OutputFloat->setText(QApplication::translate("OutputDlg", "\350\276\223\345\207\272\346\265\256\347\202\271\345\236\213\346\226\207\344\273\266", 0));
        comboBox_OutputLevel->clear();
        comboBox_OutputLevel->insertItems(0, QStringList()
         << QApplication::translate("OutputDlg", "8", 0)
         << QApplication::translate("OutputDlg", "10", 0)
         << QApplication::translate("OutputDlg", "12", 0)
         << QApplication::translate("OutputDlg", "14", 0)
         << QApplication::translate("OutputDlg", "16", 0)
        );
        label->setText(QApplication::translate("OutputDlg", "\351\207\217\345\214\226\347\255\211\347\272\247: ", 0));
        pushButton_Look->setText(QApplication::translate("OutputDlg", "\346\265\217\350\247\210", 0));
    } // retranslateUi

};

namespace Ui {
    class OutputDlg: public Ui_OutputDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTPUTDLG_H
