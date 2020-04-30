#include "crudsalle.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

crudsalle::crudsalle()
{
nom="";
num=0;
types="";
typeb="";
}
crudsalle::crudsalle(QString nom,int num,QString types,QString typeb)
{
    this ->nom=nom;
    this ->num=num;
    this ->types=types;
    this ->typeb=typeb;
}
QString crudsalle::get_nom(){return nom;}
int crudsalle::get_num() {return num;}
QString crudsalle::get_types() {return types;}
 QString crudsalle::get_typeb()  {return typeb;}


bool crudsalle::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(num);

    query.prepare("INSERT INTO SALLE (NOM, NUM, TYPES,TYPEB) "
                        "VALUES (:nom, :num, :types, :typeb)");
    query.bindValue(":nom",nom);
    query.bindValue(":num",res);
    query.bindValue(":types",types);
    query.bindValue(":typeb",typeb);
    return query.exec();
}
QSqlQueryModel *crudsalle::afficher()
{
    QSqlQueryModel *model =new QSqlQueryModel();
    model ->setQuery("select * from SALLE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("num"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("types"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("typeb"));
    return model;

}
bool crudsalle::supprimer(int numm)
{
    QSqlQuery query;
    QString res =QString::number(numm);
    query.prepare("Delete from SALLE where num=:num ");
    query.bindValue(":num",res);
    return query.exec();
}
QSqlQueryModel * crudsalle::tri_salle()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from SALLE order by num");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Noms "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("types"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typeb"));
        return model;
}

bool crudsalle:: recherche(int numm)
{
    QSqlQuery query;
      QString res=QString::number(num);
    query.prepare("select * from salle where num=:numm");
    query.bindValue(":num",res);
    return query.exec() ;
}


bool crudsalle::modifier()
{
    QSqlQuery q;
        QString res=QString::number(num);
        q.prepare("UPDATE SALLE SET num=:num , nom=:nom , types=:types,typeb=:typeb  WHERE num=:num");
        q.bindValue(":num",res);
        q.bindValue(":nom",nom);
        q.bindValue(":types",types);
        q.bindValue(":typeb",typeb);
        return(q.exec());
}

void crudsalle::clearTable(QTableView *table){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);}

void crudsalle::searchRegexp(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from salle where regexp_like(num,:num );");
   query->bindValue(":num",x);


   if(x==0){qDebug("tawa 0");

   query->prepare("select * from salle;");   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();

}


