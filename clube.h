#ifndef CLUBE_H
#define CLUBE_H
#include"clb.h"
#include <QMainWindow>

namespace Ui {
class Clube;
}

class Clube : public QMainWindow
{
    Q_OBJECT

public:
    explicit Clube(QWidget *parent = nullptr);
    ~Clube();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_lineEdit_6_textChanged(const QString &arg1);

private:
    Ui::Clube *ui;
    clb tmpclb;
};

#endif // CLUBE_H
