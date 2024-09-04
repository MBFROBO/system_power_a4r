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

    float A4R1_P;
    float A4R1_f;
    float A4R1_t;
    int A4R1_steps_count;

    float A4R2_P;
    float A4R2_t;
    int A4R2_steps_count;

    int additional_builds_state;
    int ui_debug_state;

    float S_basis;

    int line_off;
    int line_mark;

    bool line_fault_checked;
    bool knot_fault_checked;
    float h;
    float A4R2_vozvr_ust;
    bool flag_P_vozvr;
    float timer_P_vozvr;

    ~Form();

private slots:
    void on_pushButton_2_released();
    void on_pushButton_released();


private:


    Ui::Form *ui;
};

#endif // FORM_H
