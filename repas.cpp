#include "repas.h"

repas::repas()
{
  entree="" ;
  plat="" ;
  dessert="";
  nb=0;
  datee="" ;
}
repas::repas(QString entree,QString plat,QString dessert,int nb,QString datee)
{
  this->entree=entree;
  this->plat=plat;
  this->dessert=dessert;
    this->nb=nb;
    this->datee=datee;
}
QString repas::get_entree(){return  entree;}
QString repas::get_plat(){return plat;}
QString repas::get_dessert(){return dessert;}
int repas::get_nb(){return nb;}
QString repas::get_datee(){return  datee;}


bool repas::ajouter()
{
QSqlQuery query;
QString res= QString::number(nb);
query.prepare("INSERT INTO REPAS (ENTREE, PLAT, DESSERT,NB,DATEE) "
                    "VALUES (:entree, :plat, :dessert, :nb, :datee)");
query.bindValue(":entree", entree);
query.bindValue(":plat", plat);
query.bindValue(":dessert", dessert);
query.bindValue(":nb", res);
query.bindValue(":datee", datee);

return    query.exec();
}

QSqlQueryModel * repas::afficher()
{
 QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from REPAS ORDER BY NB");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("entree"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("plat "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("dessert"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("datee"));
    return model;
}

bool repas::supprimer(int nb)
{
QSqlQuery query;
QString res= QString::number(nb);
query.prepare("Delete from REPAS where nb = :nb ");
query.bindValue(":nb", res);
return    query.exec();
}

bool repas::modifier()
{
    QSqlQuery query;
    QString res= QString::number(nb);
    query.prepare("UPDATE REPAS SET entree='"+entree+"',plat='"+plat+"',dessert='"+dessert+"',nb='"+res+"'where datee='"+datee+"'  ;");
    query.bindValue(":nb",res);
    query.bindValue(":entree", entree);
    query.bindValue(":plat", plat);
    query.bindValue(":dessert", dessert);
    query.bindValue(":datee", datee);
    return    query.exec();
}




