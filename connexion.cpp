#include "connexion.h"

connexion::connexion()
{

}
bool connexion::ouvrirConnexion()
{
bool test=false;
    db=QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("chaima");//inserer nom de l'utilisateur
db.setPassword("chaima");//inserer mot de passe de cet utilisateur


if (db.open()) test = true;


return test;

}
void connexion::fermerConnexion()
{db.close();}
