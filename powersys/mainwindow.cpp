#include "mainwindow.h"
#include "normal_regim.h"
#include "new_plain.h"
#include "form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    Params = new QPushButton(this);
    connect(Params, &QPushButton::clicked, this, &MainWindow::acceptParams);

    Pause = new QPushButton(this);
    connect(Pause, &QPushButton::clicked, this, &MainWindow::paused);
    StartSim_btn = new QPushButton(this);
    connect(StartSim_btn,  &QPushButton::clicked, this, &MainWindow::StartSim);

    pushButton = new QPushButton(this);
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::callModalWindow);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::fillSqrtSinProxy);

    generator_spline_1 = new QSplineSeries();
    generator_spline_2 = new QSplineSeries();

    generator_chart_1 = new QChart();
    generator_chart_1->legend()->hide();
//    generator_chart_1->axisY()->setRange(-1, 1);
//    generator_chart_1->axisX()->setRange(0,5);

    generator_chart_2 = new QChart();
    generator_chart_2->legend()->hide();
//    generator_chart_2->createDefaultAxes();
//    generator_chart_2->axisY()->setRange(-1, 1);
//    generator_chart_2->axisX()->setRange(0,5);

    generator_freq_1 = new QChartView(generator_chart_1, this);
    generator_freq_1->setRenderHint(QPainter::Antialiasing);
    generator_freq_2 = new QChartView(generator_chart_2, this);
    generator_freq_2->setRenderHint(QPainter::Antialiasing);

    comboBox = new QComboBox(this);
    comboBox->addItem("Нормальный режим");
    comboBox->addItem("Избыток мощности");
    comboBox->addItem("Недостаток мощности");


    QImage heightMapImage(":/test.png");
    m_sqrtSinProxy = new QSurfaceDataProxy();
    m_sqrtSinSeries = new QSurface3DSeries(m_sqrtSinProxy);
    m_sqrtSinSeries->setTexture(heightMapImage);

    fillSqrtSinProxy();

    m_heightMapProxy = new QHeightMapSurfaceDataProxy(heightMapImage);
    m_heightMapSeries = new QSurface3DSeries(m_heightMapProxy);
    m_heightMapSeries->setItemLabelFormat(QStringLiteral("(@xLabel, @zLabel): @yLabel"));
    m_heightMapSeries->setTexture(heightMapImage);

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


void MainWindow::fillSqrtSinProxy()
{

    QList<QPointF> generator_data_1;
    QList<QPointF> generator_data_2;



    if (scoper < 50) {
        generator_data_1.append(QPointF(time_t, sin(_w*time_t*100)));
        generator_data_2.append(QPointF(time_t, cos(_w*time_t*100)));
    } else {
//        generator_data_1.removeFirst();
//        generator_data_2.removeFirst();
        generator_spline_1->removePoints(0, 1);
        generator_spline_2->removePoints(0, 1);
        generator_data_1.append(QPointF(time_t, sin(_w*time_t*100)));
        generator_data_2.append(QPointF(time_t, cos(_w*time_t*100)));
    }

    generator_spline_1->append(generator_data_1);
    generator_spline_2->append(generator_data_2);

    if (scoper == 0) {
        *newRow  <<  QVector3D(0.0f, 1.8f, 0.0f) << QVector3D(15.0f, 1.8f, 0.0f);
        *newRow1 <<  QVector3D(0.0f, 1.8f, 5.0f) << QVector3D(15.0f, 1.8f, 5.0f);
        *newRow2 <<  QVector3D(0.0f, 1.8f, 10.0f) << QVector3D(15.0f, 1.8f, 10.0f);
        *newRow3 <<  QVector3D(0.0f, 1.8f, 15.0f) << QVector3D(15.0f, 1.9f, 15.0f);
        *newRow4 <<  QVector3D(0.0f, 1.8f, 20.0f) << QVector3D(15.0f, 2.0f, 20.0f);
        *dataArray << newRow << newRow1 << newRow2 << newRow3 << newRow4 ;

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

        *newRow  <<  QVector3D(0.0f, sin(_w*time_t*10 + 0.0f), 0.0f) << QVector3D(15.0f, sin(_w*time_t*10 + 0.0f), 0.0f);
        *newRow1 <<  QVector3D(0.0f, sin(_w*time_t*10 + 0.1f), 5.0f) << QVector3D(15.0f, sin(_w*time_t*10 + 0.1f), 5.0f);
        *newRow2 <<  QVector3D(0.0f, sin(_w*time_t*10 + 0.2f), 10.0f) << QVector3D(15.0f, sin(_w*time_t*10 + 0.2f), 10.0f);
        *newRow3 <<  QVector3D(0.0f, sin(_w*time_t*10 + 0.3f), 15.0f) << QVector3D(15.0f, sin(_w*time_t*10 + 0.3f), 15.0f);
        *newRow4 <<  QVector3D(0.0f, sin(_w*time_t*10 + 0.4f), 20.0f) << QVector3D(15.0f, sin(_w*time_t*10 + 0.4f), 20.0f);
        *dataArray << newRow << newRow1 << newRow2 << newRow3 << newRow4 ;

    }

    if (scoper > 0) {
        graph->removeSeries(m_sqrtSinSeries);
        generator_chart_1->removeSeries(generator_spline_1);
        generator_chart_2->removeSeries(generator_spline_2);
    }

    m_sqrtSinProxy->resetArray(dataArray);
    graph->addSeries(m_sqrtSinSeries);

    generator_chart_1->addSeries(generator_spline_1);
    generator_chart_2->addSeries(generator_spline_2);

    generator_chart_1->createDefaultAxes();
    generator_chart_2->createDefaultAxes();

    if (enb_timer == true) {
        scoper++;
        time_t = time_t + step_sim;
        progress = static_cast<int>(time_t / sim_time * 100);
        progressBar->setValue(progress);

        if (count_sim_steps < scoper) {
            StartSim_btn->click();
        }
    }
}


void MainWindow::StartSim()  {
    sim_time = textEdit->text().toFloat();
    count_sim_steps = static_cast<int>(sim_time / step_sim);


    if (button_condition == false) {
        button_condition = true;
        Pause->setVisible(true);
        StartSim_btn->setGeometry(QRect(1060, 670, 211, 51));
        sim_condition = true;
        enb_timer = true;
        timer->start(20);
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
    combo_index = comboBox->currentIndex();

    if (params_enabled_change == false) {
        //! Параметры блока генерации 1 (генератор + сопротивление трансформатора)
        block_gen_1.Ug_nom = Ug1nom_field->text().toFloat();
        block_gen_1.Pnom   = Snom1_field->text().toFloat();
        block_gen_1.Xd     = Xd1_field->text().toFloat();
        block_gen_1.Xd1    = Xd11_field->text().toFloat();
        block_gen_1.Xd11   = Xd111_field->text().toFloat();
        block_gen_1.Td0    = Td0_field->text().toFloat();
        block_gen_1.Tj     = Tj_field->text().toFloat();
        block_gen_1.Xtr    = Xtr_field->text().toFloat();

        //! Параметры блока генерации 2 (генератор + сопротивление трансформатора)
        block_gen_2.Ug_nom = Ug1nom_field_2->text().toFloat();
        block_gen_2.Pnom   = Snom1_field_2->text().toFloat();
        block_gen_2.Xd     = Xd1_field_2->text().toFloat();
        block_gen_2.Xd1    = Xd11_field_2->text().toFloat();
        block_gen_2.Xd11   = Xd111_field_2->text().toFloat();
        block_gen_2.Td0    = Td0_field_2->text().toFloat();
        block_gen_2.Tj     = Tj_field_2->text().toFloat();
        block_gen_2.Xtr    = Xtr_field_2->text().toFloat();

        //! Параметры блока нагрузок
        block_loads.Pnom_1  = PnomNagr_1_field->text().toFloat();
        block_loads.cosfi_1 = cos_fi_1_field->text().toFloat();
        block_loads.group_1 = load_group_box->currentIndex();

        block_loads.Pnom_2  = PnomNagr_1_field_2->text().toFloat();
        block_loads.cosfi_2 = cos_fi_1_field_2->text().toFloat();
        block_loads.group_2 = load_group_box_2->currentIndex();

        block_loads.Pnom_3  = PnomNagr_1_field_3->text().toFloat();
        block_loads.cosfi_3 = cos_fi_1_field_3->text().toFloat();
        block_loads.group_3 = load_group_box_3->currentIndex();

        block_loads.Pnom_4  = PnomNagr_1_field_4->text().toFloat();
        block_loads.cosfi_4 = cos_fi_1_field_4->text().toFloat();
        block_loads.group_4 = load_group_box_4->currentIndex();
    }


    if (params_enabled_change == false) {
        scrollAreaWidget->setEnabled(false);
        scrollAreaWidget->setStyleSheet(QString::fromUtf8("QScrollArea QLineEdit{background-color: rgba(206, 206, 206, 200);}"));
        Params->setText(QString::fromUtf8("Изменить параметры"));
        params_enabled_change = true;
    } else {
        scrollAreaWidget->setEnabled(true);
        scrollAreaWidget->setStyleSheet(QString());
        Params->setText(QString::fromUtf8("Применить параметры"));
        params_enabled_change = false;
    }

    qDebug() << combo_index << " " << block_gen_1.Ug_nom;
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
        timer->start(20);
    }
}

void MainWindow::callModalWindow() {
    form.change_regim_label(comboBox->currentText());
    form.show();
}
