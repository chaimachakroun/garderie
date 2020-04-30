#include "salle.h"
#include "ui_salle.h"
#include "crudsalle.h"
#include "QMessageBox"
#include "QTextDocument"
#include "QFileDialog"
#include <QPrinter>


salle::salle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::salle)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmpsalle.afficher());
    ui-> lineEdit->setValidator(new QIntValidator(0, 99999999, this));
   ui->lineEdit_2->setInputMask("aaaaaaaaaaaaaa");

}

salle::~salle()
{
    delete ui;
}

void salle::on_pushButton_7_clicked()
{
    QString nom = ui->lineEdit_2->text();
    int num =ui ->lineEdit->text().toInt();
    QString types =ui->comboBox->currentText();
    QString typeb =ui->comboBox_2->currentText();
    crudsalle c (nom,num,types,typeb);
    bool test=c.ajouter();
    if (test)
    {  ui->tableView->setModel(tmpsalle.afficher()); //
        QMessageBox::information(nullptr, QObject::tr("ajouter une salle"),
                                      QObject::tr("ajout avec succés.\n"
                                                  "cliquez annuler pour sortir."), QMessageBox::Cancel);
                  }
                      else
                          QMessageBox::information(nullptr, QObject::tr("ajouter une salle"),
                                      QObject::tr("erreur d'ajout.\n"
                                                  "cliquez annuler pour sortir."), QMessageBox::Cancel);

}

void salle::on_pushButton_10_clicked()
{
    int num = ui->lineEdit_4->text().toInt();
    bool test =tmpsalle.supprimer(num);
    if (test)
    {
        ui->tableView->setModel(tmpsalle.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer une salle"),
                                      QObject::tr("suppression avec succés.\n"
                                                  "cliquez annuler pour sortir."), QMessageBox::Cancel);
                  }
                      else
                          QMessageBox::information(nullptr, QObject::tr("supprimer une salle"),
                                      QObject::tr("erreur de suppression.\n"
                                                  "cliquez annuler pour sortir."), QMessageBox::Cancel);


}

void salle::on_pushButton_12_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES COMPTES </font><br /> <br /> "));
        str.append("<table border=1><tr>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">num salle</font>&nbsp;&nbsp;"+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">Nom salle </font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">type salle</font>&nbsp;&nbsp;")+"</td>");
        str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">type batiment</font>&nbsp;&nbsp;"+"</td>");
        QSqlQuery * query=new QSqlQuery();
        query->exec("SELECT nom,num,types,typeb FROM SALLE");
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
        QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des salles","PDF(*.pdf");
         if(path.isEmpty()) return;
         printer.setOutputFileName(path);
         QTextDocument doc;
         doc.setHtml(str);
         doc.print(&printer);
}



void salle::on_pushButton_13_clicked()
{
   ui->tableView->setModel(tmpsalle.tri_salle());
}

void salle::on_pushButton_11_clicked()
{
    int num = ui->lineEdit->text().toInt();
          QString nom = ui->lineEdit_2->text();
          QString types = ui->comboBox->currentText();
          QString typeb = ui->comboBox_2->currentText();
         crudsalle c (nom,num,types,typeb);

          bool test= c.modifier();
          if(test)
          {
              ui->tableView->setModel(tmpsalle.afficher());
              QMessageBox::information(nullptr, QObject::tr("modifer  une salle"),
                                                    QObject::tr("modification avec succés.\n"
                                                                "cliquez annuler pour sortir."), QMessageBox::Cancel);
                                }
                                    else
                                        QMessageBox::information(nullptr, QObject::tr("modifier une salle"),
                                                    QObject::tr("erreur de modification.\n"
                                                                "cliquez annuler pour sortir."), QMessageBox::Cancel);
}

void salle::on_tableView_activated(const QModelIndex &index)
{
    QString val= ui->tableView->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from salle where num= '"+val+"' ");
    if(query.exec())
    {
        while(query.next())
        {



            ui->lineEdit_2->setText(query.value(0).toString());


            ui->lineEdit->setText(query.value(1).toString());

            ui->comboBox->setCurrentText(query.value(2).toString());
            ui->comboBox_2->setCurrentText(query.value(3).toString());

   ui->lineEdit_4->setText(query.value(1).toString());

        }
    }
    else
        QMessageBox::information(nullptr, QObject::tr("Selection"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}

void salle::on_lineEdit_3_textChanged(const QString &arg1)
{

    crudsalle c;
        c.clearTable(ui->tableView);
        int mat=ui->lineEdit_3->text().toInt();
        c.searchRegexp(ui->tableView,mat);
}
