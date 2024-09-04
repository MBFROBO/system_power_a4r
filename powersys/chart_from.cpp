#include "chart_from.h"
#include "ui_chart_from.h"

chart_from::chart_from(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart_from)
{
    ui->setupUi(this);
}

chart_from::~chart_from()
{
    delete ui;
}
