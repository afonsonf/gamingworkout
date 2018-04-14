#ifndef CAESGATOS_H
#define CAESGATOS_H

#include <QWidget>
#include <QPushButton>


namespace Ui {
class CaesGatos;
}

class CaesGatos : public QWidget
{
    Q_OBJECT

public:
    explicit CaesGatos(QWidget *parent = 0,QPushButton *back = 0);

    ~CaesGatos();

private:
    Ui::CaesGatos *ui;
    QPushButton *back;
};

#endif // CAESGATOS_H
