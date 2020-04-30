#ifndef CRUDBATIMENT_H
#define CRUDBATIMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>

class crudbatiment
{
public:
    crudbatiment();
    crudbatiment(int,QString,int,int);
    int get_numb();
    QString get_nomb();
    int get_nbrs();
    int get_nbrem();
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer (int numm);
     QSqlQueryModel *tri_batiment();
     bool modifier();
     void clearTable(QTableView*);
        void searchRegexp(QTableView*,int);
private:
    QString nomb;
    int numb,nbrs,nbrem;
};

#endif // CRUDBATIMENT_H
