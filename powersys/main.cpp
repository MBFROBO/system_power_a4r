#include "mainwindow.h"
#include "new_plain.h"
#include "form.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.graph->axisX()->setAutoAdjustRange(true);
    w.graph->axisY()->setAutoAdjustRange(true);
    w.graph->axisZ()->setAutoAdjustRange(true);


    QWidget *container = QWidget::createWindowContainer(w.graph);
    QSize screenSize = w.graph->screen()->size();
    container->setMinimumSize(QSize(781, 641));
    container->setMaximumSize(screenSize);

    QWidget *widget = new QWidget(&w);
    widget->setGeometry(0,10,781, 641);
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);
    w._SetupUi(&w);
    w.show();
    return a.exec();
}
