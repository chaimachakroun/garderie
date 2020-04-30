#ifndef SALLE1_H
#define SALLE1_H

#include <QMainWindow>
#include "affichagesalle.h"
#include "affichagebatiment.h"
namespace Ui {
class salle1;
}

class salle1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit salle1(QWidget *parent = nullptr);
    ~salle1();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::salle1 *ui;
    salle *sal;
    batiment *bat1;
};

#endif // SALLE1_H
