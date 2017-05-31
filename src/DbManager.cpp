#include "DbManager.h"
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>

DbManager* DbManager::_instance = 0;

DbManager& DbManager::instance() {
    QString database = QFileDialog::getOpenFileName();
    if(_instance == 0) _instance = new DbManager(database);
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
