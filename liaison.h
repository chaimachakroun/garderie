#ifndef LIAISON_H
#define LIAISON_H

#include <QMainWindow>
#include"clube.h"
#include"equip.h"
namespace Ui {
class liaison;
}

class liaison : public QMainWindow
{
    Q_OBJECT

public:
    explicit liaison(QWidget *parent = nullptr);
    ~liaison();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::liaison *ui;
    Clube * C;
    equip * E;
};

#endif // LIAISON_H
