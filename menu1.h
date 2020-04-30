#ifndef MENU1_H
#define MENU1_H

#include <QMainWindow>
#include "mainwindow.h"
#include "mainwindow1.h"
namespace Ui {
class Menu1;
}

class Menu1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu1(QWidget *parent = nullptr);
    ~Menu1();

private slots:
    void on_sauvegarder_clicked();

    void on_sauvegarder_2_clicked();

private:
    Ui::Menu1 *ui;
    MainWindow *repas ;
    MainWindow1 *quantite ;
};

#endif // MENU1_H
