#include "quantite.h"

quantite::quantite()
{
    jour="" ;
    ingredient="" ;
    qt=0;
}
quantite::quantite(QString jour,QString ingredient,int qt)
{
  this->jour=jour;
  this->ingredient=ingredient;
    this->qt=qt;
}
QString quantite::get_jour(){return  jour;}
QString quantite::get_ingredient(){return ingredient;}
int quantite::get_qt(){return qt;}

bool quantite::ajouter()
{
QSqlQuery query;
QString res= QString::number(qt);
query.prepare("INSERT INTO QUANTITE (JOUR, INGREDIENT,QT) "
                    "VALUES (:jour, :ingredient, :qt)");
query.bindValue(":jour", jour);
query.bindValue(":ingredient", ingredient);
query.bindValue(":qt", res);


return    query.exec();
}



QSqlQueryModel * quantite::afficher()
{
 QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from QUANTITE ORDER BY QT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("jour"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ingredient"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("qt"));

    return model;
}



bool quantite::supprimer(int qt)
{
QSqlQuery query;
QString res= QString::number(qt);
query.prepare("Delete from QUANTITE where qt = :qt ");
query.bindValue(":qt", res);
return    query.exec();
}


bool quantite::modifier()
{
    QSqlQuery query;
    QString res= QString::number(qt);
    query.prepare("UPDATE QUANTITE SET jour='"+jour+"',ingredient='"+ingredient+"',qt='"+res+"'where jour='"+jour+"'  ;");
    query.bindValue(":qt",res);
    query.bindValue(":jour", jour);
    query.bindValue(":ingredient", ingredient);
    return    query.exec();
}
