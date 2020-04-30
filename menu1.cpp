#include "menu1.h"
#include "ui_menu1.h"
#include "repas.h"
#include "quantite.h"


Menu1::Menu1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu1)
{
    ui->setupUi(this);
}

Menu1::~Menu1()
{
    delete ui;
}


void Menu1::on_sauvegarder_clicked()
{

    repas = new MainWindow(this) ;
    repas->show() ;

}




void Menu1::on_sauvegarder_2_clicked()
{
    quantite = new MainWindow1(this) ;
    quantite->show() ;

}
