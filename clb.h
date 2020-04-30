#ifndef CLB_H
#define CLB_H
#include "QDate"
#include "QString"
#include "QSqlQueryModel"
#include"QTableView"

class clb
{
public:
    clb();
    clb(int,QString,QString,QString);
    QString get_nom();
    QString get_ddc();
    QString get_type();
    int get_num();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * tri_club();
    void clearTable(QTableView*);
       void searchRegexp(QTableView*,int);
private:
QString nom,ddc,type;
int num;


};

#endif // CLB_H
