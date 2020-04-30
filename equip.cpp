#include "equip.h"
#include "ui_equip.h"
#include "eqp.h"
#include "QMessageBox"
#include<QSqlQuery>
#include<QPrinter>
#include"QFileDialog"
#include"QTextDocument"
equip::equip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::equip)
{
    ui->setupUi(this);
    eqp E;
     ui->tableView->setModel(E.afficher());
     ui-> lineEdit->setValidator(new QIntValidator(0, 99999999, this));
     ui-> lineEdit_2->setInputMask("aaaaaaaaaa");
     ui-> lineEdit_3->setValidator(new QIntValidator(0, 99999999, this));
     ui-> lineEdit_4->setValidator(new QIntValidator(0, 99999999, this));

}

equip::~equip()
{
    delete ui;
}

void equip::on_pushButton_2_clicked()
{
    int id=ui->lineEdit->text().toInt();
    QString nom=ui->lineEdit_2->text();
    QString dda=ui->lineEdit_3->text();
    QString bloc=ui->lineEdit_4->text();
    eqp E(id,nom,dda,bloc);
    bool test=E.ajouter();
    if(test)
    {
     ui->tableView->setModel(E.afficher());
     QMessageBox::information(nullptr, QObject::tr("ajouter un equipement"),
                                           QObject::tr("ajout avec succés.\n"
                                                       "cliquez annuler pour sortir."), QMessageBox::Cancel);
                       }
                           else
                               QMessageBox::information(nullptr, QObject::tr("ajouter un equipement"),
                                           QObject::tr("erreur d'ajout.\n"
                                                       "cliquez annuler pour sortir."), QMessageBox::Cancel);
}

void equip::on_pushButton_3_clicked()
{
    int id = ui->lineEdit_5->text().toInt();
    bool test = tmpeqp.supprimer(id);
    if(test)
{
        ui->tableView->setModel(tmpeqp.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer un equipement"),
                                              QObject::tr("suppression avec succés.\n"
                                                          "cliquez annuler pour sortir."), QMessageBox::Cancel);
                          }
                              else
                                  QMessageBox::information(nullptr, QObject::tr("supprimer un equipement"),
                                              QObject::tr("erreur de suppression.\n"
                                                          "cliquez annuler pour sortir."), QMessageBox::Cancel);
}

void equip::on_pushButton_5_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES COMPTES </font><br /> <br /> "));
        str.append("<table border=1><tr>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">Id</font>&nbsp;&nbsp;"+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">Nom </font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">Date d'arrivée</font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">Bloc</font>&nbsp;&nbsp;"+"</td>");

        QSqlQuery * query=new QSqlQuery();
        query->exec("SELECT id,nom,dda,bloc FROM EQUIP");
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
        QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des equipements","PDF(*.pdf");
         if(path.isEmpty()) return;
         printer.setOutputFileName(path);
         QTextDocument doc;
         doc.setHtml(str);
         doc.print(&printer);
}

void equip::on_pushButton_6_clicked()
{
    int idd = ui->lineEdit_7->text().toInt();
        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * from EQUIP where id like concat (:idd,'%')");
        qry->bindValue(":idd",idd);
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model) ;
}

void equip::on_pushButton_7_clicked()
{
    ui->tableView->setModel(tmpeqp.tri_equip());
}

void equip::on_tableView_activated(const QModelIndex &index)
{
    QString val= ui->tableView->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from EQUIP where id= '"+val+"' ");
    if(query.exec())
    {
        while(query.next())
        {



            ui->lineEdit_5->setText(query.value(0).toString());


            ui->lineEdit->setText(query.value(2).toString());
            ui->lineEdit_2->setText(query.value(3).toString());
             ui->lineEdit_4->setText(query.value(0).toString());
              ui->lineEdit_7->setText(query.value(0).toString());


        }
    }
    else
        QMessageBox::information(nullptr, QObject::tr("Selection"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}

void equip::on_lineEdit_7_textChanged(const QString &arg1)
{
    eqp e;
        e.clearTable(ui->tableView);
        int mat=ui->lineEdit_3->text().toInt();
        e.searchRegexp(ui->tableView,mat);
}

void equip::on_pushButton_4_clicked()
{
    int id = ui->lineEdit->text().toInt();
    QString nom = ui->lineEdit_2->text();
    QString dda = ui->lineEdit_3->text();
    QString bloc = ui->lineEdit_4->text();
    eqp E(id,nom,dda,bloc);
    bool test= E.modifier();
    if(test)
    {
        ui->tableView->setModel(tmpeqp.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifer  un club"),
                                              QObject::tr("modification avec succés.\n"
                                                          "cliquez annuler pour sortir."), QMessageBox::Cancel);
                          }
                              else
                                  QMessageBox::information(nullptr, QObject::tr("modifier un club"),
                                              QObject::tr("erreur de modification.\n"
                                                          "cliquez annuler pour sortir."), QMessageBox::Cancel);
}
