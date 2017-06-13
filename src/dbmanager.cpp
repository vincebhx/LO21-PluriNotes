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
        qDebug() << "Succès de la connexion à la base de données.";
}

DbManager::~DbManager() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Fermeture de la connexion avec la base de données.";
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
    QSqlQuery query = n->getInsertQuery();

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
    QSqlQuery query = r->getInsertQuery();

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
    QSqlQuery query = c->getInsertQuery(r);

    if(query.exec()) {
        success = true;
        qDebug() << "Note ajoutée à la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::addNote : "<< query.lastError();

    query.finish();
    return success;
}

bool DbManager::changeNoteState(Note *n) {
    bool success = false;
    QSqlQuery query = n->getUpdateStateQuery();
    qDebug()<<getLastQuery(query);

    if(query.exec()) {
        success = true;
        qDebug() << "État de la note mise à jour dans la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::updateNoteState : "<< query.lastError();

    query.finish();
    return success;
}

bool DbManager::deleteNote(Note* n) {
    bool success = false;
    QSqlQuery query = n->getDeleteQuery();
    qDebug()<<getLastQuery(query);

    if(query.exec()) {
        success = true;
        qDebug() << "Note supprimée dans la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::deleteNote : "<< query.lastError();
    query.finish();
    return success;
}

QString DbManager::getLastQuery(const QSqlQuery& query) {
    QString s = query.lastQuery();
    QMapIterator<QString, QVariant> it (query.boundValues());

    while (it.hasNext()) {
        it.next();
        s.replace(it.key(),it.value().toString());
    }
    return s;
}
