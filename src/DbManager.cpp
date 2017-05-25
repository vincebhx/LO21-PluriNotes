#include "DbManager.h"
#include <iostream>

DbManager::DbManager(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open())
      std::cout<<"Erreur : la connexion à la base de données a échoué.";
    else
      std::cout<<"Base de données : connexion ok.";
}
