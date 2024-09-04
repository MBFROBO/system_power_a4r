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
    knot_number = ui->comboBox->currentIndex();

    A4R1_P = ui->A4R1_P_field->text().toDouble();
    A4R1_f = ui->A4R1_f_field->text().toDouble();
    A4R1_t = ui->A4R1_t_field->text().toDouble();
    A4R1_steps_count = ui->A4R1_count_stpes->currentText().toInt();

    A4R2_P = ui->A4R2_P_field->text().toDouble();
    A4R2_t = ui->A4R2_t_field->text().toDouble();
    A4R2_steps_count = ui->A4R2_count_stpes->currentText().toInt();

    ui_debug_state = ui->checkBox->checkState();
    S_basis = ui->S_basis_field->text().toFloat();
    additional_builds_state = ui->checkBox_2->checkState();

    line_off = ui->Line_off->currentIndex();
    //! Индексы отключаемых линий
    //! 0 - Г1-Н1
    //! 1 - Н1-Н2
    //! 2 - Н2-Н3
    //! 3 - Н3-Г2
    //! 4 - Г2-Н4
    //! 5 - Н4-Г1

    line_mark = ui->Line_mark->currentIndex();
    //! Индексы марок проводов
    //! 0 - АС120/19
    //! 1 - AC240/32
    timer_P_vozvr = ui->Pvozvr->text().toFloat();
    flag_P_vozvr = ui->Pvozvr_check->checkState();
    line_fault_checked = ui->Line_fault->checkState();
    knot_fault_checked = ui->knot_fault->checkState();
    h = ui->h_field->text().toFloat();
    A4R2_vozvr_ust = ui->A4R2_vozvr_field->text().toFloat();
    Form::close();
}



