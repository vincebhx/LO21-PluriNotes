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
    actives.clear();
    archives.clear();
    corbeille.clear();
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

void NotesManager::addNote(Etat e, VersionIndex* n) {
    n->setEtat(static_cast<unsigned short>(e));
    std::vector<VersionIndex*>& current = ((e == ACTIVES) ? actives : ((e == ARCHIVES) ? archives : corbeille));
    for(unsigned int i = 0; i < current.size(); i++)
        if (current.at(i)->currentVersion()->getId() == n->currentVersion()->getId())
            throw Exception("Une note possédant l'id " + n->currentVersion()->getId() + " existe déjà.");
    current.push_back(n);
}

void NotesManager::load() {
    /*DEBUT*/
    std::cout<<"Chargement des données..."<<std::endl;
    QSqlRecord rec;
    VersionIndex* vIndex;
    Note* n;
    QString id;
    Etat etat;

    /*ARTICLES*/
    bool newVIndex = true;
    QString currentId = "\0";
    QSqlTableModel* articles = Article::getTableModel(DbManager::instance().db);

    for (int i = 0; i < articles->rowCount(); i++) {
        newVIndex = false;
        rec = articles->record(i);
        id = rec.value(1).toString();

        n = new Article(
                    id,
                    rec.value(2).toInt(),
                    rec.value(3).toString(),
                    QDateTime::fromString(rec.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                    QDateTime::fromString(rec.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                    rec.value(6).toString()
                    );

        if(currentId != id) {
            currentId = id;
            if(i != 0) {
                NotesManager::instance().addNote(etat, vIndex);
                newVIndex = true;
            }
            vIndex = new VersionIndex;
        }
        vIndex->addVersion(n);
        etat = toEtat(rec.value(0).toInt());
    }
    if(!newVIndex) NotesManager::instance().addNote(etat, vIndex);

    /*MEDIAS*/
    QString type;
    newVIndex = true;
    currentId = "\0";

    QSqlTableModel* medias = Media::getTableModel(DbManager::instance().db);

    for (int i = 0; i < medias->rowCount(); i++) {
        newVIndex = false;
        rec = medias->record(i);
        id = rec.value(1).toString();
        type = rec.value(3).toString();

        if (type == "image")
            n = new Image(
                        id,
                        rec.value(2).toInt(),
                        rec.value(4).toString(),
                        QDateTime::fromString(rec.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(rec.value(6).toString(), "dd/MM/yyyy hh:mm:ss"),
                        rec.value(7).toString(),
                        rec.value(8).toString()
                        );
        else if (type == "audio")
            n = new Audio(
                        id,
                        rec.value(2).toInt(),
                        rec.value(4).toString(),
                        QDateTime::fromString(rec.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(rec.value(6).toString(), "dd/MM/yyyy hh:mm:ss"),
                        rec.value(7).toString(),
                        rec.value(8).toString()
                        );
        else //type == "video"
            n = new Video(
                        id,
                        rec.value(2).toInt(),
                        rec.value(4).toString(),
                        QDateTime::fromString(rec.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(rec.value(6).toString(), "dd/MM/yyyy hh:mm:ss"),
                        rec.value(7).toString(),
                        rec.value(7).toString()
                        );

        if(currentId != id) {
            currentId = id;
            if(i != 0) {
                NotesManager::instance().addNote(etat, vIndex);
                newVIndex = true;
            }
            vIndex = new VersionIndex;
        }
        vIndex->addVersion(n);
        etat = toEtat(rec.value(0).toInt());
    }
    if(!newVIndex) NotesManager::instance().addNote(etat, vIndex);

    /*TACHES*/
    Statut stat;
    QString statStr;
    newVIndex = true;
    currentId = "\0";

    QSqlTableModel* taches = Tache::getTableModel(DbManager::instance().db);

    for (int i = 0; i < taches->rowCount(); i++) {
        newVIndex = false;
        rec = taches->record(i);
        id = rec.value(1).toString();

        statStr = rec.value(9).toString();
        if(statStr == StatutStr[EN_COURS]) stat = EN_COURS;
        else if (statStr == StatutStr[TERMINE]) stat = TERMINE;
        else stat = EN_ATTENTE;

        n = new Tache(
                    id,
                    rec.value(2).toInt(),
                    rec.value(3).toString(),
                    QDateTime::fromString(rec.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                    QDateTime::fromString(rec.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                    rec.value(6).toString(),
                    rec.value(7).toInt(),
                    QDateTime::fromString(rec.value(8).toString(), "dd/MM/yyyy hh:mm:ss"),
                    stat
                    );

        if(currentId != id) {
            currentId = id;
            if(i != 0) {
                NotesManager::instance().addNote(etat, vIndex);
                newVIndex = true;
            }
            vIndex = new VersionIndex;
        }
        vIndex->addVersion(n);
        etat = toEtat(rec.value(0).toInt());
    }
    if(!newVIndex) NotesManager::instance().addNote(etat, vIndex);

    /*FIN*/
    std::cout<<"Chargement effectué."<<std::endl;
}

Note* NotesManager::findNote(QString id) {
    NotesManager& nm = NotesManager::instance();
    Note* n;

    /* Recherche dans les notes actives */
    for(NMIterator it = nm.begin(ACTIVES); it!= nm.end(ACTIVES); it++){
        n = (*it)->currentVersion();
        if (n->getId() == id) return n;
    }

    /* Note non active : Recherche dans les archives */
    for(NMIterator it = nm.begin(ARCHIVES); it!= nm.end(ARCHIVES); it++){
        n = (*it)->currentVersion();
        if (n->getId() == id) return n;
    }

    /* Note ni active ni archivée : Recherche dans la corbeille */
    for(NMIterator it = nm.begin(CORBEILLE); it!= nm.end(CORBEILLE); it++){
        n = (*it)->currentVersion();
        if (n->getId() == id) return n;
    }

    /* Si on n'a pas trouvé la note : on renvoie un pointeur nul */
    return nullptr;
}

std::vector<VersionIndex*> NotesManager::getTasks() {
    std::vector<VersionIndex*> listTask;

    for(NMIterator it = this->begin(ACTIVES); it!= this->end(ACTIVES); it++){
        if((*it)->currentVersion()->getClassName() == "tache") {
            listTask.push_back(*it);
            std::cout << (*it)->currentVersion()->getId().toStdString();
        }
    }

    return listTask;
}

