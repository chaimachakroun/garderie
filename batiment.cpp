#include "batiment.h"
#include "ui_batiment.h"
#include "QMessageBox"
#include "crudbatiment.h"
#include "QTextDocument"
#include "QFileDialog"
#include <QPrinter>


batiment::batiment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::batiment)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmpbatiment.afficher());
    ui-> lineEdit_5->setValidator(new QIntValidator(0, 99999999, this));
    ui-> lineEdit->setValidator(new QIntValidator(0, 99999999, this));
    ui-> lineEdit_2->setValidator(new QIntValidator(0, 99999999, this));
}

batiment::~batiment()
{
    delete ui;
}

void batiment::on_pushButton_7_clicked()
{
    int numb = ui->lineEdit_5->text().toInt();
    QString nomb =ui ->comboBox->currentText();
    int nbrs =ui->lineEdit->text().toInt();
    int nbrem =ui->lineEdit_2->text().toInt();
    crudbatiment c (numb,nomb,nbrs,nbrem);
    bool test=c.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ajouter un batiment"),
                                      QObject::tr("ajout avec succés.\n"
                                                  "cliquez annuler pour sortir."), QMessageBox::Cancel);
                  }
                      else
                          QMessageBox::information(nullptr, QObject::tr("ajouter une batiment"),
                                      QObject::tr("erreur d'ajout.\n"
                                                  "cliquez annuler pour sortir."), QMessageBox::Cancel);
}

void batiment::on_pushButton_10_clicked()
{
    int numb = ui->lineEdit_4->text().toInt();
    bool test =tmpbatiment.supprimer(numb);
    if (test)
    {
        ui->tableView->setModel(tmpbatiment.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer un batiment"),
                                      QObject::tr("suppression avec succés.\n"
                                                  "cliquez annuler pour sortir."), QMessageBox::Cancel);
                  }
                      else
                          QMessageBox::information(nullptr, QObject::tr("supprimer un batiment"),
                                      QObject::tr("erreur de suppression.\n"
                                                  "cliquez annuler pour sortir."), QMessageBox::Cancel);
}

void batiment::on_pushButton_12_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES COMPTES </font><br /> <br /> "));
        str.append("<table border=1><tr>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">num batiment</font>&nbsp;&nbsp;"+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">Nom batiment </font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">nbr salles</font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">nbr employés</font>&nbsp;&nbsp;"+"</td>");
        QSqlQuery * query=new QSqlQuery();
        query->exec("SELECT numb,nomb,nbrs,nbrem FROM BATIMENT");
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
        QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des batiment","PDF(*.pdf");
         if(path.isEmpty()) return;
         printer.setOutputFileName(path);
         QTextDocument doc;
         doc.setHtml(str);
         doc.print(&printer);
}



void batiment::on_pushButton_13_clicked()
{
    ui->tableView->setModel(tmpbatiment.tri_batiment());
}

void batiment::on_pushButton_11_clicked()
{
    int numb = ui->lineEdit_5->text().toInt();
          QString nomb = ui->comboBox->currentText();
          int nbrs = ui->lineEdit->text().toInt();
          int nbrem = ui->lineEdit_2->text().toInt();
         crudbatiment c (numb,nomb,nbrs,nbrem);
          bool test= c.modifier();
          if(test)
          {
              ui->tableView->setModel(tmpbatiment.afficher());
              QMessageBox::information(nullptr, QObject::tr("modifer  une salle"),
                                                    QObject::tr("modification avec succés.\n"
                                                                "cliquez annuler pour sortir."), QMessageBox::Cancel);
                                }
                                    else
                                        QMessageBox::information(nullptr, QObject::tr("modifier une salle"),
                                                    QObject::tr("erreur de modification.\n"
                                                                "cliquez annuler pour sortir."), QMessageBox::Cancel);
}


void batiment::on_tableView_activated(const QModelIndex &index)
{
    QString val= ui->tableView->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from batiment where numb= '"+val+"' ");
    if(query.exec())
    {
        while(query.next())
        {



            ui->lineEdit_5->setText(query.value(0).toString());

            ui->comboBox->setCurrentText(query.value(1).toString());
            ui->lineEdit->setText(query.value(2).toString());
            ui->lineEdit_2->setText(query.value(3).toString());
             ui->lineEdit_4->setText(query.value(0).toString());


        }
    }
    else
        QMessageBox::information(nullptr, QObject::tr("Selection"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}

void batiment::on_lineEdit_3_textChanged(const QString &arg1)
{
    crudbatiment c;
        c.clearTable(ui->tableView);
        int mat=ui->lineEdit_3->text().toInt();
        c.searchRegexp(ui->tableView,mat);
}

