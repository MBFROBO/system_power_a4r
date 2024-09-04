#include "mainwindow.h"
#include "normal_regim.h"
#include "new_plain.h"
#include "form.h"
#include "form_debug.h"
#include "chart_form.h"
#include "doc.h"
#include <cmath>
#include<iostream>
#include<algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Params = new QPushButton(this);
    connect(Params, &QPushButton::clicked, this, &MainWindow::acceptParams);

    Pause = new QPushButton(this);
    connect(Pause, &QPushButton::clicked, this, &MainWindow::paused);
    StartSim_btn = new QPushButton(this);
    StartSim_btn->setEnabled(false);
    StartSim_btn->setToolTip("Неодходимо задать параметры системы");
    connect(StartSim_btn,  &QPushButton::clicked, this, &MainWindow::StartSim);

    pushButton = new QPushButton(this);
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::callModalWindow);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::fillSqrtSinProxy);

    generator_spline_1 = new QSplineSeries();
    generator_spline_2 = new QSplineSeries();

    generator_chart_1 = new QChart();
    generator_chart_1->setAcceptHoverEvents(true);
    generator_chart_1->setMargins(QMargins(2,2,2,2));

    axisX_gen_freq_1 = new QValueAxis;
    axisX_gen_freq_1->setTitleText("t, c");
    axisX_gen_freq_1->setLabelFormat("%.2f");
    axisX_gen_freq_1->setTickCount(0.01);

    axisY_gen_freq_1 = new QValueAxis;
    axisY_gen_freq_1->setTitleText("f, Гц");
    axisY_gen_freq_1->setLabelFormat("%.2f");
    axisY_gen_freq_1->setTickCount(0.01);

    axisX_gen_freq_2 = new QValueAxis;
    axisX_gen_freq_2->setTitleText("t, c");
    axisX_gen_freq_2->setLabelFormat("%.2f");
    axisX_gen_freq_2->setTickCount(0.01);

    axisY_gen_freq_2 = new QValueAxis;
    axisY_gen_freq_2->setTitleText("f, Гц");
    axisY_gen_freq_2->setLabelFormat("%.2f");
    axisY_gen_freq_2->setTickCount(0.01);


    AxisY_A4R_1 = new QScatterSeries;
    AxisY_A4R_1->setMarkerSize(7);

    AxisY_A4R_2 = new QScatterSeries;
    AxisY_A4R_2->setMarkerSize(7);


    AxisY_A4R_1_2 = new QScatterSeries;
    AxisY_A4R_1_2->setMarkerSize(7);

    AxisY_A4R_2_2 = new QScatterSeries;
    AxisY_A4R_2_2->setMarkerSize(7);

    generator_chart_1->setAxisX(axisX_gen_freq_1);
    generator_chart_1->setAxisY(axisY_gen_freq_1);
    generator_chart_1->legend()->hide();

    generator_chart_2 = new QChart();
    generator_chart_2->legend()->hide();
    generator_chart_2->setAcceptHoverEvents(true);
    generator_chart_2->setMargins(QMargins(2,2,2,2));
    generator_chart_2->setAxisX(axisX_gen_freq_2);
    generator_chart_2->setAxisY(axisY_gen_freq_2);

    gr = new QLinearGradient();

    generator_freq_1 = new QChartView(generator_chart_1, this);
    generator_freq_1->setRenderHint(QPainter::Antialiasing);
    generator_freq_1->setRubberBand(QChartView::VerticalRubberBand);


    generator_freq_2 = new QChartView(generator_chart_2, this);
    generator_freq_2->setRenderHint(QPainter::Antialiasing);
    generator_freq_2->setRubberBand(QChartView::VerticalRubberBand);
    comboBox = new QComboBox(this);

    comboBox->addItem("Нормальный режим");
    comboBox->addItem("Избыток мощности");
    comboBox->addItem("Недостаток мощности");


    QImage heightMapImage(":/Es.jpg");
    m_sqrtSinProxy = new QSurfaceDataProxy();
    m_sqrtSinSeries = new QSurface3DSeries(m_sqrtSinProxy);


    m_sqrtSinSeries->setTexture(heightMapImage);

    fillSqrtSinProxy();

    m_heightMapProxy = new QHeightMapSurfaceDataProxy(heightMapImage);
    m_heightMapSeries = new QSurface3DSeries(m_heightMapProxy);
    m_heightMapSeries->setItemLabelFormat(QStringLiteral("(@xLabel, @zLabel): @yLabel"));

    m_heightMapSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    m_heightMapSeries->setFlatShadingEnabled(false);

    m_heightMapWidth = heightMapImage.width();
    m_heightMapHeight = heightMapImage.height();


    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::erasing_all_arrays() {
    // Очищаем все массивы при рестарте для перестроения графиков

    while (block_gen_1.delta.count() > 0) {
        block_gen_1.delta.removeLast();
        block_gen_2.delta.removeLast();
    }

    ch_form.chart_power1->removeSeries(ch_form.series_power1);
    ch_form.chart_power2->removeSeries(ch_form.series_power2);
    ch_form.chart_delta1->removeSeries(ch_form.series_delta1);
    ch_form.chart_delta2->removeSeries(ch_form.series_delta2);
    ch_form.chart_power_delta1->removeSeries(ch_form.series_power_delta1);
    ch_form.chart_power_delta2->removeSeries(ch_form.series_power_delta2);

    while (ch_form.series_power1->count() > 0) {
        ch_form.series_power1->removePoints(0,1);
        ch_form.series_power2->removePoints(0,1);

    }

    while (ch_form.series_delta1->count() > 0) {
        ch_form.series_delta1->removePoints(0,1);
        ch_form.series_delta2->removePoints(0,1);
    }

    while (ch_form.series_power_delta1->count() > 0) {
        ch_form.series_power_delta1->removePoints(0,1);
        ch_form.series_power_delta2->removePoints(0,1);
    }

    freq_array = {50, 50};
    freq2_array = {50, 50};

    power_array = {};
    power_array_2 = {};

    time_array = {};

    fn1 = 50;
    fn2 = 50;
    fn3 = 50;
    fn4 = 50;

    delta_pn1 = 0;
    delta_pn2 = 0;
    delta_pn3 = 0;
    delta_pn4 = 0;

    generator_chart_1->removeSeries(generator_spline_1);
    generator_chart_2->removeSeries(generator_spline_2);


    while (generator_spline_1->count() > 0) {
        generator_spline_1->removePoints(0, 1);
        generator_spline_2->removePoints(0, 1);
    }

    while (newRow->length() > 0) {
        newRow->removeLast();
        newRow1->removeLast();
        newRow2->removeLast();
        newRow3->removeLast();
        newRow4->removeLast();
    }

    while (dataArray->length() > 0) {
        dataArray->removeLast();
    }

    A4R_preload.A4R1_timer = 0;
    A4R_preload.A4R2_timer = 0;
    A4R_preload.A4R1_scoper = 0;
    A4R_preload.A4R2_scoper = 0;

    A4R_preload.A4R1_timer_2 = 0;
    A4R_preload.A4R2_timer_2 = 0;
    A4R_preload.A4R1_scoper_2 = 0;
    A4R_preload.A4R2_scoper_2 = 0;


    AxisY_A4R_1->removePoints(0,    AxisY_A4R_1->count());
    AxisY_A4R_2->removePoints(0,    AxisY_A4R_2->count());
    AxisY_A4R_1_2->removePoints(0,  AxisY_A4R_1_2->count());
    AxisY_A4R_2_2->removePoints(0,  AxisY_A4R_2_2->count());
    A4R_preload.flag_once_time = false;
    A4R_preload.flag_once_time_2 = false;
    image_change = false;
    p_vozvr_once_flag = false;
}

void MainWindow::A4R1() {
    // алгоритм работы АЧР1

    if (checkBox->checkState() == Qt::Checked) {

        if (freq_array.last() <= A4R_preload.A4R1_srab && time_t - A4R_preload.A4R1_timer >= A4R_preload.A4R1_t && A4R_preload.A4R1_scoper < A4R_preload.A4R1_steps_count && (A4R_preload.A4R1_f_deriv - freq_array.last()) >= A4R_preload.A4R1_f) {
            block_gen_1.Pnagr = block_gen_1.Pnagr - A4R_preload.A4R1_P/(Sb*A4R_preload.A4R1_steps_count);

            A4R_preload.A4R1_timer = time_t;
            A4R_preload.A4R1_f_deriv = freq_array.last();
            A4R_preload.A4R1_scoper++;

            AxisY_A4R_1->setColor(Qt::red);
            AxisY_A4R_1->append(time_t,freq_array[scoper]);

            qDebug() << "Сработала АЧР1 при частоте " << freq_array[scoper] << " Отключила " << A4R_preload.A4R1_P/(Sb*A4R_preload.A4R1_steps_count) << "мощности нагрузки";
        }

        if (freq2_array.last() <= A4R_preload.A4R1_srab && time_t - A4R_preload.A4R1_timer_2 >= A4R_preload.A4R1_t && A4R_preload.A4R1_scoper_2 < A4R_preload.A4R1_steps_count && (A4R_preload.A4R1_f_deriv_2 - freq2_array.last()) >= A4R_preload.A4R1_f) {
            block_gen_2.Pnagr = block_gen_2.Pnagr - A4R_preload.A4R1_P/(Sb*A4R_preload.A4R1_steps_count);
            A4R_preload.A4R1_timer_2 = time_t;
            A4R_preload.A4R1_f_deriv_2 = freq2_array.last();
            A4R_preload.A4R1_scoper_2++;

            AxisY_A4R_1_2->setColor(Qt::red);
            AxisY_A4R_1_2->append(time_t,freq2_array[scoper]);


            qDebug() << "Сработала АЧР1 при частоте " << freq2_array[scoper] << " Отключила " << A4R_preload.A4R1_P/(Sb*A4R_preload.A4R1_steps_count) << "мощности нагрузки";
        }
    }
}

void MainWindow::A4R2() {
    // алгоритм работы АЧР2

    if (checkBox_2->checkState() == Qt::Checked) {
        if (freq_array.last() <= A4R_preload.A4R2_srab) { // АЧР1 начинает работу ( уставка АЧР2 равна АЧР1 по частоте пуска)
            if (A4R_preload.flag_once_time == false) {
                A4R_preload.A4R2_timer_fromA4R1 = time_t;
                A4R_preload.flag_once_time = true;
            }
            if (time_t - A4R_preload.A4R2_timer_fromA4R1 >= A4R_preload.A4R2_from_A4R1_time && A4R_preload.A4R2_scoper < A4R_preload.A4R2_steps_count && time_t - A4R_preload.A4R2_timer >= A4R_preload.A4R2_t) {
                block_gen_1.Pnagr = block_gen_1.Pnagr - A4R_preload.A4R2_P/(Sb*A4R_preload.A4R2_steps_count);
                A4R_preload.A4R2_timer = time_t;
                A4R_preload.A4R2_scoper++;
                A4R_preload.A4R2_srab_flag = true;
                qDebug() << "Сработала АЧР 2 ген 1";
                AxisY_A4R_2->setColor(Qt::green);
                AxisY_A4R_2->append(time_t,freq_array[scoper]);

            }
        } else {
            if (A4R_preload.A4R2_srab_flag == true && freq_array.last() <= A4R_preload.A4R2_ust_vozvr && A4R_preload.A4R2_scoper < A4R_preload.A4R2_steps_count && time_t - A4R_preload.A4R2_timer >= A4R_preload.A4R2_t) {
                block_gen_1.Pnagr = block_gen_1.Pnagr - A4R_preload.A4R2_P/(Sb*A4R_preload.A4R2_steps_count);
                A4R_preload.A4R2_timer = time_t;
                A4R_preload.A4R2_scoper++;
                A4R_preload.A4R2_srab_flag = true;
                qDebug() << "Сработала АЧР 2 ген 1";
                AxisY_A4R_2->setColor(Qt::green);
                AxisY_A4R_2->append(time_t,freq_array[scoper]);
            }
        }

        if (freq2_array.last() <= A4R_preload.A4R2_srab) { // АЧР1 начинает работу ( уставка АЧР2 равна АЧР1 по частоте пуска)
            if (A4R_preload.flag_once_time_2 == false) {
                A4R_preload.A4R2_timer_fromA4R1_2 = time_t;
                A4R_preload.flag_once_time_2 = true;
            }
            if (time_t - A4R_preload.A4R2_timer_fromA4R1_2 >= A4R_preload.A4R2_from_A4R1_time && A4R_preload.A4R2_scoper_2 < A4R_preload.A4R2_steps_count && time_t - A4R_preload.A4R2_timer_2 >= A4R_preload.A4R2_t) {
                block_gen_2.Pnagr = block_gen_2.Pnagr - A4R_preload.A4R2_P/(Sb*A4R_preload.A4R2_steps_count);
                A4R_preload.A4R2_timer_2 = time_t;
                A4R_preload.A4R2_scoper_2++;

                A4R_preload.A4R2_srab_flag_2 = true;
                qDebug() << "Сработала АЧР 2 ген 2";
                AxisY_A4R_2_2->setColor(Qt::green);
                AxisY_A4R_2_2->append(time_t,freq2_array[scoper]);

            }
        } else {

            if (A4R_preload.A4R2_srab_flag_2 == true && freq2_array.last() <= A4R_preload.A4R2_ust_vozvr &&  A4R_preload.A4R2_scoper_2 < A4R_preload.A4R2_steps_count && time_t - A4R_preload.A4R2_timer_2 >= A4R_preload.A4R2_t) {
                block_gen_2.Pnagr = block_gen_2.Pnagr - A4R_preload.A4R2_P/(Sb*A4R_preload.A4R2_steps_count);
                A4R_preload.A4R2_timer_2 = time_t;
                A4R_preload.A4R2_scoper_2++;

                A4R_preload.A4R2_srab_flag_2 = true;
                qDebug() << "Сработала АЧР 2 ген 2";
                AxisY_A4R_2_2->setColor(Qt::green);
                AxisY_A4R_2_2->append(time_t,freq2_array[scoper]);
            }
        }
    }
}

void MainWindow::power_balance() {
    //! Весь расчёт проводится в базисе, установленном в настройках
    //! в относительных величинах, согласно формулировке формулы движения ротора
    //!
    float PA  = power_array[scoper] * Sb; // уже в базисах
    float PB  = power_array_2[scoper] * Sb; // уже в базисах
    float Pn4 = block_loads.Pnom_4* Sb;
    float Pn1 = block_loads.Pnom_1* Sb;
    float Pn2 = block_loads.Pnom_2* Sb;
    float Pn3 = block_loads.Pnom_3* Sb;
    //! Расчёт веток
    float Pa4;
    float Pb4;

    float delta_pn1;
    float delta_pn2;
    float delta_pn3;
    float delta_pn4;

    if (form.line_fault_checked == false) {

        Pa4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) - LB4/LA4)*Pn4);
        Pb4 = ((LB4/LA4)*Pn4);

        if  ((PA - Pa4 - Pn1) >= 0) { delta_pn1 = 0; } else {delta_pn1 = (PA - Pa4 - Pn1);}

        if  ((PB - Pb4 - Pn3) >= 0) {delta_pn3 = 0;} else {delta_pn3 = (PB - Pb4 - Pn3);};
        delta_pn2 = (PA - Pa4 - Pn1) + (PB - Pb4 - Pn3) - Pn2;
        delta_pn4 = Pa4 + Pb4 - Pn4;

    } else {
        if (lines_fault.line_off == 0) {
            // отключеена Г1-Н1
            if (time_t > form.t_vozm) {
                Pa4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) - LB4/LA4)*Pn4);
                Pb4 = (LB4/LA4)*Pn4;
            }
        }

        if (lines_fault.line_off == 1) {
            // отключена Н1-Н2
            if (time_t > form.t_vozm) {
                Pa4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) - LB4/LA4)*Pn4);
                Pb4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) * LB4/LA4)*Pn4);
            }
        }
        if (lines_fault.line_off == 2) {
            // отключена Н2-Н3
            if (time_t > form.t_vozm) {

                Pa4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) - LB4/LA4)*Pn4);
                Pb4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) * LB4/LA4)*Pn4);
            }

        }

        if (lines_fault.line_off == 3) {
            // отключена Н3-Г2
            if (time_t > form.t_vozm) {
                Pa4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) - LB4/LA4)*Pn4);
                Pb4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) * LB4/LA4)*Pn4);
            }
        }

        if (lines_fault.line_off == 4) {
            // отключена Г2-Н4
            if (time_t > form.t_vozm) {
                Pa4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) - LB4/LA4)*Pn4);
                Pb4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) * LB4/LA4)*Pn4);
            }

        }

        if (lines_fault.line_off == 5) {
            // отключена Н4-Г1
            if (time_t > form.t_vozm) {
                Pa4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) - LB4/LA4)*Pn4);
                Pb4 = (((PA + PB)/(Pn1+Pn2+Pn3+Pn4) * LB4/LA4)*Pn4);
            }

        }

        if  ((PA - Pa4 - Pn1) >= 0) { delta_pn1 = 0; } else {delta_pn1 = (PA - Pa4 - Pn1);}

        if  ((PB - Pb4 - Pn3) >= 0) {delta_pn3 = 0;} else {delta_pn3 = (PB - Pb4 - Pn3);};
        delta_pn2 = (PA - Pa4 - Pn1) + (PB - Pb4 - Pn3) - Pn2;
        delta_pn4 = Pa4 + Pb4 - Pn4;
    }


    if (delta_pn1*block_loads.statizm1 + 50 <= 0 ) { fn1 = 0;} else {fn1 = delta_pn1*block_loads.statizm1 + 50;}
    if (delta_pn2*block_loads.statizm2 + 50 <= 0 ) { fn2 = 0;} else {fn2 = delta_pn2*block_loads.statizm2 + 50;}
    if (delta_pn3*block_loads.statizm3 + 50 <= 0 ) { fn3 = 0;} else {fn3 = delta_pn3*block_loads.statizm3 + 50;}
    if (delta_pn4*block_loads.statizm4 + 50 <= 0 ) { fn4 = 0;} else {fn4 = delta_pn4*block_loads.statizm4 + 50;}
}

void MainWindow::equation_gen_1() {
    // делаем обратную связь по нагрузкам

    float Pem1 = block_gen_1.Pnagr*sin(block_gen_1.delta[scoper - 2]) + abs(block_gen_1.Pnagr - block_gen_2.Pnagr)*sin(block_gen_1.delta[scoper-2] - block_gen_2.delta[scoper-2]);
    float Pt1  = block_gen_1.Pnom*sin(block_gen_1.delta[0]) + abs(block_gen_1.Pnom - block_gen_2.Pnom)*sin(block_gen_1.delta[0] - block_gen_2.delta[0]);
    float Pload_marked_1 = block_loads.Pnom_1 + 0.3*block_loads.Pnom_4 + block_loads.Pnom_2*0.36;// выделенная на генератор нагрузка
    float deltaPnagr = Pem1 - Pload_marked_1;
    //! Расчёт режима первого генератора.

    float freq_new1 = ((Pt1 - deltaPnagr) - (Pem1 - deltaPnagr))/(block_gen_1.Tj)*2*h*50*3.14 + freq_array[scoper-1];
    float delta_new1 = (((Pt1- deltaPnagr) - (Pem1 - deltaPnagr))*h*h + (2*block_gen_1.Tj/W0*block_gen_1.delta[scoper-1]) - (block_gen_1.Tj/W0*block_gen_1.delta[scoper-2]) + (0.5*D*h*block_gen_1.delta[scoper-1]))/(block_gen_1.Tj/W0 + 0.5*D*h);
    freq_array.append(freq_new1);
    block_gen_1.delta.append(delta_new1);
    power_array.append(Pem1);
}


void MainWindow::equation_gen_2() {

    float Pem2 = block_gen_2.Pnagr*sin(block_gen_2.delta[scoper - 2]) + abs(- block_gen_1.Pnom + block_gen_2.Pnom)*sin(- block_gen_1.delta[scoper-2] + block_gen_2.delta[scoper-2]);
    float Pt2 = block_gen_2.Pnom*sin(block_gen_2.delta[0]) + abs(- block_gen_1.Pnom + block_gen_2.Pnom)*sin(- block_gen_1.delta[0] + block_gen_2.delta[0]);
    float Pload_marked_2 = block_loads.Pnom_3 + 0.7*block_loads.Pnom_4 + block_loads.Pnom_2*0.64;// выделенная на генератор нагрузка
    float deltaPnagr2 = Pem2 - Pload_marked_2;
    //! Расчёт режима первого генератора.


    float freq_new2 = ((Pt2- deltaPnagr2) - (Pem2 - deltaPnagr2))/block_gen_2.Tj*2*h*50*3.14 + freq2_array[scoper-1];
    float delta_new2 = (((Pt2 - deltaPnagr2) - (Pem2 - deltaPnagr2))*h*h + (2*block_gen_2.Tj/W0*block_gen_2.delta[scoper-1])- (block_gen_2.Tj/W0*block_gen_2.delta[scoper-2]) + (0.5*D*h*block_gen_2.delta[scoper-1]))/(block_gen_2.Tj/W0 + 0.5*D*h);
    freq2_array.append(freq_new2);
    block_gen_2.delta.append(delta_new2);
    power_array_2.append(Pem2);
}

void MainWindow::line_fault_regim_calc() {

    if (form.line_fault_checked == true) {
        if (lines_fault.line_off == 0) {
            // отключеена Г1-Н1
            if (time_t > form.t_vozm) {
                if (image_change == false) {
                    QImage heightMapImage(":/ES_G11.png");
                    m_sqrtSinSeries->setTexture(heightMapImage);
                    block_gen_2.Pnagr = block_loads.Pnom_1 + block_loads.Pnom_2 + block_loads.Pnom_3;
                    block_gen_1.Pnagr = block_loads.Pnom_4;
                    image_change = true;
                }
            }
        }

        if (lines_fault.line_off == 1) {
            // отключена Н1-Н2
            if (time_t > form.t_vozm) {
                if (image_change == false) {
                    QImage heightMapImage(":/ES_12.png");
                    m_sqrtSinSeries->setTexture(heightMapImage);
                    block_gen_2.Pnagr =  block_loads.Pnom_2 + block_loads.Pnom_3;
                    block_gen_1.Pnagr = block_loads.Pnom_1 + block_loads.Pnom_4;
                    image_change = true;
                }
            }
        }

        if (lines_fault.line_off == 2) {
            // отключена Н2-Н3
            if (time_t > form.t_vozm) {
                if (image_change == false) {
                    QImage heightMapImage(":/ES_23.png");
                    m_sqrtSinSeries->setTexture(heightMapImage);
                    block_gen_2.Pnagr = block_loads.Pnom_3 + block_loads.Pnom_4;
                    block_gen_1.Pnagr = block_loads.Pnom_1 + block_loads.Pnom_2;
                    image_change = true;
                }
            }
        }

        if (lines_fault.line_off == 3) {
            // отключена Н3-Г2
            if (time_t > form.t_vozm) {
                if (image_change == false) {
                    QImage heightMapImage(":/ES_3G2.png");
                    m_sqrtSinSeries->setTexture(heightMapImage);
                    block_gen_1.Pnagr = block_loads.Pnom_1 + block_loads.Pnom_2 + block_loads.Pnom_3;
                    block_gen_2.Pnagr = block_loads.Pnom_4;

                    image_change = true;
                }
            }
        }

        if (lines_fault.line_off == 4) {
            // отключена Г2-Н4
            if (time_t > form.t_vozm) {
                if (image_change == false) {
                    QImage heightMapImage(":/ES_G24.png");
                    m_sqrtSinSeries->setTexture(heightMapImage);
                    block_gen_2.Pnagr = block_loads.Pnom_2 + block_loads.Pnom_3;
                    block_gen_1.Pnagr = block_loads.Pnom_1 + block_loads.Pnom_4;
                    image_change = true;
                }
            }
        }

        if (lines_fault.line_off == 5) {
            // отключена Н4-Г1
            if (time_t > form.t_vozm) {
                QImage heightMapImage(":/ES_4G1.png");
                block_gen_1.Pnagr = block_loads.Pnom_1 + block_loads.Pnom_2 + block_loads.Pnom_3;
                block_gen_2.Pnagr = block_loads.Pnom_4;
                m_sqrtSinSeries->setTexture(heightMapImage);
            }
        }
    }


}
void MainWindow::fillSqrtSinProxy()
{

    QList<QPointF> generator_data_1;
    QList<QPointF> generator_data_2;

    if (regim_flag == 0) {
        // нормальный режим
    }

    if (p_vozvr_flag == true && regim_flag == 1 && p_vozvr_once_flag == false ) {
        //! Функция для возврата мощности после возмущения по таймеру
        //! для исследования АПВ
        if (time_t > form.t_vozm + p_vozvr) {
            if (form.knot_number == 0) {
                block_gen_1.Pnom = block_gen_1.Pnom - form.power_of_knot/Sb;
                // Если возмущение на Г1
                p_vozvr_once_flag = true;
            }

            if (form.knot_number == 1) {
                block_gen_2.Pnom = block_gen_2.Pnom - form.power_of_knot/Sb;
                // Если возмущение на Г2
                p_vozvr_once_flag = true;
            }

            if (form.knot_number == 2) {
                block_gen_1.Pnagr = block_gen_1.Pnagr - form.power_of_knot/Sb;
                // Если возмущение на нагрузке 1
                block_loads.Pnom_1 = block_loads.Pnom_1 - form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }
            if (form.knot_number == 3) {
                block_gen_1.Pnagr = block_gen_2.Pnagr - 0.5*form.power_of_knot/Sb;
                block_gen_2.Pnagr = block_gen_2.Pnagr - 0.5*form.power_of_knot/Sb;
                // Если возмущение на нагрузке 2
                block_loads.Pnom_2 = block_loads.Pnom_1 - form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }

            if (form.knot_number == 4) {
                block_gen_2.Pnagr = block_gen_2.Pnagr - form.power_of_knot/Sb;
                // Если возмущение на нагрузке 3
                block_loads.Pnom_3 = block_loads.Pnom_3 - form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }
            if (form.knot_number == 5) {
                block_gen_1.Pnagr = block_gen_2.Pnagr - 0.5*form.power_of_knot/Sb;
                block_gen_2.Pnagr = block_gen_2.Pnagr - 0.5*form.power_of_knot/Sb;
                // Если возмущение на нагрузке 4
                block_loads.Pnom_4 = block_loads.Pnom_4 - form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }
        }
    }

    if (p_vozvr_flag == true && regim_flag == 2 && p_vozvr_once_flag == false ) {
        //! Функция для возврата мощности после возмущения по таймеру
        //! для исследования АПВ
        if (time_t > form.t_vozm + p_vozvr) {
            if (form.knot_number == 0 ) {
                // Если возмущение на Г1
                block_gen_1.Pnom = block_gen_1.Pnom + form.power_of_knot/Sb;
                p_vozvr_once_flag = true;

            }

            if (form.knot_number == 1) {
                // Если возмущение на Г2
                block_gen_2.Pnom = block_gen_2.Pnom + form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }

            if (form.knot_number == 2) {
                // Если возмущение на нагрузке 1
                block_gen_1.Pnagr = block_gen_1.Pnagr   + form.power_of_knot/Sb;
                block_loads.Pnom_1 = block_loads.Pnom_1 + form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }
            if (form.knot_number == 3) {
                // Если возмущение на нагрузке 2
                block_gen_1.Pnagr = block_gen_2.Pnagr   + 0.5*form.power_of_knot/Sb;
                block_gen_2.Pnagr = block_gen_2.Pnagr   + 0.5*form.power_of_knot/Sb;
                block_loads.Pnom_2 = block_loads.Pnom_1 + form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }

            if (form.knot_number == 4) {
                // Если возмущение на нагрузке 3
                block_gen_2.Pnagr = block_gen_2.Pnagr  + form.power_of_knot/Sb;
                block_loads.Pnom_3 = block_loads.Pnom_3 + form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }
            if (form.knot_number == 5) {
                // Если возмущение на нагрузке 4
                block_gen_1.Pnagr = block_gen_2.Pnagr  + 0.5*form.power_of_knot/Sb;
                block_gen_2.Pnagr = block_gen_2.Pnagr  + 0.5*form.power_of_knot/Sb;
                block_loads.Pnom_4 = block_loads.Pnom_4 + form.power_of_knot/Sb;
                p_vozvr_once_flag = true;
            }

        }
    }

    if (regim_flag == 1 && form.knot_fault_checked == true) {
        // избыток мощности
        if (time_t > form.t_vozm) {
            // Расчёт в режиме после возмущения

            if (form.knot_number == 0 && regim_flag_knot_fault == false) {
                block_gen_1.Pnom = block_gen_1.Pnom + form.power_of_knot/Sb;
                // Если возмущение на Г1
                regim_flag_knot_fault = true;
            }

            if (form.knot_number == 1 && regim_flag_knot_fault == false) {
                block_gen_2.Pnom = block_gen_2.Pnom + form.power_of_knot/Sb;
                // Если возмущение на Г2
                regim_flag_knot_fault = true;
            }

            if (form.knot_number == 2 && regim_flag_knot_fault == false) {
                block_gen_1.Pnagr = block_gen_1.Pnagr + form.power_of_knot/Sb;
                // Если возмущение на нагрузке 1
                block_loads.Pnom_1 = block_loads.Pnom_1 + form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }
            if (form.knot_number == 3 && regim_flag_knot_fault == false) {
                block_gen_1.Pnagr = block_gen_2.Pnagr + 0.5*form.power_of_knot/Sb;
                block_gen_2.Pnagr = block_gen_2.Pnagr + 0.5*form.power_of_knot/Sb;
                // Если возмущение на нагрузке 2
                block_loads.Pnom_2 = block_loads.Pnom_1 + form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }

            if (form.knot_number == 4 && regim_flag_knot_fault == false) {
                block_gen_2.Pnagr = block_gen_2.Pnagr + form.power_of_knot/Sb;
                // Если возмущение на нагрузке 3
                block_loads.Pnom_3 = block_loads.Pnom_3 + form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }
            if (form.knot_number == 5 && regim_flag_knot_fault == false) {
                block_gen_1.Pnagr = block_gen_2.Pnagr + 0.5*form.power_of_knot/Sb;
                block_gen_2.Pnagr = block_gen_2.Pnagr + 0.5*form.power_of_knot/Sb;
                // Если возмущение на нагрузке 4
                block_loads.Pnom_4 = block_loads.Pnom_4 + form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }

        }

    }

    if (regim_flag == 2 && form.knot_fault_checked == true) {
        // недостаток мощности
        if (time_t > form.t_vozm) {
            // Расчёт в режиме после возмущения

            if (form.knot_number == 0 && regim_flag_knot_fault == false) {
                // Если возмущение на Г1

                block_gen_1.Pnom = block_gen_1.Pnom - form.power_of_knot/Sb;
                regim_flag_knot_fault = true;

            }

            if (form.knot_number == 1 && regim_flag_knot_fault == false) {
                // Если возмущение на Г2
                block_gen_2.Pnom = block_gen_2.Pnom - form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }

            if (form.knot_number == 2 && regim_flag_knot_fault == false) {
                // Если возмущение на нагрузке 1
                block_gen_1.Pnagr = block_gen_1.Pnagr - form.power_of_knot/Sb;
                block_loads.Pnom_1 = block_loads.Pnom_1 - form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }
            if (form.knot_number == 3 && regim_flag_knot_fault == false) {
                // Если возмущение на нагрузке 2
                block_gen_1.Pnagr = block_gen_2.Pnagr - 0.5*form.power_of_knot/Sb;
                block_gen_2.Pnagr = block_gen_2.Pnagr - 0.5*form.power_of_knot/Sb;
                block_loads.Pnom_2 = block_loads.Pnom_1 - form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }

            if (form.knot_number == 4 && regim_flag_knot_fault == false) {
                // Если возмущение на нагрузке 3
                block_gen_2.Pnagr = block_gen_2.Pnagr - form.power_of_knot/Sb;
                block_loads.Pnom_3 = block_loads.Pnom_3 - form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }
            if (form.knot_number == 5 && regim_flag_knot_fault == false) {
                // Если возмущение на нагрузке 4
                block_gen_1.Pnagr = block_gen_2.Pnagr - 0.5*form.power_of_knot/Sb;
                block_gen_2.Pnagr = block_gen_2.Pnagr - 0.5*form.power_of_knot/Sb;
                block_loads.Pnom_4 = block_loads.Pnom_4 - form.power_of_knot/Sb;
                regim_flag_knot_fault = true;
            }

        }

    }

    if (scoper >= 2) {
        // все расчёты
        equation_gen_1();
        equation_gen_2();
        power_balance();
        A4R1();
        A4R2();
        line_fault_regim_calc();
        time_array.append(time_t);

    }

    if (scoper < 1000) {

        generator_data_1.append(QPointF(time_t, freq_array[scoper]));
        generator_data_2.append(QPointF(time_t, freq2_array[scoper]));


    } else {
//        generator_spline_1->removePoints(0, 1);
//        generator_spline_2->removePoints(0, 1);

        generator_data_1.append(QPointF(time_t, freq_array[scoper]));
        generator_data_2.append(QPointF(time_t, freq2_array[scoper]));
    }


    generator_spline_1->append(generator_data_1);
    generator_spline_2->append(generator_data_2);




    if (scoper < 2) {                                                                      // генератор 1                  генератор 1                         генератор 1
        *newRow  <<  QVector3D(0.0f, 50.0f, 0.0f)   << QVector3D(5.0f, 50.0f, 0.0f) << QVector3D(10.0f, 50.0f, 0.0f)    << QVector3D(15.0f, 50.0f, 0.0f)  << QVector3D(20.0f, 50.0f, 0.0f) << QVector3D( 25.0f, fn4, 0.0f) << QVector3D( 30.0f, fn4,  0.0f);
        *newRow1 <<  QVector3D(0.0f, 50.0f, 5.0f)   << QVector3D(5.0f, 50.0f, 5.0f) << QVector3D(10.0f, 50.0f, 5.0f)    << QVector3D(15.0f, 50.0f, 5.0f)  << QVector3D(20.0f, 50.0f, 5.0f) << QVector3D(25.0f, fn4,  5.0f) << QVector3D( 30.0f, fn4,  5.0);
        *newRow2 <<  QVector3D(0.0f, 50.0f, 10.0f) << QVector3D(5.0f, 50.0f, 10.0f) << QVector3D(10.0f, 50.0f, 10.0f)   << QVector3D(15.0f, 50.0f, 10.0f) << QVector3D(20.0f, 50.0f, 10.0f) << QVector3D(25.0f, fn4, 10.0f) << QVector3D( 30.0f, fn4,  10.0);
        *newRow3 <<  QVector3D(0.0f, 50.0f, 15.0f) << QVector3D(5.0f, 50.0f, 15.0f) << QVector3D(10.0f, 50.0f, 15.0f)   << QVector3D(15.0f, 50.0f, 15.0f) << QVector3D(20.0f, 50.0f, 15.0f) << QVector3D(25.0f, 50.0f, 15.0f) << QVector3D( 30.0f, 50.0f,  15.0f);
        *newRow4 <<  QVector3D(0.0f, fn2, 20.0f) << QVector3D(5.0f, fn2, 20.0f) << QVector3D(10.0f, 50.0f, 20.0f)   << QVector3D(15.0f, 50.0f, 20.0f) << QVector3D(20.0f, 50.0f, 20.0f) << QVector3D(25.0f, 50.0f, 20.0f) << QVector3D( 30.0f, 50.0f,  20.0f);                                                                                    // генератор 2                  генератор 2                         генератор 2
        *newRow5 <<  QVector3D(0.0f, fn2, 25.0f) << QVector3D(5.0f, fn2, 25.0f) << QVector3D(10.0f, fn3, 25.0f)   << QVector3D(15.0f, fn3, 25.0f) << QVector3D(20.0f, fn3, 25.0f) << QVector3D(25.0f, 50.0f, 25.0f) << QVector3D( 30.0f, 50.0f,  25.0f);
        *newRow6 <<  QVector3D(0.0f, 50.0f, 30.0f) << QVector3D(5.0f, 50.0f, 30.0f) << QVector3D(10.0f, fn3, 30.0f)   << QVector3D(15.0f, fn3, 30.0f) << QVector3D(20.0f, fn3, 30.0f) << QVector3D(25.0f, 50.0f, 30.0f) << QVector3D( 30.0f, 50.0f,  30.0f);
        *dataArray << newRow << newRow1 << newRow2 << newRow3 << newRow4 <<  newRow5 << newRow6 ;


    } else {

        while (newRow->length() > 0) {
            newRow->removeLast();
            newRow1->removeLast();
            newRow2->removeLast();
            newRow3->removeLast();
            newRow4->removeLast();
        }

        while (dataArray->length() > 0) {
            dataArray->removeLast();
        }

        *newRow  <<  QVector3D(0.0f, 50.0f, 0.0f)   << QVector3D(5.0f, 50.0f, 0.0f) << QVector3D(10.0f, 50, 0.0f)       << QVector3D(15.0f, freq_array[scoper], 0.0f)  << QVector3D(20.0f, freq_array[scoper], 0.0f) << QVector3D( 25.0f, fn4, 0.0f) << QVector3D( 30.0f, fn4,  0.0f);
        *newRow1 <<  QVector3D(0.0f, fn1, 5.0f)     << QVector3D(5.0f, fn1, 5.0f)   << QVector3D(10.0f, 50, 5.0f)       << QVector3D(15.0f, freq_array[scoper], 5.0f)  << QVector3D(20.0f, calc_regim.freq_gen_1+0.0f, 5.0f) << QVector3D(25.0f, fn4,  5.0f) << QVector3D( 30.0f, fn4,  5.0f);
        *newRow2 <<  QVector3D(0.0f, fn1, 10.0f)    << QVector3D(5.0f, fn1, 10.0f)  << QVector3D(10.0f, 50.0f, 10.0f)   << QVector3D(15.0f, 50.0f, 10.0f)               << QVector3D(20.0f, 50.0f, 10.0f) << QVector3D(25.0f, fn4, 10.0f) << QVector3D( 30.0f, fn4,  10.0f);
        *newRow3 <<  QVector3D(0.0f, 50.0f, 15.0f)  << QVector3D(5.0f, 50.0f, 15.0f) << QVector3D(10.0f, 50.0f, 15.0f)  << QVector3D(15.0f, 50.0f, 15.0f) << QVector3D(20.0f, 50.0f, 15.0f) << QVector3D(25.0f, 50.0f, 15.0f) << QVector3D( 30.0f, 50.0f,  15.0f);
        *newRow4 <<  QVector3D(0.0f, fn2, 20.0f)    << QVector3D(5.0f, fn2, 20.0f)  << QVector3D(10.0f, 50.0f, 20.0f)   << QVector3D(15.0f, 50.0f, 20.0f) << QVector3D(20.0f, 50.0f, 20.0f) << QVector3D(25.0f, freq2_array[scoper], 20.0f) << QVector3D( 30.0f, freq2_array[scoper],  20.0f);
        *newRow5 <<  QVector3D(0.0f, fn2, 25.0f)    << QVector3D(5.0f, fn2, 25.0f)  << QVector3D(10.0f, fn3, 25.0f)     << QVector3D(15.0f, fn3, 25.0f) << QVector3D(20.0f, fn3, 25.0f) << QVector3D(25.0f, freq2_array[scoper], 25.0f) << QVector3D( 30.0f, freq2_array[scoper],  25.0f);
        *newRow6 <<  QVector3D(0.0f, 50.0f, 30.0f) << QVector3D(5.0f, 50.0f, 30.0f) << QVector3D(10.0f, fn3, 30.0f)     << QVector3D(15.0f,fn3, 30.0f) << QVector3D(20.0f, fn3, 30.0f) << QVector3D(25.0f, 50.0f, 30.0f) << QVector3D( 30.0f, 50.0f,  30.0f);
        *dataArray << newRow << newRow1 << newRow2 << newRow3 << newRow4 <<  newRow5 << newRow6 ;
    }

    if (scoper >= 2) {
        graph->removeSeries(m_sqrtSinSeries);
        generator_chart_1->removeSeries(generator_spline_1);
        generator_chart_1->removeSeries(AxisY_A4R_1);
        generator_chart_1->removeSeries(AxisY_A4R_2);
        generator_chart_2->removeSeries(generator_spline_2);
        generator_chart_2->removeSeries(AxisY_A4R_1_2);
        generator_chart_2->removeSeries(AxisY_A4R_2_2);
    }

    m_sqrtSinProxy->resetArray(dataArray);
    graph->addSeries(m_sqrtSinSeries);
    generator_chart_1->addSeries(generator_spline_1);
    generator_chart_1->addSeries(AxisY_A4R_1);
    generator_chart_1->addSeries(AxisY_A4R_2);

    generator_chart_2->addSeries(generator_spline_2);
    generator_chart_2->addSeries(AxisY_A4R_1_2);
    generator_chart_2->addSeries(AxisY_A4R_2_2);

    axisX_gen_freq_1->setRange(0,time_t +1);
    axisY_gen_freq_1->setRange(45,55);
    axisY_gen_freq_2->setRange(45,55);
    axisX_gen_freq_2->setRange(0,time_t + 1);

    generator_spline_1->attachAxis(axisX_gen_freq_1);
    generator_spline_1->attachAxis(axisY_gen_freq_1);

    generator_spline_2->attachAxis(axisX_gen_freq_2);
    generator_spline_2->attachAxis(axisY_gen_freq_2);

    AxisY_A4R_1->attachAxis(axisX_gen_freq_1);
    AxisY_A4R_1->attachAxis(axisY_gen_freq_1);

    AxisY_A4R_2->attachAxis(axisX_gen_freq_1);
    AxisY_A4R_2->attachAxis(axisY_gen_freq_1);

    AxisY_A4R_1_2->attachAxis(axisX_gen_freq_2);
    AxisY_A4R_1_2->attachAxis(axisY_gen_freq_2);

    AxisY_A4R_2_2->attachAxis(axisX_gen_freq_2);
    AxisY_A4R_2_2->attachAxis(axisY_gen_freq_2);

    if (enb_timer == true) {
        scoper++;
        time_t = time_t + step_sim;
        progress = static_cast<int>(time_t / sim_time * 100);
        progressBar->setValue(progress);


        if (count_sim_steps < scoper) {
            StartSim_btn->click();
            start_build_add_graph = true;
            if (form.additional_builds_state == 2){
                for (int i =0; i<power_array.count() - 2; i++) {
                    ch_form.series_power1->append(time_array[i], power_array[i]);
                    ch_form.series_delta1->append(time_array[i], block_gen_1.delta[i]*180/3.14);
                    ch_form.series_power2->append(time_array[i], power_array_2[i]);
                    ch_form.series_delta2->append(time_array[i], block_gen_2.delta[i]*180/3.14);
                    ch_form.series_power_delta1->append(block_gen_1.delta[i]*180/3.14, power_array[i]);
                    ch_form.series_power_delta2->append(block_gen_2.delta[i]*180/3.14, power_array_2[i]);
                }

                ch_form.chart_delta1->addSeries(ch_form.series_delta1);
                ch_form.chart_delta2->addSeries(ch_form.series_delta2);
                ch_form.chart_power1->addSeries(ch_form.series_power1);
                ch_form.chart_power2->addSeries(ch_form.series_power2);
                ch_form.chart_power_delta1->addSeries(ch_form.series_power_delta1);
                ch_form.chart_power_delta2->addSeries(ch_form.series_power_delta2);

                ch_form.series_power_delta1->attachAxis(ch_form.power_delta_1_axisX);
                ch_form.series_power_delta1->attachAxis(ch_form.power_delta_1_axisY);
                ch_form.series_power_delta2->attachAxis(ch_form.power_delta_2_axisX);
                ch_form.series_power_delta2->attachAxis(ch_form.power_delta_2_axisY);

                ch_form.series_power1->attachAxis(ch_form.power1_axisX);
                ch_form.series_power1->attachAxis(ch_form.power1_axisY);
                ch_form.series_delta1->attachAxis(ch_form.delta1_axisX);
                ch_form.series_delta1->attachAxis(ch_form.delta1_axisY);

                ch_form.series_power2->attachAxis(ch_form.power2_axisX);
                ch_form.series_power2->attachAxis(ch_form.power2_axisY);

                ch_form.series_delta2->attachAxis(ch_form.delta2_axisX);
                ch_form.series_delta2->attachAxis(ch_form.delta2_axisY);

                start_build_add_graph = false;
            }
        }
    }
}


void MainWindow::StartSim()  {

    sim_time = textEdit->text().toFloat();
    count_sim_steps = static_cast<int>(sim_time / step_sim);

   // базисная мощность (для приведения параметров в относительные единицы)
    if (form.additional_builds_state == 2) {
        ch_form.show();
    }


    if (form.ui_debug_state == 2) {
        if (button_condition == false) {
            form_debug.setP1VerticalRange(int(block_loads.Pnom_1+100), int(block_loads.Pnom_1-100), int(block_loads.Pnom_1));
            form_debug.setP2VerticalRange(int(block_loads.Pnom_2+100), int(block_loads.Pnom_2-100), int(block_loads.Pnom_2));
            form_debug.setP3VerticalRange(int(block_loads.Pnom_3+100), int(block_loads.Pnom_3-100), int(block_loads.Pnom_3));
            form_debug.setP4VerticalRange(int(block_loads.Pnom_4+100), int(block_loads.Pnom_4-100), int(block_loads.Pnom_4));

            form_debug.show();
        }
    }

    if (button_condition == false) {
        if (restart == false) {
            restart = true;
        } else {}

        button_condition = true;
        Pause->setVisible(true);
        StartSim_btn->setGeometry(QRect(1060, 670, 211, 51));
        sim_condition = true;
        enb_timer = true;
        timer->start(1);

        if (ifSimStarted == false) {
            ifSimStarted = true;
        } else {ifSimStarted = false;}
        Pause->setText(QCoreApplication::translate("MainWindow",  "\320\237\320\260\321\203\320\267\320\260" , nullptr));
        StartSim_btn->setText(QCoreApplication::translate("MainWindow",  "\320\236\321\202\320\274\320\265\320\275\320\260" , nullptr));
        StartSim_btn->setStyleSheet(QString::fromUtf8(" background-color: #f44336;"                                                      "  border: none;\n"
                                                      "  color: white;\n"
                                                      "  padding: 15px 32px;\n"
                                                      "  text-align: center;\n"
                                                      "  text-decoration: none;\n"
                                                      "  display: inline-block;\n"
                                                      "  font-size: 16px;\n"
                                                      " border-radius: 5px;"));
    }
    else {
        enb_timer = false;
        scoper = 0;
        time_t = 0;
        button_condition = false;
        Pause->setVisible(false);
        StartSim_btn->setGeometry(QRect(820, 670, 451, 51));
        sim_condition = false;
        timer->stop();
        progressBar->setValue(0);
        StartSim_btn->setText(QCoreApplication::translate("MainWindow","\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        StartSim_btn->setStyleSheet(QString::fromUtf8("background-color: #4CAF50;\n"
                                                      "  border: none;\n"
                                                      "  color: white;\n"
                                                      "  padding: 15px 32px;\n"
                                                      "  text-align: center;\n"
                                                      "  text-decoration: none;\n"
                                                      "  display: inline-block;\n"
                                                      "  font-size: 16px;\n"
                                                      " border-radius: 5px;"));
    }


}

void MainWindow::acceptParams() {

    Sb = form.S_basis;

    QImage heightMapImage(":/Es.jpg");
    m_sqrtSinSeries->setTexture(heightMapImage);

    if (params_enabled_change == false) {
        combo_index = comboBox->currentIndex();
        switch (combo_index) {
        case 0:
            regim_flag = 0; // нормальный режим
            break;
        case 1:
            regim_flag = 1; // избыток мощности
            break;
        case 2:
            regim_flag = 2; // недостаток мощности
            break;
        default:
            regim_flag = 0;
        }

        //! Параметры блока генерации 1 (генератор)


        block_gen_1.Tj     = Tj_field->text().toFloat();

        block_gen_1.delta.append(Xtr_field->text().toFloat()*3.14/180);
        block_gen_1.delta.append(Xtr_field->text().toFloat()*3.14/180);

        block_gen_1.Pnom = Snom1_field->text().toFloat()/Sb;
        block_gen_1.Pnom_const = Snom1_field->text().toFloat()/Sb;
        block_gen_1.Pnagr = Snom1_field->text().toFloat()/Sb;

        //! Параметры блока генерации 2 (генератор)


        block_gen_2.Tj     = Tj_field_2->text().toFloat();

        block_gen_2.delta.append(Xtr_field_2->text().toFloat()*3.14/180);
        block_gen_2.delta.append(Xtr_field_2->text().toFloat()*3.14/180);

        block_gen_2.Pnom = Snom1_field_2->text().toFloat()/Sb;
        block_gen_2.Pnom_const = Snom1_field_2->text().toFloat()/Sb;
        block_gen_2.Pnagr = Snom1_field_2->text().toFloat()/Sb;
        //! Параметры блока нагрузок
        block_loads.Pnom_1  = PnomNagr_1_field->text().toFloat()/Sb;
        block_loads.kn1 = load_group_box->currentIndex();
        block_loads.statizm1 = cos_fi_1_field->text().toFloat() / 100;

        block_loads.Pnom_2  = PnomNagr_1_field_2->text().toFloat()/Sb;
        block_loads.kn2 = load_group_box_2->currentIndex();
        block_loads.statizm2 = cos_fi_1_field_2->text().toFloat() / 100;

        block_loads.Pnom_3  = PnomNagr_1_field_3->text().toFloat()/Sb;
        block_loads.kn3 = load_group_box_3->currentIndex();
        block_loads.statizm3 = cos_fi_1_field_3->text().toFloat() / 100;

        block_loads.Pnom_4  = PnomNagr_1_field_4->text().toFloat()/Sb;
        block_loads.kn4 = load_group_box_4->currentIndex();
        block_loads.statizm4 = cos_fi_1_field_4->text().toFloat() / 100; // статизм (раньше было полем косинуса, теперь sf)

        if (A4R2_time_A4R1_field->text().toFloat() == 0) {
            A4R_preload.A4R2_from_A4R1_time = 5;
        } else {
            A4R_preload.A4R2_from_A4R1_time = A4R2_time_A4R1_field->text().toFloat();
        }
        //! Блок предварительных расчётов. Расчёт величин для предущего установившегося режима


        float sum_power = block_loads.Pnom_4 + block_loads.Pnom_3 + block_loads.Pnom_2 + block_loads.Pnom_1;

        D = ((block_loads.Pnom_1 / sum_power)*block_loads.kn1 +
             (block_loads.Pnom_2 / sum_power)*block_loads.kn2 +
             (block_loads.Pnom_3 / sum_power)*block_loads.kn3 +
             (block_loads.Pnom_4 / sum_power)*block_loads.kn4) ; // коэффициент демпфирования, рассчитанный по павлову

        power_array.append(block_gen_1.Pnom*sin(block_gen_1.delta[0]) + (block_gen_1.Pnom - block_gen_2.Pnom)*sin(block_gen_1.delta[0] - block_gen_2.delta[0]));
        power_array.append(block_gen_1.Pnom*sin(block_gen_1.delta[0]) + (block_gen_1.Pnom - block_gen_2.Pnom)*sin(block_gen_1.delta[0] - block_gen_2.delta[0]));

        power_array_2.append(block_gen_2.Pnom*sin(block_gen_2.delta[0]) + (block_gen_1.Pnom - block_gen_2.Pnom)*sin(block_gen_1.delta[0] - block_gen_2.delta[0]));
        power_array_2.append(block_gen_2.Pnom*sin(block_gen_2.delta[0]) + (block_gen_1.Pnom - block_gen_2.Pnom)*sin(block_gen_1.delta[0] - block_gen_2.delta[0]));

        //! Параметры срабатывания АЧР 1 и АЧР 2 (берём из формы)
        //!


        A4R_preload.A4R1_srab = lineEdit_2->text().toFloat();
        A4R_preload.A4R2_srab = lineEdit_2->text().toFloat();

        A4R_preload.A4R1_P = form.A4R1_P;
        A4R_preload.A4R1_f = form.A4R1_f;
        A4R_preload.A4R1_t = form.A4R1_t;
        A4R_preload.A4R1_timer = form.A4R1_t;

        A4R_preload.A4R2_P = form.A4R2_P;
        A4R_preload.A4R2_t = form.A4R2_t;

        A4R_preload.A4R1_steps_count = form.A4R1_steps_count;
        A4R_preload.A4R2_steps_count = form.A4R2_steps_count;
        A4R_preload.flag_once_time = false;

        lines_fault.line_mark = form.line_mark;
        lines_fault.line_off = form.line_off;

        h = form.h;
        regim_flag_knot_fault = false;
        A4R_preload.A4R2_ust_vozvr = form.A4R2_vozvr_ust;

        A4R_preload.A4R2_srab_flag = false;
        A4R_preload.A4R2_srab_flag_2 = false;

        A4R_preload.A4R1_f_deriv = 50;
        A4R_preload.A4R1_f_deriv_2 = 50;

        p_vozvr = form.timer_P_vozvr;
        p_vozvr_flag = form.flag_P_vozvr;

    }


    if (params_enabled_change == false) {
        scrollAreaWidget->setEnabled(false);
        comboBox->setEnabled(false);
        StartSim_btn->setToolTip("");
        StartSim_btn->setStyleSheet(QString::fromUtf8("background-color: #4CAF50;\n"
                                                      "  border: none;\n"
                                                      "  color: white;\n"
                                                      "  padding: 15px 32px;\n"
                                                      "  text-align: center;\n"
                                                      "  text-decoration: none;\n"
                                                      "  display: inline-block;\n"
                                                      "  font-size: 16px;\n"
                                                      " border-radius: 5px;"));
        StartSim_btn->setEnabled(true);

        scrollAreaWidget->setStyleSheet(QString::fromUtf8("QScrollArea QLineEdit{background-color: rgba(206, 206, 206, 200);}"));
        Params->setText(QString::fromUtf8("Изменить параметры и очистить графики"));
        params_enabled_change = true;

    } else {
        scrollAreaWidget->setEnabled(true);
        comboBox->setEnabled(true);
        erasing_all_arrays();
        scrollAreaWidget->setStyleSheet(QString());
        StartSim_btn->setEnabled(false);
        StartSim_btn->setToolTip("Неодходимо задать параметры системы");
        StartSim_btn->setStyleSheet(QString::fromUtf8("background-color: #c5c5c5;\n"
                                                      "  border: none;\n"
                                                      "  color: white;\n"
                                                      "  padding: 15px 32px;\n"
                                                      "  text-align: center;\n"
                                                      "  text-decoration: none;\n"
                                                      "  display: inline-block;\n"
                                                      "  font-size: 16px;\n"
                                                      " border-radius: 5px;"));
        Params->setText(QString::fromUtf8("Применить параметры"));
        params_enabled_change = false;
    }


}

void MainWindow::paused() {
    if (button_pause_condition == false) {
        enb_timer = false;
        button_pause_condition = true;
        sim_condition = false;
        Pause->setText(QCoreApplication::translate("MainWindow",  "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214" , nullptr));
        timer->stop();
    }
    else {
        button_pause_condition = false;
        sim_condition = true;
        enb_timer = true;
        Pause->setText(QCoreApplication::translate("MainWindow",  "\320\237\320\260\321\203\320\267\320\260" , nullptr));
        timer->start(1);
    }
}

void MainWindow::callModalWindow() {
    form.change_regim_label(comboBox->currentText());
    form.show();
}

void MainWindow::scroll_graph_fq_1() {

}
