#include "dbmanager.h"
#include "note/note.h"
#include "exception.h"
#include "./relation/relation.h"
#include "./relation/relationsmanager.h"

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

// -- INSERTION D'UNE RELATION DANS LA BASE DE DONNEES -- //
bool DbManager::saveRelation(Relation* r) {
    bool success = false;
    QSqlQuery query = r->getInsertQuery();

    if(query.exec()) {
        success = true;
        qDebug() << "Note ajoutée à la base de données.";
        //RelationsManager::instance().addRelation(r);
    }
    else
        qDebug() << "Erreur - DbManager::addRelation : "<< query.lastError();

    query.finish();
    return success;
}

bool DbManager::saveCouple(Relation* r, Couple* c) {
    bool success = false;
    QSqlQuery query = c->getInsertQuery(r);

    if(query.exec()) {
        success = true;
        qDebug() << "Note ajoutée à la base de données.";
        r->addCouple(c);
    }
    else
        qDebug() << "Erreur - DbManager::addNote : "<< query.lastError();

    query.finish();
    return success;
}

bool DbManager::changeNoteState(Note *n) {
    bool success = false;
    QSqlQuery query = n->getUpdateStateQuery();

    if(query.exec()) {
        success = true;
        qDebug() << "État de la note"<<n->getId()<<"version"<<n->getVersion()<<"amis à jour dans la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::updateNoteState : "<< query.lastError();

    query.finish();
    return success;
}

bool DbManager::deleteNote(Note* n) {
    bool success = false;
    // -- LA NOTE EST-ELLE REFERENCEE ? -- //
    if (n->referencee()){
        qDebug()<<"Impossible de supprimer la note car elle est référencée : archivez-la.\n";
    }
    else{
        QSqlQuery query = n->getDeleteQuery();
        qDebug()<<getLastQuery(query);

        if(query.exec()) {
            success = true;
            qDebug() << "Note supprimée dans la base de données.";
        }
        else
            qDebug() << "Erreur - DbManager::deleteNote : "<< query.lastError();
        query.finish();
    }
    return success;
};

// -- SUPPRESSION D'UN COUPLE DANS LA BASE DE DONNEES -- //
bool DbManager::deleteCouple(Couple* c, Relation* r) {
    bool success = false;
    QSqlQuery query = c->getDeleteQuery(r);
    qDebug()<<getLastQuery(query);

    if(query.exec()) {
        success = true;
        qDebug() << "Note supprimée dans la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::deleteNote : "<< query.lastError();
    query.finish();
    return success;
};

bool DbManager::deleteCouples(Relation* r) {
    bool success = false;
    QSqlQuery query = r->getDeleteQueryCouples();
    qDebug()<<getLastQuery(query);

    if(query.exec()) {
        success = true;
        qDebug() << "Couples supprimées dans la base de données.";
    }
    else
        qDebug() << "Erreur - DbManager::deleteCouples : "<< query.lastError();
    query.finish();
    return success;
};


bool DbManager::deleteRelation(Relation* r) {
    bool success = false;
    QString ref = "Reference";

    if (r->getTitre() != ref){
        bool susu = deleteCouples(r);

        QSqlQuery query = r->getDeleteQuery();
        qDebug()<<getLastQuery(query);
        if(query.exec()) {
            success = true;
            qDebug() << "Relation supprimée dans la base de données.";
        }
        else
            qDebug() << "Erreur - DbManager::deleteRelation : "<< query.lastError();
        query.finish();
    }
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
