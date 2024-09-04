#include "chart_form.h"
#include "ui_chart_form.h"

chart_form::chart_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart_form)
{

    power1_axisX = new QValueAxis;
    power1_axisX->setTitleText("t, c");
    power1_axisX->setLabelFormat("%.2f");
    power1_axisX->setTickCount(0.01);

    power1_axisY = new QValueAxis;
    power1_axisY->setTitleText("P, о.е");
    power1_axisY->setLabelFormat("%.2f");
    power1_axisY->setTickCount(0.01);

    power2_axisX = new QValueAxis;
    power2_axisX->setTitleText("t, c");
    power2_axisX->setLabelFormat("%.2f");
    power2_axisX->setTickCount(0.01);

    power2_axisY = new QValueAxis;
    power2_axisY->setTitleText("P, о.е");
    power2_axisY->setLabelFormat("%.2f");
    power2_axisY->setTickCount(0.01);

    delta1_axisX = new QValueAxis;
    delta1_axisX->setTitleText("t, c");
    delta1_axisX->setLabelFormat("%.2f");
    delta1_axisX->setTickCount(0.01);

    delta1_axisY = new QValueAxis;
    delta1_axisY->setTitleText("\u03B4, град");
    delta1_axisY->setLabelFormat("%.2f");
    delta1_axisY->setTickCount(0.01);

    delta2_axisX = new QValueAxis;
    delta2_axisX->setTitleText("t, c");
    delta2_axisX->setLabelFormat("%.2f");
    delta2_axisX->setTickCount(0.01);

    delta2_axisY = new QValueAxis;
    delta2_axisY->setTitleText("\u03B4, град");
    delta2_axisY->setLabelFormat("%.2f");
    delta2_axisY->setTickCount(0.01);

    power_delta_1_axisX = new QValueAxis;
    power_delta_1_axisX->setTitleText("\u03B4, град");
    power_delta_1_axisX->setLabelFormat("%.2f");
    power_delta_1_axisX->setTickCount(0.01);

    power_delta_1_axisY = new QValueAxis;
    power_delta_1_axisY->setTitleText("Pэм, о.е");
    power_delta_1_axisY->setLabelFormat("%.2f");
    power_delta_1_axisY->setTickCount(0.01);

    power_delta_2_axisX = new QValueAxis;
    power_delta_2_axisX->setTitleText("\u03B4, град");
    power_delta_2_axisX->setLabelFormat("%.2f");
    power_delta_2_axisX->setTickCount(0.01);

    power_delta_2_axisY = new QValueAxis;
    power_delta_2_axisY->setTitleText("Pэм, о.е");
    power_delta_2_axisY->setLabelFormat("%.2f");
    power_delta_2_axisY->setTickCount(0.01);



    series_power1 = new QSplineSeries();
    series_power2 = new QSplineSeries();
    series_delta1 = new QSplineSeries();
    series_delta2 = new QSplineSeries();
    series_power_delta1 = new QSplineSeries();
    series_power_delta2 = new QSplineSeries();

    chart_power_delta1 = new QChart();
    chart_power_delta1->setMargins(QMargins(2,2,2,2));
    chart_power_delta1->setTitle("Годограф мощности - угла дельта Г1");
    chart_power_delta1->legend()->hide();
    chart_power_delta1->setAxisX(power_delta_1_axisX);
    chart_power_delta1->setAxisY(power_delta_1_axisY);

    chart_power_delta2 = new QChart();
    chart_power_delta2->setMargins(QMargins(2,2,2,2));
    chart_power_delta2->setTitle("Годограф мощности - угла дельта Г2");
    chart_power_delta2->legend()->hide();
    chart_power_delta2->setAxisX(power_delta_2_axisX);
    chart_power_delta2->setAxisY(power_delta_2_axisY);

    chart_power1 = new QChart();
    chart_power1->setMargins(QMargins(2,2,2,2));
    chart_power1->setTitle("Мощность генератора 1");
    chart_power1->legend()->hide();
    chart_power1->setAxisX(power1_axisX);
    chart_power1->setAxisY(power1_axisY);


    chart_power2 = new QChart();
    chart_power2->legend()->hide();
    chart_power2->setMargins(QMargins(2,2,2,2));
    chart_power2->setTitle("Мощность генератора 2");
    chart_power2->setAxisX(power2_axisX);
    chart_power2->setAxisY(power2_axisY);


    chart_delta1 = new QChart();
    chart_delta1->legend()->hide();
    chart_delta1->setMargins(QMargins(2,2,2,2));
    chart_delta1->setTitle("Угол Передачи генератора 1");
    chart_delta1->setAxisX(delta1_axisX);
    chart_delta1->setAxisY(delta1_axisY);

    chart_delta2 = new QChart();
    chart_delta2->legend()->hide();
    chart_delta2->setMargins(QMargins(2,2,2,2));
    chart_delta2->setTitle("Угол передачи генератора 2");
    chart_delta2->setAxisX(delta2_axisX);
    chart_delta2->setAxisY(delta2_axisY);

    chart_power_view1 = new QChartView(chart_power1,this);
    chart_power_view1->setRenderHint(QPainter::Antialiasing);
    chart_power_view1->setGeometry(QRect(20, 40, 1001, 221));
    chart_power_view1->setRubberBand(QChartView::VerticalRubberBand);

    chart_power_view2 = new QChartView(chart_power2,this);
    chart_power_view2->setRenderHint(QPainter::Antialiasing);
    chart_power_view2->setGeometry(QRect(20, 480, 1001, 221));
    chart_power_view2->setRubberBand(QChartView::VerticalRubberBand);

    chart_delta_view1 = new QChartView(chart_delta1,this);
    chart_delta_view1->setRenderHint(QPainter::Antialiasing);
    chart_delta_view1->setGeometry(QRect(20, 260, 1001, 221));
    chart_delta_view1->setRubberBand(QChartView::VerticalRubberBand);

    chart_delta_view2 = new QChartView(chart_delta2,this);
    chart_delta_view2->setRenderHint(QPainter::Antialiasing);
    chart_delta_view2->setGeometry(QRect(20, 700, 1001, 221));
    chart_delta_view2->setRubberBand(QChartView::VerticalRubberBand);

    chart_delta_power_view1 = new QChartView(chart_power_delta1,this);
    chart_delta_power_view1->setRenderHint(QPainter::Antialiasing);
    chart_delta_power_view1->setGeometry(QRect(1020, 40, 530, 440));
    chart_delta_power_view1->setRubberBand(QChartView::HorizontalRubberBand);

    chart_delta_power_view2 = new QChartView(chart_power_delta2,this);
    chart_delta_power_view2->setRenderHint(QPainter::Antialiasing);
    chart_delta_power_view2->setGeometry(QRect(1020, 480, 530, 440));
    chart_delta_power_view2->setRubberBand(QChartView::HorizontalRubberBand);

    ui->setupUi(this);

}

chart_form::~chart_form()
{
    delete ui;
}
