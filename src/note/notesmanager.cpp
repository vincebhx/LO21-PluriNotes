#include "article.h"
#include "../dbmanager.h"
#include "media.h"
#include "notesmanager.h"
#include "tache.h"
#include "../exception.h"
#include "versionindex.h"

#include <iostream>
#include <QSqlRecord>

NotesManager* NotesManager::_instance = 0;

NotesManager::NotesManager() {
    std::cout<<"Construction du NotesManager."<<std::endl;
}

NotesManager::~NotesManager() {
    notes.clear();
    std::cout<<"NotesManager détruit."<<std::endl;
}

NotesManager& NotesManager::instance() {
    if(_instance == 0) {
        _instance = new NotesManager;
    }
    return *_instance;
}

void NotesManager::free() {
    delete this;
}

void NotesManager::addNote(VersionIndex* n) {
    for(unsigned int i = 0; i < notes.size(); i++)
        if (notes.at(i)->currentVersion()->getId() == n->currentVersion()->getId())
            throw Exception("Une note possédant l'id " + n->currentVersion()->getId() + " existe déjà.");
    notes.push_back(n);
}

void NotesManager::load() {
    /*DEBUT*/
    std::cout<<"Chargement des données..."<<std::endl;

    QSqlRecord rec;
    VersionIndex* vIndex;
    Note* n;
    QString id;

    /*ARTICLES*/
    bool newVIndex = true;
    QString currentId = "\0";

    QSqlTableModel* articles = Article::getTableModel(DbManager::instance().db);

    for (int i = 0; i < articles->rowCount(); i++) {
        newVIndex = false;
        rec = articles->record(i);
        id = rec.value(0).toString();
        n = new Article(
                    id,
                    rec.value(1).toInt(),
                    rec.value(2).toString(),
                    QDateTime::fromString(rec.value(3).toString(), "dd/MM/yyyy hh:mm:ss"),
                    QDateTime::fromString(rec.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                    rec.value(5).toString()
                    );

        if(currentId != id) {
            currentId = id;
            if(i != 0) {
                NotesManager::instance().addNote(vIndex);
                newVIndex = true;
            }
            vIndex = new VersionIndex;
        }
        vIndex->addVersion(n);
    }
    if(!newVIndex) NotesManager::instance().addNote(vIndex);

    /*MEDIAS*/
    QString type;
    newVIndex = true;
    currentId = "\0";

    QSqlTableModel* medias = Media::getTableModel(DbManager::instance().db);

    for (int i = 0; i < medias->rowCount(); i++) {
        newVIndex = false;
        rec = medias->record(i);
        id = rec.value(0).toString();
        type = rec.value(2).toString();

        if (type == "image")
            n = new Image(
                        id,
                        rec.value(1).toInt(),
                        rec.value(3).toString(),
                        QDateTime::fromString(rec.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(rec.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        rec.value(6).toString(),
                        rec.value(7).toString()
                        );
        else if (type == "audio")
            n = new Audio(
                        id,
                        rec.value(1).toInt(),
                        rec.value(3).toString(),
                        QDateTime::fromString(rec.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(rec.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        rec.value(6).toString(),
                        rec.value(7).toString()
                        );
        else //type == "video"
            n = new Video(
                        id,
                        rec.value(1).toInt(),
                        rec.value(3).toString(),
                        QDateTime::fromString(rec.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(rec.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        rec.value(6).toString(),
                        rec.value(7).toString()
                        );

        if(currentId != id) {
            currentId = id;
            if(i != 0) {
                NotesManager::instance().addNote(vIndex);
                newVIndex = true;
            }
            vIndex = new VersionIndex;
        }
        vIndex->addVersion(n);
    }
    if(!newVIndex) NotesManager::instance().addNote(vIndex);

    /*TACHES*/
    Statut stat;
    QString statStr;
    newVIndex = true;
    currentId = "\0";

    QSqlTableModel* taches = Tache::getTableModel(DbManager::instance().db);

    for (int i = 0; i < taches->rowCount(); i++) {
        newVIndex = false;
        rec = taches->record(i);
        id = rec.value(0).toString();

        statStr = rec.value(8).toString();
        if(statStr == StatutStr[EN_COURS]) stat = EN_COURS;
        else if (statStr == StatutStr[TERMINE]) stat = TERMINE;
        else stat = EN_ATTENTE;

        n = new Tache(
                    id,
                    rec.value(1).toInt(),
                    rec.value(2).toString(),
                    QDateTime::fromString(rec.value(3).toString(), "dd/MM/yyyy hh:mm:ss"),
                    QDateTime::fromString(rec.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                    rec.value(5).toString(),
                    rec.value(6).toInt(),
                    QDateTime::fromString(rec.value(7).toString(), "dd/MM/yyyy hh:mm:ss"),
                    stat
                    );

        if(currentId != id) {
            currentId = id;
            if(i != 0) {
                NotesManager::instance().addNote(vIndex);
                newVIndex = true;
            }
            vIndex = new VersionIndex;
        }
        vIndex->addVersion(n);
    }
    if(!newVIndex) NotesManager::instance().addNote(vIndex);


    /*FIN*/
    std::cout<<"Chargement effectué."<<std::endl;
}
