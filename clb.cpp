#include "clb.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>

clb::clb()
{
num=0;
nom="";
ddc="";
type="";
}
clb::clb(int num,QString nom,QString ddc,QString type)
{
    this->num=num;
    this->nom=nom;
    this->ddc=ddc;
    this->type=type;
}
QString clb::get_nom(){return nom;}
QString clb::get_ddc(){return ddc;}
QString clb::get_type(){return type;}
int clb::get_num(){return num;}

bool clb::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(num);
    query.prepare("INSERT INTO CLUB (NUM, NOM, DDC,TYPE) "
                        "VALUES (:num, :nom, :ddc, :type)");
    query.bindValue(":num",res);
    query.bindValue(":nom",nom);
    query.bindValue(":ddc",ddc);
    query.bindValue(":type",type);
    return query.exec();
}
QSqlQueryModel * clb::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from CLUB");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("num"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ddc"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("type"));
return model;
}
bool clb::supprimer(int nume)
{
    QSqlQuery q;
    QString res=QString::number(nume);
    q.prepare("delete from CLUB where num=:num");
    q.bindValue(":num", res);
    return q.exec();
}
bool clb::modifier()
{
    QSqlQuery query;
    QString res=QString::number(num);
    query.prepare("UPDATE Club SET nom=:modifNom, ddc=:modifDdc, type=:modifType WHERE num =:modifNum");
    query.bindValue(":modifNum",res);
    query.bindValue(":modifNom",nom);
    query.bindValue(":modifDdc",ddc);
    query.bindValue(":modifType",type);

    return query.exec();
}
QSqlQueryModel * clb::tri_club()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CLUB order by num");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de creation"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
        return model;
}
void clb::clearTable(QTableView *table){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);}

void clb::searchRegexp(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from CLUB where regexp_like(num,:num );");
   query->bindValue(":num",x);


   if(x==0){qDebug("tawa 0");

   query->prepare("select * from CLUB;");   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();

}
