#ifndef AVANCO_H
#define AVANCO_H

#include <QWidget>

namespace Ui {
class avanco;
}

class avanco : public QWidget
{
    Q_OBJECT

public:
    explicit avanco(QWidget *parent = 0);
    ~avanco();

private:
    Ui::avanco *ui;
};

#endif // AVANCO_H
