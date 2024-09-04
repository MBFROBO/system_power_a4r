#ifndef FORM_DEBUG_H
#define FORM_DEBUG_H

#include <QWidget>

namespace Ui {
class Form_debug;
}

class Form_debug : public QWidget
{
    Q_OBJECT

public:
    explicit Form_debug(QWidget *parent = nullptr);
    ~Form_debug();


public slots:
    void setP1VerticalRange(int P1max, int P1min, int Cur_P);
    void setP2VerticalRange(int P2max, int P2min, int Cur_P);
    void setP3VerticalRange(int P3max, int P3min, int Cur_P);
    void setP4VerticalRange(int P4max, int P4min, int Cur_P);

private slots:
    void on_PverticalSlider_sliderMoved(int position);




    void on_PverticalSlider_2_sliderMoved(int position);

    void on_PverticalSlider_3_sliderMoved(int position);

    void on_PverticalSlider_4_sliderMoved(int position);

private:
    Ui::Form_debug *ui;
};

#endif // FORM_DEBUG_H
