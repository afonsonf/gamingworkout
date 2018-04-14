#ifndef RASTROS_H
#define RASTROS_H

#include <QWidget>

namespace Ui {
class rastros;
}

class rastros : public QWidget
{
    Q_OBJECT

public:
    explicit rastros(QWidget *parent = 0);
    ~rastros();

private:
    Ui::rastros *ui;
};

#endif // RASTROS_H
