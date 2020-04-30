#ifndef BATIMENT_H
#define BATIMENT_H
#include "crudbatiment.h"
#include <QMainWindow>


namespace Ui {
class batiment;
}

class batiment : public QMainWindow
{
    Q_OBJECT

public:
    explicit batiment(QWidget *parent = nullptr);
    ~batiment();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();


    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_lineEdit_3_textChanged(const QString &arg1);



private:
    Ui::batiment *ui;
     crudbatiment tmpbatiment;
};

#endif // BATIMENT_H
