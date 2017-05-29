#include "DbManager.h"
#include <iostream>
#include <QSqlQuery>

DbManager::DbManager(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open())
      std::cout<<"Erreur : la connexion à la base de données a échoué.";
    else
      std::cout<<"Base de données : connexion ok.";
}

bool DbManager::addNote(Note &n) {
    bool success = false;
    QSqlQuery query = n.getQuery();

    if(query.exec())
       success = true;
    else {
        //qDebug() << "addPerson error:  "<< query.lastError(); //il aime pas cette ligne là :(
    }

    return success;
}
