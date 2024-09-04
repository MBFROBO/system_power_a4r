#include "doc.h"
#include "ui_doc.h"

Doc::Doc(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Doc)
{
    ui->setupUi(this);
}

Doc::~Doc()
{
    delete ui;
}
