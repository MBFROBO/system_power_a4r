#include "form_debug.h"
#include "ui_form_debug.h"

Form_debug::Form_debug(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_debug)
{
    ui->setupUi(this);
}

Form_debug::~Form_debug()
{
    delete ui;

}

void Form_debug::on_PverticalSlider_sliderMoved(int position)
{

    ui->Pcurent_state->setText(QString::number(position));
}

void Form_debug::setP1VerticalRange(int P1max, int P1min, int Cur_P) {
    ui->PverticalSlider->setRange(P1min, P1max);
    ui->PverticalSlider->setValue(Cur_P);
}
void Form_debug::setP2VerticalRange(int P2max, int P2min, int Cur_P) {
    ui->PverticalSlider_2->setRange(P2min, P2max);
    ui->PverticalSlider_2->setValue(Cur_P);
}
void Form_debug::setP3VerticalRange(int P3max, int P3min, int Cur_P) {
    ui->PverticalSlider_3->setRange(P3min, P3max);
    ui->PverticalSlider_3->setValue(Cur_P);
}
void Form_debug::setP4VerticalRange(int P4max, int  P4min, int Cur_P) {
    ui->PverticalSlider_4->setRange(P4min, P4max);
    ui->PverticalSlider_4->setValue(Cur_P);
}

void Form_debug::on_PverticalSlider_2_sliderMoved(int position)
{
    ui->Pcurent_state_2->setText(QString::number(position));
}


void Form_debug::on_PverticalSlider_3_sliderMoved(int position)
{
    ui->Pcurent_state_3->setText(QString::number(position));
}


void Form_debug::on_PverticalSlider_4_sliderMoved(int position)
{
    ui->Pcurent_state_4->setText(QString::number(position));
}

