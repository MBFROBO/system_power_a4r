#ifndef CHART_FORM_H
#define CHART_FORM_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QChart>
#include <QSplineSeries>
#include <QChartView>
#include <QValueAxis>

namespace Ui {
class chart_form;
}

class chart_form : public QWidget
{
    Q_OBJECT

public:
    explicit chart_form(QWidget *parent = nullptr);
    ~chart_form();

    QChart *chart_power1;
    QChart *chart_power2;
    QChart *chart_delta1;
    QChart *chart_delta2;
    QChart *chart_power_delta1;
    QChart *chart_power_delta2;


    QSplineSeries *series_power1;
    QSplineSeries *series_power2;
    QSplineSeries *series_delta1;
    QSplineSeries *series_delta2;
    QSplineSeries *series_power_delta1;
    QSplineSeries *series_power_delta2;

    QChartView *chart_power_view1;
    QChartView *chart_power_view2;
    QChartView *chart_delta_view1;
    QChartView *chart_delta_view2;
    QChartView * chart_delta_power_view1;
    QChartView * chart_delta_power_view2;

    QList<QPointF> generator_power_data_1;
    QList<QPointF> generator_power_data_2;
    QList<QPointF> generator_delta_data_1;
    QList<QPointF> generator_delta_data_2;
    QList<QPointF> generator_power_delta_data_1;
    QList<QPointF> generator_power_delta_data_2;

    QValueAxis *power_delta_1_axisX;
    QValueAxis *power_delta_1_axisY;
    QValueAxis *power_delta_2_axisX;
    QValueAxis *power_delta_2_axisY;

    QValueAxis *power1_axisX;
    QValueAxis *power1_axisY;
    QValueAxis *power2_axisY;
    QValueAxis *power2_axisX;
    QValueAxis *delta1_axisX;
    QValueAxis *delta1_axisY;
    QValueAxis *delta2_axisX;
    QValueAxis *delta2_axisY;


private:
    Ui::chart_form *ui;
};

#endif // CHART_FORM_H
