#include "connexion.h"
connexion::connexion()
{
}
bool connexion::ouvrirConnexion()
{
bool test=false;
    db=QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("Wael");//inserer nom de l'utilisateur
db.setPassword("root");//inserer mot de passe de cet utilisateur
if (db.open()) test = true;
return test;
}
void connexion::fermerConnexion()
{db.close();}
