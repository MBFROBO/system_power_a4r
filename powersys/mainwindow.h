#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <normal_regim.h>
#include <outline_power.h>
#include <relief_power.h>
#include <form_debug.h>
#include <QtCharts/QChartView>
#include <QValueAxis>
#include "chart_form.h"
#include <QChart>
#include <QSplineSeries>
#include <QMainWindow>
#include <form.h>
#include <Q3DSurface>
#include <QWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QLineEdit>
#include <QHeightMapSurfaceDataProxy>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QCoreApplication>
#include <QtWidgets/QScrollArea>
#include <QDoubleValidator>
#include <Q3DSurface>
#include <QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <QIntValidator>
#include <QDebug>
#include <QPushButton>
#include <QSpacerItem>
#include <QCheckBox>
#include <QDialog>
#include <QLineSeries>
#include <QScatterSeries>
#include <QPainter>
#include <QPen>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSurface3DSeries *m_heightMapSeries;
    QSurfaceDataProxy *m_sqrtSinProxy;
    QSurface3DSeries *m_sqrtSinSeries;
    QHeightMapSurfaceDataProxy *m_heightMapProxy;
    QSurfaceDataArray *dataArray = new QSurfaceDataArray;

    QSurfaceDataRow *newRow = new QSurfaceDataRow;
    QSurfaceDataRow *newRow1 = new QSurfaceDataRow;
    QSurfaceDataRow *newRow2 = new QSurfaceDataRow;
    QSurfaceDataRow *newRow3 = new QSurfaceDataRow;
    QSurfaceDataRow *newRow4 = new QSurfaceDataRow;
    QSurfaceDataRow *newRow5 = new QSurfaceDataRow;
    QSurfaceDataRow *newRow6 = new QSurfaceDataRow;

public:

    MainWindow(QWidget *parent = nullptr);
    Q3DSurface *graph = new Q3DSurface();
    ~MainWindow();




    struct regim {
        //! описание режима

        auto normal(){
            auto nr = new Normal_regim();
            return nr;
        }
        auto load_outline(){
            auto lo = new outline_power();
            return lo;
        }

        auto load_relief() {
            auto lr = new relief_power();
            return lr;
        }

    }_regim;

    struct gen_1{

        float Pnom;
        float Pnom_const;
        float Pnagr;
        float Tj;
        QList<float> delta = {};

    } block_gen_1;

    struct gen_2{

        float Pnom;
        float Pnom_const;
        float Pnagr;
        float Tj;
        QList<float> delta = {};

    } block_gen_2;

    struct lines {
        int line_mark;
        int line_off;
        float Power_transit; // Транзит мощности по оставшейся связи

    } lines_fault;

    struct loads{

        float Pnom_1 = 0;
        float kn1;
        float statizm1;

        float Pnom_2 = 0;
        float kn2;
        float statizm2;

        float Pnom_3 = 0;
        float kn3;
        float statizm3;

        float Pnom_4 = 0;
        float kn4;
        float statizm4;

    } block_loads;

    struct A4R{
        // структура уставок АЧР

        float A4R1_srab;
        float A4R2_srab;
        float A4R1_f_deriv = 50;
        float A4R1_f_deriv_2 = 50;
        float A4R1_timer;
        float A4R2_timer = 0;

        float A4R1_timer_2;
        float A4R2_timer_2 = 0;

        float A4R2_timer_fromA4R1 = 0;
        float A4R2_timer_fromA4R1_2 = 0;
        bool flag_once_time = false;
        bool flag_once_time_2 = false;

        int A4R1_scoper = 0;
        int A4R2_scoper = 0;

        int A4R1_scoper_2 = 0;
        int A4R2_scoper_2 = 0;
        float A4R2_ust_vozvr;

        bool A4R2_srab_flag = false;
        bool A4R2_srab_flag_2 = false;

        float A4R2_from_A4R1_time = 5;

        float A4R1_P;
        float A4R1_t;
        float A4R1_f;

        float A4R2_t;
        float A4R2_P;

        int A4R1_steps_count;
        int A4R2_steps_count;

    } A4R_preload;


    struct regim_params {
        // параметры режима
        float freq_gen_1 = 50;
        float delta_gen_1 = 15;
        float power_gen_1 = 1.6;

        float freq_gen_2;
        float delta_gen_2;
        float power_gen_2;
    } calc_regim;

    void _SetupUi(QMainWindow *MainWindow) {

        StartSim_btn->setObjectName("StartSim_btn");
        StartSim_btn->setGeometry(QRect(819, 672, 452, 47));
        StartSim_btn->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        StartSim_btn->setCursor(QCursor(Qt::PointingHandCursor));
        StartSim_btn->setStyleSheet(QString::fromUtf8("background-color: #c5c5c5;\n"
                                                      "  border: none;\n"
                                                      "  color: white;\n"
                                                      "  padding: 15px 32px;\n"
                                                      "  text-align: center;\n"
                                                      "  text-decoration: none;\n"
                                                      "  display: inline-block;\n"
                                                      "  font-size: 16px;\n"
                                                      " border-radius: 5px;"));


        QIntValidator *pIntVld = new QIntValidator(this);
        pIntVld->setBottom(0);

        data_load_list << "0" << "1" << "2" << "3" << "4";

        QDoubleValidator *pDoubleVld = new QDoubleValidator(this);
        pDoubleVld->setNotation(QDoubleValidator::ScientificNotation);
        pDoubleVld->setLocale(QLocale::English);
        pDoubleVld->setDecimals(3);

        QFont font;

        textEdit = new QLineEdit(MainWindow);
        textEdit->setText(QString("15"));
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(1440, 20, 131, 20));
        textEdit->setValidator(pIntVld);

        progressBar = new QProgressBar(MainWindow);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(40, 685, 741, 20));
        progressBar->setValue(0);


        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(1440, 50, 131, 21));


        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1580, 20, 151, 51));


        scrollArea = new QScrollArea(this);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(1290, 260, 441, 401));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(false);
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea{border: 0px solid #a5a5a5;\n"
                                                    "border-radius:5px;}\n"
                                                    ));

        scrollAreaWidget = new QWidget();
        scrollAreaWidget->setGeometry(QRect(0, 0, 421, 400));

        //! ГЕНЕРАТОР - ТРАНСФОРМТАОР 1
        groupBox = new QGroupBox(scrollAreaWidget);
        groupBox->setObjectName("groupBox");
        groupBox->setEnabled(true);
        groupBox->setGeometry(QRect(10, 10, 410, 81));
        groupBox->setContextMenuPolicy(Qt::CustomContextMenu);
        groupBox->setStyleSheet(QString::fromUtf8("border: 1px solid #a3a3a3;\n"));


        Snom1_field = new QLineEdit(groupBox);
        Snom1_field->setObjectName("Snom1_field");
        Snom1_field->setText("250");
        Snom1_field->setGeometry(QRect(60, 40, 51, 21));
        Snom1_field->setValidator(pDoubleVld);


        S1nom = new QLabel(groupBox);
        S1nom->setObjectName("S1nom");
        S1nom->setGeometry(QRect(10, 40, 50, 21));

        Tj1 = new QLabel(groupBox);
        Tj1->setObjectName("Tj1");
        Tj1->setGeometry(QRect(285, 40, 26, 21));

        Tj_field = new QLineEdit(groupBox);
        Tj_field->setObjectName("Tj_field");
        Tj_field->setText("7");
        Tj_field->setGeometry(QRect(310, 40, 51, 21));
        Tj_field->setValidator(pDoubleVld);

        Tj_izm = new QLabel(groupBox);
        Tj_izm->setObjectName("Tj_izm");
        Tj_izm->setGeometry(QRect(360, 40, 26, 21));

        Xtr1 = new QLabel(groupBox);
        Xtr1->setObjectName("Xtr1");
        Xtr1->setGeometry(QRect(170, 40, 26, 22));

        Xtr_field = new QLineEdit(groupBox);
        Xtr_field->setObjectName("Xtr_field");
        Xtr_field->setText("27.05");
        Xtr_field->setGeometry(QRect(186, 40, 51, 22));
        Xtr_field->setValidator(pDoubleVld);

        Xtr_izm = new QLabel(groupBox);
        Xtr_izm->setObjectName("Xtr_izm");
        Xtr_izm->setGeometry(QRect(237, 40, 30, 22));

        Snom1_izm = new QLabel(groupBox);
        Snom1_izm->setObjectName("Snom1_izm");
        Snom1_izm->setGeometry(QRect(110, 40, 35, 21));

        //! ГЕНЕРАТОР - ТРАНСФОРМТАОР 2
        groupBox_2 = new QGroupBox(scrollAreaWidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setEnabled(true);
        groupBox_2->setGeometry(QRect(10, 101, 410, 81));
        groupBox_2->setStyleSheet(QString::fromUtf8("border: 1px solid #a3a3a3;\n"));


        Snom1_field_2 = new QLineEdit(groupBox_2);
        Snom1_field_2->setObjectName("Snom1_field_2");
        Snom1_field_2->setGeometry(QRect(60, 40, 51, 21));
        Snom1_field_2->setText("400");
        Snom1_field_2->setValidator(pDoubleVld);



        S1nom_2 = new QLabel(groupBox_2);
        S1nom_2->setObjectName("S1nom_2");
        S1nom_2->setGeometry(QRect(10, 40, 50, 21));


        Tj1_2 = new QLabel(groupBox_2);
        Tj1_2->setObjectName("Tj1_2");
        Tj1_2->setGeometry(QRect(285, 40, 26, 21));

        Tj_field_2 = new QLineEdit(groupBox_2);
        Tj_field_2->setObjectName("Tj_field_2");
        Tj_field_2->setText("9");
        Tj_field_2->setGeometry(QRect(310, 40, 51, 21));
        Tj_field_2->setValidator(pDoubleVld);

        Tj_izm_2 = new QLabel(groupBox_2);
        Tj_izm_2->setObjectName("Tj_izm_2");
        Tj_izm_2->setGeometry(QRect(360, 40, 26, 21));

        Xtr1_2 = new QLabel(groupBox_2);
        Xtr1_2->setObjectName("Xtr1_2");
        Xtr1_2->setGeometry(QRect(170, 40, 26, 22));

        Xtr_field_2 = new QLineEdit(groupBox_2);
        Xtr_field_2->setObjectName("Xtr_field_2");
        Xtr_field_2->setText("25.24");
        Xtr_field_2->setGeometry(QRect(186, 40, 51, 22));
        Xtr_field_2->setValidator(pDoubleVld);

        Xtr_izm_2 = new QLabel(groupBox_2);
        Xtr_izm_2->setObjectName("Xtr_izm_2");
        Xtr_izm_2->setGeometry(QRect(237, 40, 30, 22));

        Snom1_izm_2 = new QLabel(groupBox_2);
        Snom1_izm_2->setObjectName("Snom1_izm_2");
        Snom1_izm_2->setGeometry(QRect(110, 40, 35, 21));

        groupBox_4 = new QGroupBox(scrollAreaWidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(10, 192, 410, 181));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {border: 1px solid #a3a3a3;}\n"
                                                    "QLabel {border: 1px solid #a3a3a3;}\n"
                                                    "QLineEdit {border: 1px solid #a3a3a3;}\n"));

        PnomNagr_1_field = new QLineEdit(groupBox_4);
        PnomNagr_1_field->setObjectName("PnomNagr_1_field");
        PnomNagr_1_field->setText("62.3");
        PnomNagr_1_field->setGeometry(QRect(80, 30, 51, 21));
        PnomNagr_1_field->setValidator(pDoubleVld);

        PnomNagr_1 = new QLabel(groupBox_4);
        PnomNagr_1->setObjectName("PnomNagr_1");
        PnomNagr_1->setGeometry(QRect(10, 30, 71, 21));

        PnomNagr_1_izm = new QLabel(groupBox_4);
        PnomNagr_1_izm->setObjectName("PnomNagr_1_izm");
        PnomNagr_1_izm->setGeometry(QRect(130, 30, 31, 21));

        cos_fi_1 = new QLabel(groupBox_4);
        cos_fi_1->setObjectName("cos_fi_1");
        cos_fi_1->setGeometry(QRect(170, 30, 41, 21));

        cos_fi_1_field = new QLineEdit(groupBox_4);
        cos_fi_1_field->setObjectName("cos_fi_1_field");
        cos_fi_1_field->setText("3");
        cos_fi_1_field->setGeometry(QRect(210, 30, 71, 21));
        cos_fi_1_field->setValidator(pDoubleVld);

        line_2 = new QFrame(groupBox_4);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(20, 52, 361, 5));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        load_group = new QLabel(groupBox_4);
        load_group->setObjectName("load_group");
        load_group->setGeometry(QRect(290, 30, 48, 21));

        load_group_box = new QComboBox(groupBox_4);
        load_group_box->setObjectName("load_group_box");
        load_group_box->setGeometry(QRect(340, 30, 41, 21));
        load_group_box->addItems(data_load_list);



        PnomNagr_2 = new QLabel(groupBox_4);
        PnomNagr_2->setObjectName("PnomNagr_2");
        PnomNagr_2->setGeometry(QRect(10, 60, 71, 21));

        PnomNagr_1_field_2 = new QLineEdit(groupBox_4);
        PnomNagr_1_field_2->setObjectName("PnomNagr_1_field_2");
        PnomNagr_1_field_2->setGeometry(QRect(80, 60, 51, 21));
        PnomNagr_1_field_2->setText("81.7");
        PnomNagr_1_field_2->setValidator(pDoubleVld);

        PnomNagr_1_izm_2 = new QLabel(groupBox_4);
        PnomNagr_1_izm_2->setObjectName("PnomNagr_1_izm_2");
        PnomNagr_1_izm_2->setGeometry(QRect(130, 60, 31, 21));

        cos_fi_2 = new QLabel(groupBox_4);
        cos_fi_2->setObjectName("cos_fi_2");
        cos_fi_2->setGeometry(QRect(170, 60, 41, 21));

        cos_fi_1_field_2 = new QLineEdit(groupBox_4);
        cos_fi_1_field_2->setObjectName("cos_fi_1_field_2");
        cos_fi_1_field_2->setText("3");
        cos_fi_1_field_2->setGeometry(QRect(210, 60, 71, 21));
        cos_fi_1_field_2->setValidator(pDoubleVld);

        load_group_2 = new QLabel(groupBox_4);
        load_group_2->setObjectName("load_group_2");
        load_group_2->setGeometry(QRect(290, 60, 48, 21));

        load_group_box_2 = new QComboBox(groupBox_4);
        load_group_box_2->setObjectName("load_group_box_2");
        load_group_box_2->setGeometry(QRect(340, 60, 41, 21));
        load_group_box_2->addItems(data_load_list);

        line_3 = new QFrame(groupBox_4);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(20, 82, 361, 5));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        PnomNagr_3 = new QLabel(groupBox_4);
        PnomNagr_3->setObjectName("PnomNagr_3");
        PnomNagr_3->setGeometry(QRect(10, 90, 71, 21));

        PnomNagr_1_field_3 = new QLineEdit(groupBox_4);
        PnomNagr_1_field_3->setObjectName("PnomNagr_1_field_3");
        PnomNagr_1_field_3->setGeometry(QRect(80, 90, 51, 21));
        PnomNagr_1_field_3->setText("68");
        PnomNagr_1_field_3->setValidator(pDoubleVld);

        PnomNagr_1_izm_3 = new QLabel(groupBox_4);
        PnomNagr_1_izm_3->setObjectName("PnomNagr_1_izm_3");
        PnomNagr_1_izm_3->setGeometry(QRect(130, 90, 31, 21));

        cos_fi_3 = new QLabel(groupBox_4);
        cos_fi_3->setObjectName("cos_fi_3");

        cos_fi_3->setGeometry(QRect(170, 90, 41, 21));
        cos_fi_1_field_3 = new QLineEdit(groupBox_4);
        cos_fi_1_field_3->setObjectName("cos_fi_1_field_3");
        cos_fi_1_field_3->setText("3");
        cos_fi_1_field_3->setGeometry(QRect(210, 90, 71, 21));
        cos_fi_1_field_3->setValidator(pDoubleVld);

        load_group_3 = new QLabel(groupBox_4);
        load_group_3->setObjectName("load_group_3");
        load_group_3->setGeometry(QRect(290, 90, 48, 21));

        load_group_box_3 = new QComboBox(groupBox_4);
        load_group_box_3->setObjectName("load_group_box_3");
        load_group_box_3->setGeometry(QRect(340, 90, 41, 21));
        load_group_box_3->addItems(data_load_list);

        line_4 = new QFrame(groupBox_4);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(20, 112, 361, 5));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        PnomNagr_4 = new QLabel(groupBox_4);
        PnomNagr_4->setObjectName("PnomNagr_4");
        PnomNagr_4->setGeometry(QRect(10, 120, 71, 21));

        PnomNagr_1_field_4 = new QLineEdit(groupBox_4);
        PnomNagr_1_field_4->setObjectName("PnomNagr_1_field_4");
        PnomNagr_1_field_4->setText("72.25");
        PnomNagr_1_field_4->setGeometry(QRect(80, 120, 51, 21));
        PnomNagr_1_field_4->setValidator(pDoubleVld);

        PnomNagr_1_izm_4 = new QLabel(groupBox_4);
        PnomNagr_1_izm_4->setObjectName("PnomNagr_1_izm_4");
        PnomNagr_1_izm_4->setGeometry(QRect(130, 120, 31, 21));

        cos_fi_4 = new QLabel(groupBox_4);
        cos_fi_4->setObjectName("cos_fi_4");
        cos_fi_4->setGeometry(QRect(170, 120, 41, 21));

        cos_fi_1_field_4 = new QLineEdit(groupBox_4);
        cos_fi_1_field_4->setObjectName("cos_fi_1_field_4");
        cos_fi_1_field_4->setText("3");
        cos_fi_1_field_4->setGeometry(QRect(210, 120, 71, 21));
        cos_fi_1_field_4->setValidator(pDoubleVld);

        load_group_4 = new QLabel(groupBox_4);
        load_group_4->setObjectName("load_group_4");
        load_group_4->setGeometry(QRect(290, 120, 48, 21));

        load_group_box_4 = new QComboBox(groupBox_4);
        load_group_box_4->setObjectName("load_group_box_4");
        load_group_box_4->setGeometry(QRect(340, 120, 41, 21));
        load_group_box_4->addItems(data_load_list);

        line_5 = new QFrame(groupBox_4);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(20, 142, 361, 5));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);



        scroll_layout = new QVBoxLayout(this);
        scroll_layout->addWidget(scrollAreaWidget);

        scrollArea->setWidget(scrollAreaWidget);


        label_3 = new QLabel(MainWindow);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(1300, 230, 191, 21));
        font.setPointSize(11);
        label_3->setFont(font);

        groupBox_5 = new QGroupBox(MainWindow);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(1290, 80, 431, 141));
        groupBox_5->setFont(font);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 30, 49, 16));

        QFont font1;
        font1.setPointSize(9);
        label_4->setFont(font1);
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(240, 30, 49, 16));
        label_5->setFont(font1);

        line = new QFrame(groupBox_5);
        line->setObjectName("line");
        line->setGeometry(QRect(210, 20, 16, 111));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        checkBox = new QCheckBox(groupBox_5);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(40, 50, 121, 16));
        checkBox->setFont(font1);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 80, 91, 21));
        label_6->setFont(font1);
        lineEdit_2 = new QLineEdit(groupBox_5);

        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(120, 80, 61, 21));
        lineEdit_2->setValidator(pDoubleVld);


        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(190, 80, 21, 21));
        label_7->setFont(font1);

        checkBox_2 = new QCheckBox(groupBox_5);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(260, 50, 121, 16));
        checkBox_2->setFont(font1);

        label = new QLabel(MainWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(1300, 20, 131, 21));
        font.setPointSize(11);
        label->setFont(font);
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \321\201\320\270\320\274\321\203\320\273\321\217\321\206\320\270\320\270:", nullptr));

        label_2 = new QLabel(MainWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1300, 50, 131, 21));
        label_2->setFont(font);

        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(230, 80, 111, 21));
        label_8->setFont(font1);

        A4R2_time_A4R1_field = new QLineEdit(groupBox_5);
        A4R2_time_A4R1_field->setValidator(pDoubleVld);
        A4R2_time_A4R1_field->setObjectName("A4R2_time_A4R1_field");
        A4R2_time_A4R1_field->setGeometry(QRect(340, 80, 51, 21));


        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(400, 80, 21, 21));
        label_9->setFont(font1);

        Params->setObjectName("StartSim_2");
        Params->setGeometry(QRect(1280, 670, 451, 51));
        Params->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));

        Pause->setObjectName("Pause");
        Pause->setGeometry(QRect(820, 670, 211, 51));
        Pause->setCursor(QCursor(Qt::PointingHandCursor));
        Pause->setStyleSheet(QString::fromUtf8("background-color: #008CBA;\n"));
        Pause->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        Pause->setVisible(false);
        Pause->setStyleSheet(QString::fromUtf8("background-color: #008CBA;\n"
                                               "  border: none;\n"
                                               "  color: white;\n"
                                               "  padding: 15px 32px;\n"
                                               "  text-align: center;\n"
                                               "  text-decoration: none;\n"
                                               "  display: inline-block;\n"
                                               "  font-size: 16px;\n"
                                               " border-radius: 5px;"));



        generator_freq_1->setObjectName("generator_freq_1");
        generator_freq_1->setGeometry(QRect(810, 10, 470, 327));
        generator_chart_1->setTitle("Частота генератора 1");

        generator_freq_2->setObjectName("generator_freq_2");
        generator_freq_2->setGeometry(QRect(810, 340, 470, 327));
        generator_chart_2->setTitle("Частота генератора 2");

        label_2->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274:", nullptr));
        groupBox->setTitle(QString("Генератор 1"));
        groupBox_2->setTitle(QString("Генератор 2"));

        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\263\321\200\321\203\320\267\320\272\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \321\200\320\265\320\266\320\270\320\274", nullptr));
        S1nom->setText(QCoreApplication::translate("MainWindow", "P\320\275\320\276\320\274", nullptr));

        Tj1->setText(QCoreApplication::translate("MainWindow", "Tj", nullptr));
        Tj_izm->setText(QCoreApplication::translate("MainWindow", "\321\201", nullptr));
        Xtr1->setText("\u03B4");
        Xtr_izm->setText(QString("град"));
        Snom1_izm->setText(QString("МВт"));

        S1nom_2->setText(QCoreApplication::translate("MainWindow", "P\320\275\320\276\320\274", nullptr));

        Tj1_2->setText(QCoreApplication::translate("MainWindow", "Tj", nullptr));
        Tj_izm_2->setText(QCoreApplication::translate("MainWindow", "\321\201", nullptr));
        Xtr1_2->setText("\u03B4");
        Xtr_izm_2->setText(QString("град"));
        Snom1_izm_2->setText(QString("МВт"));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\215\320\275\320\265\321\200\320\263\320\276\321\200\320\260\320\271\320\276\320\275\320\260", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\220\320\247\320\240", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\220\320\247\320\240-1", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\220\320\247\320\240-2", nullptr));
        checkBox->setText(QString("Ввод АЧР 1"));
        label_6->setText(QString("    Усатвка АЧР 1"));
        label_6->setToolTip(QString("Уставка основного объёма АЧР1"));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\223\321\206", nullptr));
        label_8->setText(QString("Отстройка от АЧР1"));
        label_9->setText(QString("сек"));
        checkBox_2->setText(QString("Ввод АЧР 2"));
        PnomNagr_1->setText(QCoreApplication::translate("MainWindow", "(1) P\320\275, \320\275\320\276\320\274", nullptr));
        PnomNagr_1_izm->setText(QCoreApplication::translate("MainWindow", "M\320\222\321\202", nullptr));
        cos_fi_1->setText(QString(" sf,%"));
        load_group->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
        PnomNagr_2->setText(QCoreApplication::translate("MainWindow", "(2) P\320\275, \320\275\320\276\320\274", nullptr));
        PnomNagr_1_izm_2->setText(QCoreApplication::translate("MainWindow", "M\320\222\321\202", nullptr));
        cos_fi_2->setText(QString(" sf,%"));
        load_group_2->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
        PnomNagr_3->setText(QCoreApplication::translate("MainWindow", "(3) P\320\275, \320\275\320\276\320\274", nullptr));
        PnomNagr_1_izm_3->setText(QCoreApplication::translate("MainWindow", "M\320\222\321\202", nullptr));
        cos_fi_3->setText(QString(" sf,%"));
        load_group_3->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
        PnomNagr_4->setText(QCoreApplication::translate("MainWindow", "(4) P\320\275, \320\275\320\276\320\274", nullptr));
        PnomNagr_1_izm_4->setText(QCoreApplication::translate("MainWindow", "M\320\222\321\202", nullptr));
        cos_fi_4->setText(QString(" sf,%"));

        load_group_4->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
    }

private slots:
    void fillSqrtSinProxy();
    void StartSim();
    void acceptParams();
    void paused();
    void callModalWindow();
    void power_balance();
    void equation_gen_1();
    void equation_gen_2();
    void erasing_all_arrays();
    void scroll_graph_fq_1();
    void A4R1();
    void A4R2();
    void line_fault_regim_calc();


private:

    QPushButton *StartSim_btn;
    QTimer *timer;
    QLineEdit *textEdit;
    QLabel *label;
    QLabel *label_2;
    QPushButton *Params;
    QPushButton *Pause;
    QProgressBar *progressBar;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QScrollArea *scrollArea;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_4;
    QWidget *scrollAreaWidget;
    QVBoxLayout *scroll_layout;
    QSpacerItem *d_bottom_vertical_spacer ;
    QLineEdit *PnomNagr_1_field;
    QLabel *PnomNagr_1;
    QLabel *PnomNagr_1_izm;
    QLabel *cos_fi_1;
    QLineEdit *cos_fi_1_field;
    QFrame *line_2;
    QLabel *load_group;
    QComboBox *load_group_box;
    QLabel *PnomNagr_2;
    QLineEdit *PnomNagr_1_field_2;
    QLabel *PnomNagr_1_izm_2;
    QLabel *cos_fi_2;
    QLineEdit *cos_fi_1_field_2;
    QLabel *load_group_2;
    QComboBox *load_group_box_2;
    QFrame *line_3;
    QLabel *PnomNagr_3;
    QLineEdit *PnomNagr_1_field_3;
    QLabel *PnomNagr_1_izm_3;
    QLabel *cos_fi_3;
    QLineEdit *cos_fi_1_field_3;
    QLabel *load_group_3;
    QComboBox *load_group_box_3;
    QFrame *line_4;
    QLabel *PnomNagr_4;
    QLineEdit *PnomNagr_1_field_4;
    QLabel *PnomNagr_1_izm_4;
    QLabel *cos_fi_4;
    QLineEdit *cos_fi_1_field_4;
    QLabel *load_group_4;
    QComboBox *load_group_box_4;
    QFrame *line_5;
    QStringList data_load_list;
    QLineEdit *Snom1_field;
    QLabel *S1nom;

    QLabel *Tj1;
    QLineEdit *Tj_field;
    QLabel *Tj_izm;
    QLabel *Xtr1;
    QLineEdit *Xtr_field;
    QLabel *Xtr_izm;
    QLabel *Snom1_izm;
    QGroupBox *Gen2;
    QLineEdit *Snom1_field_2;
    QLabel *S1nom_2;
    QLinearGradient *gr;

    QLabel *Tj1_2;
    QLineEdit *Tj_field_2;
    QLabel *Tj_izm_2;
    QLabel *Xtr1_2;
    QLineEdit *Xtr_field_2;
    QLabel *Xtr_izm_2;
    QLabel *Snom1_izm_2;
    QLabel *label_3;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *A4R2_time_A4R1_field;
    QGroupBox *groupBox_5;
    QLabel *label_4;
    QLabel *label_5;
    QFrame *line;
    QCheckBox *checkBox;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QLabel *label_7;
    QCheckBox *checkBox_2;
    QMenuBar *menubar;
    QChartView *generator_freq_1;
    QChartView *generator_freq_2;
    QSplineSeries *generator_spline_1;
    QSplineSeries *generator_spline_2;
    QChart *generator_chart_1;
    QChart *generator_chart_2;

    QScatterSeries *AxisY_A4R_2;
    QScatterSeries *AxisY_A4R_1;

    QScatterSeries *AxisY_A4R_2_2;
    QScatterSeries *AxisY_A4R_1_2;

    QValueAxis *axisX_gen_freq_1;
    QValueAxis *axisY_gen_freq_1;
    QValueAxis *axisX_gen_freq_2;
    QValueAxis *axisY_gen_freq_2;

    chart_form ch_form;
    Form form;
    Form_debug form_debug;



    bool button_pause_condition = false;
    int combo_index;
    int regim_flag;
    bool button_condition = false;
    bool sim_condition = false;
    bool params_enabled_change = false;
    float _w = 2*3.14*50;
    int scoper = 0;
    int progress = 0;
    float sim_time;
    int count_sim_steps;
    float time = 0.0;
    float time_t = 0.0;
    float step_sim = 0.02;

    float p_vozvr;
    bool p_vozvr_flag;
    bool p_vozvr_once_flag = false;

    float Sb = 1;
    bool restart = false;
    bool ifSimStarted = false;

    QList<float> time_array = {};
    bool start_build_add_graph = false;
    QList<float> freq_array = {50, 50};
    QList<float> freq2_array = {50, 50};

    int W0 = 18000;
    float h = 0.02;

    float fn1 = 50;
    float fn2 = 50;
    float fn3 = 50;
    float fn4 = 50;
    float D = 1;

    float delta_pn1 = 0;
    float delta_pn2 = 0;
    float delta_pn3 = 0;
    float delta_pn4 = 0;

    float LA1 = 41.824;
    float L12 = 73.635;
    float L32 = 46.4;
    float LB3 = 41.824;
    float LB4 = 36.682;
    float LA4 = 51.877;
    bool image_change = false;
    bool regim_flag_knot_fault = false;


    QList<float> power_array = {};
    QList<float> power_array_2 = {};

    bool enb_timer = false;
    float m_rangeMinX;
    float m_rangeMinZ;
    float m_stepX;
    float m_stepZ;
    int m_heightMapWidth;
    int m_heightMapHeight;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
