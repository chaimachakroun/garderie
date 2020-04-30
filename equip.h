#ifndef EQUIP_H
#define EQUIP_H
#include "eqp.h"
#include <QMainWindow>

namespace Ui {
class equip;
}

class equip : public QMainWindow
{
    Q_OBJECT

public:
    explicit equip(QWidget *parent = nullptr);
    ~equip();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

private:
    Ui::equip *ui;
     eqp tmpeqp;
};

#endif // EQUIP_H
