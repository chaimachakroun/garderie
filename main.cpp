#include "MainWindow.h"
#include "connexion.h"
#include <QDebug>
#include<QMessageBox>
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion C;
     bool test = C.ouvrirConnexion();
  Club Cl;
    if(test)
  {
          Cl.show();
          QMessageBox::information(nullptr, QObject::tr("database is  open"),
                      QObject::tr("connexion ok.\n""Click Cancel to exit."), QMessageBox::Cancel);
      }
            else
                 QMessageBox::information(nullptr, QObject::tr("database is not open"),
                             QObject::tr("Echec de la connexion.\n""Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
