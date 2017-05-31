#include "DbManager.h"
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DbManager* DbManager::_instance = 0;

DbManager& DbManager::instance() {
    if(_instance == 0) _instance = new DbManager("notes.db");
    return *_instance;
}

DbManager::DbManager(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open())
      std::cout<<"Erreur : la connexion à la base de données a échoué."<<endl;
    else
      std::cout<<"Base de données : connexion ok."<<endl;
}

bool DbManager::addNote(Note &n) {
    bool success = false;
    QSqlQuery query = n.getQuery();

    if(query.exec())
        success = true;
    else
        qDebug() << "Erreur - DbManager::addNote : "<< query.lastError();

    return success;
}

bool DbManager::loadAll() {
    QSqlQuery queryArticle("SELECT * FROM Article ORDER BY id, version ASC;");


    /*
    QSqlQuery queryTache("SELECT * FROM Tache ORDER BY id, version ASC;");
    QSqlQuery queryImage("SELECT * FROM Media WHERE type = 'image' ORDER BY id, version ASC;");
    QSqlQuery queryAudio("SELECT * FROM Media WHERE type = 'audio' ORDER BY id, version ASC;");
    QSqlQuery queryVideo("SELECT * FROM Media WHERE type = 'video' ORDER BY id, version ASC;");
    */
    return true;
}

bool DbManager::saveAll() {
    return true;
}
