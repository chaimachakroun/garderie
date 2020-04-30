#include "salle1.h"
#include "ui_salle1.h"

salle1::salle1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::salle1)
{
    ui->setupUi(this);
}

salle1::~salle1()
{
    delete ui;
}

void salle1::on_pushButton_7_clicked()
{
    sal =new salle (this);
      sal->show();
}

void salle1::on_pushButton_8_clicked()
{
    bat1 =new batiment (this);
    bat1->show();
}
