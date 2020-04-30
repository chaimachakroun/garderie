#ifndef REPAS_H
#define REPAS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class repas
{
public:
    repas();
    repas(QString, QString, QString, int nb, QString datee);
       QString get_entree();
       QString get_plat();
       QString get_dessert();
       int get_nb();
       QString get_datee();

       bool ajouter();
       QSqlQueryModel * afficher();
       bool supprimer(int);
       bool modifier ();
   private:
       QString entree,plat,dessert,datee;
       int nb;
};

#endif // REPAS_H
