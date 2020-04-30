#include "MainWindow.h"
#include "ui_club.h"

Club::Club(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Club)
{
    ui->setupUi(this);
}

Club::~Club()
{
    delete ui;
}

void Club::on_pushButton_clicked()
{
    L = new liaison(this);
    L->show();
}
