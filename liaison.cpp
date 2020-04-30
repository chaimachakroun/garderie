#include "liaison.h"
#include "ui_liaison.h"

#include<QMainWindow>
liaison::liaison(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::liaison)
{
    ui->setupUi(this);
}

liaison::~liaison()
{
    delete ui;
}

void liaison::on_pushButton_clicked()
{
   C = new Clube(this);
    C->show();
}

void liaison::on_pushButton_2_clicked()
{
    E = new equip(this);
    E->show();
}
