#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include <QMessageBox>
#include "quantite.h"
#include <QPixmap>
#include <QPrinter>
#include <QFileDialog>
#include<QTextDocument>

MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    ui->tablequantite->setModel(tableau1.afficher()) ;
    QPixmap pix("C:/Users/Utilisateur/Documents/garderie2/lepetit.png");
        ui->label->setPixmap(pix) ;
}

MainWindow1::~MainWindow1()
{
    delete ui;
}


void MainWindow1::on_sauvegarder_clicked()
{
    QString jour= ui->lineEmpl_4->text();
    QString ingredients= ui->lineEmpl_2->text();
    int qt = ui->lineEmpl_3->text().toInt();
 quantite q(jour,ingredients,qt);
  bool test=q.ajouter();
  if(test)
{

      ui->tablequantite->setModel(tableau1.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter la quantité"),
                  QObject::tr("quantité ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter la quantité"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);



}
void MainWindow1::on_pushButton_4_clicked()
{
    int qt = ui->lineTache_3->text().toInt() ;
    bool test=tableau1.supprimer(qt);
    if(test)
    {
        ui->tablequantite->setModel(tableau1.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer la quantite saisie"),
                    QObject::tr("quantité supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer la quantité"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow1::on_pushButton_3_clicked()
{
    QString jour= ui->lineEmpl_4->text();
    QString ingredients= ui->lineEmpl_2->text();
    int qt = ui->lineEmpl_3->text().toInt();
 quantite q(jour,ingredients,qt);
  bool test=q.modifier();
  if(test)
    {
       ui->tablequantite->setModel(tableau1.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Modifier quantite"),
                      QObject::tr("quantité modifier.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Modifier la quantité"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow1::on_sauvegarder_4_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> Quantités </font><br /> <br /> "));
        str.append("<table border=1><tr>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">jour</font>&nbsp;&nbsp;"+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">ingrédients </font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">quantités</font>&nbsp;&nbsp;")+"</td>");



        QSqlQuery * query=new QSqlQuery();
        query->exec("SELECT jour,ingredient,qt FROM quantite");
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
        QString path= QFileDialog::getSaveFileName(NULL,"imprimer","quantite","PDF(*.pdf");
         if(path.isEmpty()) return;
         printer.setOutputFileName(path);
         QTextDocument doc;
         doc.setHtml(str);
         doc.print(&printer);
}

void MainWindow1::on_sauvegarder_5_clicked()
{
    int qt = ui->lineEmpl_3->text().toInt();
        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * from quantite where qt like concat (:qt,'%')");
        qry->bindValue(":qt",qt);
        qry->exec();
        model->setQuery(*qry);
        ui->tablequantite->setModel(model) ;

}

void MainWindow1::on_tablequantite_activated(const QModelIndex &index)
{
    QString qt = ui->tablequantite->model()->data(index).toString() ;
       QSqlQuery qry;
       qry.prepare("SELECT * from quantite where qt = '"+qt+"'") ;
       if (qry.exec())
       {
           while (qry.next()) {

               ui->lineEmpl_4->setText(qry.value(0).toString()) ;

               ui->lineEmpl_2->setText(qry.value(1).toString()) ;
               ui->lineEmpl_3->setText(qry.value(2).toString()) ;
           }
       }
      QSqlQuery qry1;
      qry1.prepare("SELECT * from quantite where qt = '"+qt+"'") ;
      if (qry1.exec())
      {
          while (qry1.next()) {
              //ui->lineEdit_id_2->setText(qry1.value(0).toString()) ;
          }
      }
}
