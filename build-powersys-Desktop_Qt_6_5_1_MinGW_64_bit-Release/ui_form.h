/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QLabel *label_2;
    QFrame *line;
    QGroupBox *groupBox;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_2;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QLabel *label_9;
    QLineEdit *lineEdit_4;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEdit_5;
    QFrame *line_2;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineEdit_6;
    QLabel *label_14;
    QLineEdit *lineEdit_7;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(431, 539);
        Form->setMinimumSize(QSize(431, 539));
        Form->setMaximumSize(QSize(431, 539));
        QFont font;
        font.setPointSize(12);
        Form->setFont(font);
        label = new QLabel(Form);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 141, 31));
        label_2 = new QLabel(Form);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(180, 20, 201, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setItalic(true);
        font1.setUnderline(true);
        label_2->setFont(font1);
        line = new QFrame(Form);
        line->setObjectName("line");
        line->setGeometry(QRect(20, 50, 391, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox = new QGroupBox(Form);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 60, 371, 141));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 40, 151, 21));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(210, 40, 81, 21));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(300, 40, 49, 21));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 70, 181, 21));
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(210, 70, 81, 21));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(300, 70, 49, 21));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 100, 181, 21));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(210, 100, 81, 21));
        pushButton = new QPushButton(Form);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 490, 251, 31));
        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(290, 490, 121, 31));
        groupBox_2 = new QGroupBox(Form);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(30, 210, 371, 261));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 60, 61, 16));
        QFont font2;
        font2.setPointSize(10);
        label_8->setFont(font2);
        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(90, 60, 41, 21));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(150, 60, 151, 16));
        label_9->setFont(font2);
        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(310, 60, 41, 21));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 30, 121, 21));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 90, 161, 16));
        label_11->setFont(font2);
        lineEdit_5 = new QLineEdit(groupBox_2);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(190, 90, 41, 21));
        line_2 = new QFrame(groupBox_2);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(20, 120, 331, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 160, 111, 16));
        label_12->setFont(font2);
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(20, 130, 121, 21));
        lineEdit_6 = new QLineEdit(groupBox_2);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(130, 160, 41, 21));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(20, 190, 111, 16));
        label_14->setFont(font2);
        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(130, 190, 41, 21));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "\320\230\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262 \321\200\320\265\320\266\320\270\320\274\320\260", nullptr));
        label->setText(QCoreApplication::translate("Form", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\200\320\265\320\266\320\270\320\274\320\260:", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "\320\242\320\265\321\201\321\202\320\276\320\262\321\213\320\271", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Form", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\262\320\276\320\267\320\274\321\203\321\211\320\265\320\275\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "\320\222\321\200\320\265\320\274\321\217 \320\262\320\276\320\267\320\274\321\203\321\211\320\265\320\275\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("Form", "\321\201", nullptr));
        label_5->setText(QCoreApplication::translate("Form", "\320\234\320\276\321\211\320\275\320\276\321\201\321\202\321\214 \320\262\320\276\320\267\320\274\321\203\321\211\320\265\320\275\320\270\321\217", nullptr));
        label_6->setText(QCoreApplication::translate("Form", "\320\234\320\222\321\202", nullptr));
        label_7->setText(QCoreApplication::translate("Form", "\320\243\320\267\320\265\320\273 \320\262\320\276\320\267\320\274\321\203\321\211\320\265\320\275\320\270\321\217", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Form", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Form", "\320\243\321\201\321\202\320\260\320\262\320\272\320\270 \320\220\320\247\320\240 1", nullptr));
        label_8->setText(QCoreApplication::translate("Form", "\320\236\320\261\321\212\321\221\320\274, %", nullptr));
        label_9->setText(QCoreApplication::translate("Form", "\320\222\321\200\320\265\320\274\321\217 \321\201\321\200\320\260\320\261\320\260\321\202\320\262\321\213\320\262\320\260\320\275\320\270\321\217, \321\201", nullptr));
        label_10->setText(QCoreApplication::translate("Form", "\320\241\320\277\320\265\321\206\320\276\321\207\320\265\321\200\320\265\320\264\321\214", nullptr));
        label_11->setText(QCoreApplication::translate("Form", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \321\201\321\200\320\260\320\261\320\260\321\202\321\213\320\262\320\260\320\275\320\270\321\217, \320\223\321\206", nullptr));
        label_12->setText(QCoreApplication::translate("Form", "\320\250\320\260\320\263 \320\276\321\207\320\265\321\200\320\265\320\264\320\270, \320\223\321\206", nullptr));
        label_13->setText(QCoreApplication::translate("Form", "\320\236\321\201\320\275\320\276\320\262\320\275\320\276\320\271 \320\276\320\261\321\212\321\221\320\274", nullptr));
        label_14->setText(QCoreApplication::translate("Form", "\320\250\320\260\320\263 \320\276\321\207\320\265\321\200\320\265\320\264\320\270, \321\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
