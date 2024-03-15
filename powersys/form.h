#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);

    void change_regim_label(QString text_label);

    float t_vozm;
    float power_of_knot;
    int knot_number;

    float volume_specqueue;
    float t_srab_que;
    float f_srab_que;

    float f_main_queue_step;
    float t_main_queue_step;


    ~Form();

private slots:
    void on_pushButton_2_released();

    void on_pushButton_released();

private:


    Ui::Form *ui;
};

#endif // FORM_H
