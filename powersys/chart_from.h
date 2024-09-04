#ifndef CHART_FROM_H
#define CHART_FROM_H

#include <QWidget>

namespace Ui {
class chart_from;
}

class chart_from : public QWidget
{
    Q_OBJECT

public:
    explicit chart_from(QWidget *parent = nullptr);
    ~chart_from();

private:
    Ui::chart_from *ui;
};

#endif // CHART_FROM_H
