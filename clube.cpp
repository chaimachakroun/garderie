#include "clube.h"
#include "ui_clube.h"
#include "clb.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QPrinter>
#include"QFileDialog"
#include"QTextDocument"
Clube::Clube(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Clube)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmpclb.afficher());
    ui-> lineEdit->setValidator(new QIntValidator(0, 99999999, this));
    ui-> lineEdit_2->setInputMask("aaaaaaaaaaaaaaa");
    ui-> lineEdit_3->setValidator(new QIntValidator(0,99999999, this));
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
