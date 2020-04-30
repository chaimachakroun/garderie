#include "eqp.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>

eqp::eqp()
{
id=0;
nom="";
dda="";
bloc="";
}
eqp::eqp(int id,QString nom,QString dda,QString bloc)
{
    this->id=id;
    this->nom=nom;
    this->dda=dda;
    this->bloc=bloc;
}
QString eqp::get_nom(){return nom;}
QString eqp::get_dda(){return dda;}
QString eqp::get_bloc(){return bloc;}
int eqp::get_id(){return id;}

bool eqp::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("INSERT INTO EQUIP (ID, NOM, DDA,BLOC) "
                        "VALUES (:id, :nom, :dda, :bloc)");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":dda",dda);
    query.bindValue(":bloc",bloc);
    return query.exec();
}
QSqlQueryModel * eqp::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from EQUIP");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("dda"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("bloc"));
return model;
}
bool eqp::supprimer(int nume)
{
    QSqlQuery q;
    QString res=QString::number(nume);
    q.prepare("delete from EQUIP where id=:id");
    q.bindValue(":id", res);
    return q.exec();
}
bool eqp::modifier()
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("UPDATE EQUIP SET nom=:modifNom, dda=:modifDda, bloc=:modifBloc WHERE id =:modifId");
    query.bindValue(":modifId",res);
    query.bindValue(":modifNom",nom);
    query.bindValue(":modifDda",dda);
    query.bindValue(":modifBloc",bloc);

    return query.exec();
}
QSqlQueryModel * eqp::tri_equip()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EQUIP order by id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date d'arrivee"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Bloc"));
        return model;
}

void eqp::clearTable(QTableView *table){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);}

void eqp::searchRegexp(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from EQUIP where regexp_like(id,:id );");
   query->bindValue(":id",x);


   if(x==0){qDebug("tawa 0");

   query->prepare("select * from EQUIP;");   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();

}
