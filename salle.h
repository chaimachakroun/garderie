#ifndef SALLE_H
#define SALLE_H
#include "crudsalle.h"
#include <QMainWindow>

namespace Ui {
class salle;
}

class salle : public QMainWindow
{
    Q_OBJECT

public:
    explicit salle(QWidget *parent = nullptr);
    ~salle();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();



    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_lineEdit_3_textChanged(const QString &arg1);

private:
    Ui::salle *ui;
    crudsalle tmpsalle;

};

#endif // SALLE_H
