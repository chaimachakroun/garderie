#ifndef EQP_H
#define EQP_H
#include "QDate"
#include "QString"
#include "QSqlQueryModel"
#include"QTableView"


class eqp
{
public:
    eqp();
    eqp(int,QString,QString,QString);
    QString get_nom();
    QString get_dda();
    QString get_bloc();
    int get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * tri_equip();
    void clearTable(QTableView*);
       void searchRegexp(QTableView*,int);
private:
QString nom,dda,bloc;
int id;
};

#endif // EQP_H
