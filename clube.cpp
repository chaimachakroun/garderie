#include "clube.h"
#include "ui_clube.h"
#include "clb.h"
#include "QMessageBox"
#include "QTextDocument"
#include "QFileDialog"
#include<QSqlQuery>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include"QSortFilterProxyModel"
QT_CHARTS_USE_NAMESPACE
Clube::Clube(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Clube)
{
    //ui->setupUi(this);
    ui->tableView->setModel(tmpclb.afficher());
  //  ui-> lineEdit->setValidator(new QIntValidator(0, 99999999, this));
    ui-> lineEdit_2->setInputMask("aaaaaaaaaaaaaaa");
    //ui-> lineEdit_3->setValidator(new QIntValidator(0,99999999, this));
    clb C;

}

Clube::~Clube()
{
    delete ui;
}


void Clube::on_pushButton_2_clicked()
{
    int num=ui->lineEdit->text().toInt();
    QString nom=ui->lineEdit_2->text();
    QString ddc=ui->lineEdit_3->text();
    QString type=ui->comboBox->currentText();
   clb C(num,nom,ddc,type);
    bool test=C.ajouter();
    if(test)
    {
     ui->tableView->setModel(C.afficher());
     QMessageBox::information(nullptr, QObject::tr("ajouter un club"),
                                           QObject::tr("ajout avec succés.\n"
                                                       "cliquez annuler pour sortir."), QMessageBox::Cancel);
                       }
                           else
                               QMessageBox::information(nullptr, QObject::tr("ajouter un club"),
                                           QObject::tr("erreur d'ajout.\n"
                                                       "cliquez annuler pour sortir."), QMessageBox::Cancel);
}


void Clube::on_pushButton_3_clicked()
{
    int num = ui->lineEdit->text().toInt();
    bool test = tmpclb.supprimer(num);
    if(test)
{
        ui->tableView->setModel(tmpclb.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer un club"),
                                              QObject::tr("suppression avec succés.\n"
                                                          "cliquez annuler pour sortir."), QMessageBox::Cancel);
                          }
                              else
                                  QMessageBox::information(nullptr, QObject::tr("supprimer un club"),
                                              QObject::tr("erreur de suppression.\n"
                                                          "cliquez annuler pour sortir."), QMessageBox::Cancel);
    }






void Clube::on_pushButton_4_clicked()
{
   int num = ui->lineEdit->text().toInt();
   QString nom = ui->lineEdit_2->text();
   QString ddc = ui->lineEdit_3->text();
   QString type = ui->comboBox->currentText();
   clb C(num,nom,ddc,type);
   bool test= C.modifier();
   if(test)
   {
       ui->tableView->setModel(tmpclb.afficher());
       QMessageBox::information(nullptr, QObject::tr("modifer  un club"),
                                             QObject::tr("modification avec succés.\n"
                                                         "cliquez annuler pour sortir."), QMessageBox::Cancel);
                         }
                             else
                                 QMessageBox::information(nullptr, QObject::tr("modifier un club"),
                                             QObject::tr("erreur de modification.\n"
                                                         "cliquez annuler pour sortir."), QMessageBox::Cancel);
   }


void Clube::on_pushButton_5_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES COMPTES </font><br /> <br /> "));
        str.append("<table border=1><tr>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">Num</font>&nbsp;&nbsp;"+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">Nom </font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">Date de creation</font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">Type</font>&nbsp;&nbsp;"+"</td>");

        QSqlQuery * query=new QSqlQuery();
        query->exec("SELECT num,nom,ddc,type FROM CLUB");
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
        QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des clubs","PDF(*.pdf");
         if(path.isEmpty()) return;
         printer.setOutputFileName(path);
         QTextDocument doc;
         doc.setHtml(str);
         doc.print(&printer);
}

void Clube::on_pushButton_6_clicked()
{
    int numm = ui->lineEdit_6->text().toInt();
        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * from CLUB where num like concat (:numm,'%')");
        qry->bindValue(":numm",numm);
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model) ;
}

void Clube::on_pushButton_7_clicked()
{
    ui->tableView->setModel(tmpclb.tri_club());
}

void Clube::on_tableView_activated(const QModelIndex &index)
{
    QString val= ui->tableView->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from CLUB where num= '"+val+"' ");
    if(query.exec())
    {
        while(query.next())
        {



            ui->lineEdit_5->setText(query.value(0).toString());

            ui->comboBox->setCurrentText(query.value(1).toString());
            ui->lineEdit->setText(query.value(2).toString());
            ui->lineEdit_2->setText(query.value(3).toString());
             ui->lineEdit_6->setText(query.value(0).toString());



        }
    }
    else
        QMessageBox::information(nullptr, QObject::tr("Selection"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}

void Clube::on_lineEdit_6_textChanged(const QString &arg1)
{
    clb c;
        c.clearTable(ui->tableView);
        int mat=ui->lineEdit_6->text().toInt();
        c.searchRegexp(ui->tableView,mat);
}

void Clube::on_pushButton_8_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
               model->setQuery("select * from CLUB where TYPE =:chant");
               float bat1=model->rowCount();
               model->setQuery("select * from CLUB where TYPE=:musique ");
               float bat2=model->rowCount();
               model->setQuery("select * from CLUB where TYPE=:theatre ");
               float bat3=model->rowCount();
               model->setQuery("select * from CLUB where TYPE=:arts plastique ");
               float bat4=model->rowCount();
               model->setQuery("select * from CLUB where TYPE=:dance ");
               float bat5=model->rowCount();
               float total=bat1+bat2+bat3+bat4+bat5;
               QString a=QString("club chant  "+QString::number((bat1*100)/total,'f',2)+"%" );
               QString b=QString("club musique  "+QString::number((bat2*100)/total,'f',2)+"%" );
               QString c=QString("club theatre  "+QString::number((bat3*100)/total,'f',2)+"%" );
               QString d=QString("club arts plastique  "+QString::number((bat4*100)/total,'f',2)+"%" );
               QString e=QString("club dance  "+QString::number((bat5*100)/total,'f',2)+"%" );
               QPieSeries *series = new QPieSeries();
               series->append(a,bat1);
               series->append(b,bat2);
               series->append(c,bat3);
                series->append(d,bat4);
                 series->append(e,bat5);
       if (bat1!=0)
       {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
       if ( bat2!=0)
       {
                // Add label, explode and define brush for 2nd slice
                QPieSlice *slice1 = series->slices().at(1);
                //slice1->setExploded();
                slice1->setLabelVisible();
       }
       if(bat3!=0)
       {
                // Add labels to rest of slices
                QPieSlice *slice2 = series->slices().at(2);
                //slice1->setExploded();
                slice2->setLabelVisible();
       }
       if(bat4!=0)
       {
                // Add labels to rest of slices
                QPieSlice *slice3 = series->slices().at(3);
                //slice1->setExploded();
                slice3->setLabelVisible();
       }
       if(bat5!=0)
       {
                // Add labels to rest of slices
                QPieSlice *slice4 = series->slices().at(4);
                //slice1->setExploded();
                slice4->setLabelVisible();
       }
               // Create the chart widget
               QChart *chart = new QChart();
               // Add data to chart with title and hide legend
               chart->addSeries(series);
               chart->setTitle("Pourcentage Par club :totale de "+ QString::number(total));
               chart->legend()->hide();
               // Used to display the chart
               QChartView *chartView = new QChartView(chart);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->resize(1000,500);
               chartView->show();
}
