#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H
#include "quantite.h"
#include <QMainWindow>


namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();
private slots:
    void on_sauvegarder_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_sauvegarder_4_clicked();

    void on_sauvegarder_5_clicked();

    void on_tablequantite_activated(const QModelIndex &index);

private:
    Ui::MainWindow1 *ui;
   quantite tableau1;
};

#endif // MAINWINDOW1_H
