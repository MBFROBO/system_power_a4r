#ifndef DOC_H
#define DOC_H

#include <QDockWidget>

namespace Ui {
class Doc;
}

class Doc : public QDockWidget
{
    Q_OBJECT

public:
    explicit Doc(QWidget *parent = nullptr);
    ~Doc();

private:
    Ui::Doc *ui;
};

#endif // DOC_H
