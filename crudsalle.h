#ifndef CRUDSALLE_H
#define CRUDSALLE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>

class crudsalle
{
public:

    crudsalle();
    crudsalle(QString,int,QString,QString);
    QString get_nom();
    int get_num();
    QString get_types();
    QString get_typeb();
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer (int numm);
    QSqlQueryModel *tri_salle();
     bool  recherche(int);
    bool modifier();
    void clearTable(QTableView*);
       void searchRegexp(QTableView*,int);

private:
    QString nom,types,typeb;
    int num;


};

#endif // CRUDSALLE_H
