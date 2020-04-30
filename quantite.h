#ifndef QUANTITE_H
#define QUANTITE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class quantite
{
public:
    quantite();
     quantite(QString, QString,int);
     QString get_jour();
     QString get_ingredient();
     int get_qt();

     bool ajouter();
     QSqlQueryModel * afficher();
     bool supprimer(int);
     bool modifier ();
private:
    QString jour,ingredient;
    int qt;
};

#endif // QUANTITE_H
