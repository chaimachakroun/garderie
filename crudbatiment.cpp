#include "crudbatiment.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

crudbatiment::crudbatiment()
{
     numb=0;
    nomb="";
    nbrs=0;
    nbrem=0;
}
crudbatiment::crudbatiment(int numb,QString nomb,int nbrs,int nbrem)
{
    this ->numb=numb;
    this ->nomb=nomb;
    this ->nbrs=nbrs;
    this ->nbrem=nbrem;
}
int crudbatiment::get_numb(){return numb;}
QString crudbatiment::get_nomb() {return nomb;}
int crudbatiment::get_nbrs() {return nbrs;}
 int crudbatiment::get_nbrem()  {return nbrem;}

 bool crudbatiment::ajouter()
 {
     QSqlQuery query;
     QString res=QString::number(numb);

     query.prepare("INSERT INTO BATIMENT (NUMB, NOMB, NBRS,NBREM) "
                         "VALUES (:numb, :nomb, :nbrs, :nbrem)");
     query.bindValue(":numb",res);
     query.bindValue(":nomb",nomb);
     query.bindValue(":nbrs",nbrs);
     query.bindValue(":nbrem",nbrem);
     return query.exec();
 }
 QSqlQueryModel *crudbatiment::afficher()
 {
     QSqlQueryModel *model =new QSqlQueryModel();
     model ->setQuery("select * from BATIMENT");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("numb"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("nomb"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("nbrs"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("nbrem"));
     return model;

 }

 bool crudbatiment::supprimer(int numbb)
 {
     QSqlQuery query;
     QString res =QString::number(numbb);
     query.prepare("Delete from BATIMENT where numb=:numb ");
     query.bindValue(":numb",res);
     return query.exec();
 }
 QSqlQueryModel * crudbatiment::tri_batiment()
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from BATIMENT order by numb");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("numb"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nomb "));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nbrs"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("nbrem"));
         return model;
 }
 bool crudbatiment::modifier()
 {
     QSqlQuery query;
     QString res=QString::number(numb);
     query.prepare("UPDATE batiment SET nomb=:modifNomb, nbrs=:modifNbrs, nbrem=:modifNbrem WHERE numb =:modifNumb");
     query.bindValue(":modifNumb",res);
     query.bindValue(":modifNomb",nomb);
     query.bindValue(":modifNbrs",nbrs);
     query.bindValue(":modifNbrem",nbrem);

     return query.exec();
 }

 void crudbatiment::clearTable(QTableView *table){
     QSqlQueryModel *model=new QSqlQueryModel();
     model->clear();
     table->setModel(model);}

 void crudbatiment::searchRegexp(QTableView *table, int x)
 {
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from batiment where regexp_like(numb,:numb );");
    query->bindValue(":numb",x);


    if(x==0){qDebug("tawa 0");

    query->prepare("select * from batiment;");   }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

 }
