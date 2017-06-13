#include "dbmanager.h"
#include "note/note.h"
#include "exception.h"
#include "./relation/relation.h"

#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <QSqlError>

DbManager* DbManager::_instance = 0;

DbManager::DbManager(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if(!db.open())
        throw Exception("Échec de la connexion à la base de données.");
    else
        std::cout<<"Succès de la connexion à la base de données."<<std::endl;
}

DbManager::~DbManager() {
    if (db.isOpen()) {
        db.close();
        std::cout<<"Fermeture de la connexion avec la base de données."<<std::endl;
    }
}

DbManager& DbManager::instance() {
    if (_instance == 0) {
        //QString database = QFileDialog::getOpenFileName();
        QString database("./notes.db");
        _instance = new DbManager(database);
    }
    return *_instance;
}

void DbManager::free() {
    delete this;
}

bool DbManager::saveNote(Note *n) {
    bool success = false;
    QSqlQuery query = n->getQuery();

    if(query.exec()) {
        success = true;
        qDebug() << "Note ajoutée à la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::addNote : "<< query.lastError();

    query.finish();
    return success;
}

bool DbManager::saveRelation(Relation* r) {
    bool success = false;
    QSqlQuery query = r->getQuery();

    if(query.exec()) {
        success = true;
        qDebug() << "Note ajoutée à la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::addNote : "<< query.lastError();

    query.finish();
    return success;
}

bool DbManager::saveCouple(Relation* r, Couple* c) {
    bool success = false;
    QSqlQuery query = c->getQuery(r);

    if(query.exec()) {
        success = true;
        qDebug() << "Note ajoutée à la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::addNote : "<< query.lastError();

    query.finish();
    return success;
}
