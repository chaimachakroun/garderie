#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "repas.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_sauvegarder_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_sauvegarder_2_clicked();

    void on_sauvegarder_4_clicked();

    void on_sauvegarder_5_clicked();

    void on_sauvegarder_3_clicked();

    void on_tablerepas_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    repas tableau ;

};
#endif // MAINWINDOW_H
