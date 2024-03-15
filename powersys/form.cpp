#include "form.h"
#include "ui_form.h"
#include <QString>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::change_regim_label(QString text_label) {
    ui->label_2->setText(text_label);
}


void Form::on_pushButton_2_released()
{
    Form::close();
}


void Form::on_pushButton_released()
{
    t_vozm = ui->lineEdit->text().toDouble();
    power_of_knot = ui->lineEdit_2->text().toDouble();
    knot_number = ui->comboBox->currentText().toInt();

    volume_specqueue = ui->lineEdit_3->text().toDouble();
    t_srab_que = ui->lineEdit_4->text().toDouble();
    f_srab_que = ui->lineEdit_5->text().toDouble();

    f_main_queue_step = ui->lineEdit_6->text().toDouble();
    t_main_queue_step = ui->lineEdit_7->text().toDouble();

    Form::close();
}

