#include <QPixmap>
#include "ui_menu1.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPrinter>
#include <QFileDialog>
#include<QTextDocument>

#include "repas.h"
#include "menu1.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tablerepas->setModel(tableau.afficher()) ;
    QPixmap pix("C:/Users/Utilisateur/Documents/garderie2/lepetit.png");
        ui->label->setPixmap(pix) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*void MainWindow::on_sauvegarder_clicked()
{
    QString entree= ui->lineEmpl_2->text();
    QString plat= ui->lineEmpl_3->text();
    QString dessert= ui->lineTache->text();
    int nb = ui->lineTache_2->text().toInt();
    QString datee= ui->lineEmpl_4->text();
  repas e(entree,plat,dessert,nb,datee);
  bool test=e.ajouter();
  if(test)
{

      ui->tablerepas->setModel(tableau.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un repas"),
                  QObject::tr("repas ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un repas"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);



}*/

void MainWindow::on_pushButton_4_clicked()
{
    int nb = ui->lineTache_3->text().toInt() ;
    bool test=tableau.supprimer(nb);
    if(test)
    {
        ui->tablerepas->setModel(tableau.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un repas"),
                    QObject::tr("repas supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un repas"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_3_clicked()
{
    QString entree= ui->lineEmpl_2->text();
    QString plat= ui->lineEmpl_3->text();
    QString dessert= ui->lineTache->text();
    int nb = ui->lineTache_2->text().toInt();
    QString datee= ui->lineEmpl_4->text();
  repas e(entree,plat,dessert,nb,datee);
  bool test=e.modifier();
  if(test)
    {
       ui->tablerepas->setModel(tableau.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Modifier repas"),
                      QObject::tr("repas modifier.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Modifier repas"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_sauvegarder_4_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> Repas du jour </font><br /> <br /> "));
        str.append("<table border=1><tr>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">jour</font>&nbsp;&nbsp;"+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">entrée </font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">plat principale</font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">dessert</font>&nbsp;&nbsp;"+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">nombres </font>&nbsp;&nbsp;")+"</td>");

        QSqlQuery * query=new QSqlQuery();
        query->exec("SELECT entree,plat,dessert,nb,date FROM repas");
        while(query->next())
        {
            str.append("<tr><td>");
            str.append("&nbsp;&nbsp;<font color =""green"" size= ""10"">"+query->value(0).toString()+"&nbsp;&nbsp;");
            str.append("</td><td>");
            str.append("&nbsp;&nbsp;<font color =""green""  size=""10"">"+query->value(1).toString()+"&nbsp;&nbsp;");
            str.append("</td><td>");
            str.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(2).toString()+"&nbsp;&nbsp;");
             str.append("</td><td>");
            str.append("&nbsp;&nbsp;<font color =""green"" size= ""10"">"+query->value(3).toString()+"&nbsp;&nbsp;");
            str.append("</td><td>");
            str.append("&nbsp;&nbsp;<font color =""green""  size=""10"">"+query->value(4).toString()+"&nbsp;&nbsp;");
            str.append("</td><td>");
            str.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(5).toString()+"&nbsp;&nbsp;");
            str.append("</td></tr>");
    }
        str.append("</table></center><body></html>");
        QPrinter printer;
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        QString path= QFileDialog::getSaveFileName(NULL,"imprimer","repas","PDF(*.pdf");
         if(path.isEmpty()) return;
         printer.setOutputFileName(path);
         QTextDocument doc;
         doc.setHtml(str);
         doc.print(&printer);
}

void MainWindow::on_sauvegarder_5_clicked()
{
    int nb = ui->lineTache_2->text().toInt();
        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * from repas where nb like concat (:nb,'%')");
        qry->bindValue(":nb",nb);
        qry->exec();
        model->setQuery(*qry);
        ui->tablerepas->setModel(model) ;

}



void MainWindow::on_sauvegarder_3_clicked()
{
    QString entree= ui->lineEmpl_2->text();
    QString plat= ui->lineEmpl_3->text();
    QString dessert= ui->lineTache->text();
    int nb = ui->lineTache_2->text().toInt();
    QString datee= ui->lineEmpl_4->text();
  repas e(entree,plat,dessert,nb,datee);
  bool test=e.ajouter();
  if(test)
{

      ui->tablerepas->setModel(tableau.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un repas"),
                  QObject::tr("repas ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un repas"),

                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_tablerepas_activated(const QModelIndex &index)
{

        QString nb = ui->tablerepas->model()->data(index).toString() ;
           QSqlQuery qry;
           qry.prepare("SELECT * from repas where nb = '"+nb+"'") ;
           if (qry.exec())
           {
               while (qry.next()) {

                   ui->lineEmpl_2->setText(qry.value(0).toString()) ;

                   ui->lineEmpl_3->setText(qry.value(1).toString()) ;
                   ui->lineTache->setText(qry.value(2).toString()) ;
                   ui->lineTache_2->setText(qry.value(2).toString()) ;
                   ui->lineEmpl_4->setText(qry.value(2).toString()) ;
               }
           }
          QSqlQuery qry1;
          qry1.prepare("SELECT * from repas where nb = '"+nb+"'") ;
          if (qry1.exec())
          {
              while (qry1.next()) {
                  //ui->lineEdit_id_2->setText(qry1.value(0).toString()) ;
              }
          }


}
