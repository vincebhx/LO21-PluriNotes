#include "article.h"
#include "../dbmanager.h"
#include "media.h"
#include "notesmanager.h"
#include "tache.h"
#include "../exception.h"
#include "versionindex.h"
#include "./src/relation/relationsmanager.h"

#include <iostream>
#include <algorithm>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

NotesManager* NotesManager::_instance = 0;

NotesManager::NotesManager() {
    qDebug()<<"Construction du NotesManager.";
}

NotesManager::~NotesManager() {
    actives.clear();
    archives.clear();
    corbeille.clear();
    qDebug()<<"Destruction du NotesManager.";
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
    indexId.push_back(n->currentVersion()->getId());
}

void NotesManager::archiveNote(VersionIndex* v) {
    Etat etat = static_cast<Etat>(v->getEtat());
    if (etat == ARCHIVES) //Note déjà archivée
        qDebug()<<"Note déjà archivée !";
    else {
        this->addNote(ARCHIVES, v); //Met à jour l'état dans le VersionIndex !
        NMIterator oldPos = find(this->begin(etat), this->end(etat), v);
        switch (etat) {
        case ACTIVES: actives.erase(oldPos); break;
        case CORBEILLE: corbeille.erase(oldPos); break;
        default: throw Exception("Erreur d'archivage : la position de la note est inconnue !");
        }
        for (VersionIterator it = v->begin(); it != v->end(); it++) //Mise à jour de toutes les versions de la note dans la BDD
            DbManager::instance().updateNoteState(*it);
    }
}

void NotesManager::trashNote(VersionIndex* v) {
    Etat etat = static_cast<Etat>(v->getEtat());
    if (etat == CORBEILLE) //Note déjà archivée
        qDebug()<<"Note déjà dans la corbeille !";
    else {
        this->addNote(CORBEILLE, v);    //Met à jour l'état dans le VersionIndex !
        NMIterator oldPos = find(this->begin(etat), this->end(etat), v);
        switch (etat) {
        case ACTIVES: actives.erase(oldPos); break;
        case ARCHIVES: corbeille.erase(oldPos); break;
        default: throw Exception("Erreur de mise à la corbeille : la position de la note est inconnue !");
        }
        for (VersionIterator it = v->begin(); it != v->end(); it++) //Mise à jour de toutes les versions de la note dans la BDD
            DbManager::instance().updateNoteState(*it);
    }
}

void NotesManager::deleteNote(VersionIndex* v) {
    Etat etat = static_cast<Etat>(v->getEtat());
    if (etat != CORBEILLE)
        qDebug()<<"Erreur : impossible de supprimer une note qui n'est pas dans la corbeille !";
    else {
        for (VersionIterator it = v->begin(); it != v->end(); it++) //Mise à jour de toutes les versions de la note dans la BDD
            DbManager::instance().deleteNote(*it);

        NMIterator pos = find(this->begin(CORBEILLE), this->end(CORBEILLE), v);
        corbeille.erase(pos);
        delete v;
    }
}

VersionIndex* NotesManager::findVersionIndex(QString id) {
    //VersionIndex* versionI;
    Note* n;

    /* Recherche dans les notes actives */
    for(NMIterator it = this->begin(ACTIVES); it!= this->end(ACTIVES); it++){
        n = (*it)->currentVersion();
        if (n->getId() == id) return *it;
    }

    /* Note non active : Recherche dans les archives */
    for(NMIterator it = this->begin(ARCHIVES); it!= this->end(ARCHIVES); it++){
        n = (*it)->currentVersion();
        if (n->getId() == id) return *it;
    }

    /* Note ni active ni archivée : Recherche dans la corbeille */
    for(NMIterator it = this->begin(CORBEILLE); it!= this->end(CORBEILLE); it++){
        n = (*it)->currentVersion();
        if (n->getId() == id) return *it;
    }

    /* Si on n'a pas trouvé la note : on renvoie un pointeur nul */
    return nullptr;

}

Note* NotesManager::findNote(QString id) {

    VersionIndex* versionI = this->findVersionIndex(id);
    return versionI->currentVersion();

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

void NotesManager::load() {
    /*DEBUT*/
    qDebug()<<"\nChargement des données...";
    VersionIndex* vIndex;
    Note* n;
    QString id;
    Etat etat;

    /*ARTICLES*/
    QSqlQuery queryART;
    unsigned int count = 0;
    QString currentId = "\0";

    queryART.prepare("SELECT * FROM Article ORDER BY id, version");
    if(queryART.exec()) qDebug() << "Récupération des articles ok.";
    else qDebug() << "Erreur - NotesManager::load : "<< queryART.lastError();

    while(queryART.next()) {
        id = queryART.value(1).toString();
        n = new Article(
                    id,
                    queryART.value(2).toInt(),
                    queryART.value(3).toString(),
                    QDateTime::fromString(queryART.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                    QDateTime::fromString(queryART.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                    queryART.value(6).toString()
                    );

        if(currentId != id) {
            currentId = id;
            if(count != 0) NotesManager::instance().addNote(etat, vIndex);
            vIndex = new VersionIndex;
            Article::idIncrement++;
        }
        vIndex->addVersion(n);
        etat = toEtat(queryART.value(0).toInt());
        count++;
    }
    if (count != 0) NotesManager::instance().addNote(etat, vIndex);

    /*MEDIAS*/
    QSqlQuery queryMED;
    QString type;
    count = 0;
    currentId = "\0";

    queryMED.prepare("SELECT * FROM Media ORDER BY id, version");
    if(queryMED.exec()) qDebug() << "Récupération des médias ok.";
    else qDebug() << "Erreur - NotesManager::load : "<< queryMED.lastError();

    while(queryMED.next()) {
        id = queryMED.value(1).toString();
        type = queryMED.value(3).toString();

        if (type == "image")
            n = new Image(
                        id,
                        queryMED.value(2).toInt(),
                        queryMED.value(4).toString(),
                        QDateTime::fromString(queryMED.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(queryMED.value(6).toString(), "dd/MM/yyyy hh:mm:ss"),
                        queryMED.value(7).toString(),
                        queryMED.value(8).toString()
                        );
        else if (type == "audio")
            n = new Audio(
                        id,
                        queryMED.value(2).toInt(),
                        queryMED.value(4).toString(),
                        QDateTime::fromString(queryMED.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(queryMED.value(6).toString(), "dd/MM/yyyy hh:mm:ss"),
                        queryMED.value(7).toString(),
                        queryMED.value(8).toString()
                        );
        else //type == "video"
            n = new Video(
                        id,
                        queryMED.value(2).toInt(),
                        queryMED.value(4).toString(),
                        QDateTime::fromString(queryMED.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                        QDateTime::fromString(queryMED.value(6).toString(), "dd/MM/yyyy hh:mm:ss"),
                        queryMED.value(7).toString(),
                        queryMED.value(7).toString()
                        );

        if(currentId != id) {
            currentId = id;
            if(count != 0) NotesManager::instance().addNote(etat, vIndex);
            vIndex = new VersionIndex;
            if (type == "image") Image::idIncrement++;
            else if (type == "audio") Audio::idIncrement++;
            else Video::idIncrement++;
        }
        vIndex->addVersion(n);
        etat = toEtat(queryMED.value(0).toInt());
        count++;
    }
    if(count != 0) NotesManager::instance().addNote(etat, vIndex);


    /*TACHES*/
    QSqlQuery queryTCH;
    Statut stat;
    QString statStr;
    count = 0;
    currentId = "\0";

    queryTCH.prepare("SELECT * FROM Tache ORDER BY id, version");
    if(queryTCH.exec()) qDebug() << "Récupération des tâches ok.";
    else qDebug() << "Erreur - NotesManager::load : "<< queryTCH.lastError();

    while(queryTCH.next()) {
        id = queryTCH.value(1).toString();

        statStr = queryTCH.value(9).toString();
        if(statStr == StatutStr[EN_COURS]) stat = EN_COURS;
        else if (statStr == StatutStr[TERMINE]) stat = TERMINE;
        else stat = EN_ATTENTE;

        n = new Tache(
                    id,
                    queryTCH.value(2).toInt(),
                    queryTCH.value(3).toString(),
                    QDateTime::fromString(queryTCH.value(4).toString(), "dd/MM/yyyy hh:mm:ss"),
                    QDateTime::fromString(queryTCH.value(5).toString(), "dd/MM/yyyy hh:mm:ss"),
                    queryTCH.value(6).toString(),
                    queryTCH.value(7).toInt(),
                    QDateTime::fromString(queryTCH.value(8).toString(), "dd/MM/yyyy hh:mm:ss"),
                    stat
                    );

        if(currentId != id) {
            currentId = id;
            if(count != 0) NotesManager::instance().addNote(etat, vIndex);
            vIndex = new VersionIndex;
            Tache::idIncrement++;
        }
        vIndex->addVersion(n);
        etat = toEtat(queryTCH.value(0).toInt());
        count++;
    }
    if(count != 0) NotesManager::instance().addNote(etat, vIndex);

    /*FIN*/
    qDebug()<<"Chargement effectué.\n";
}


int NotesManager::getIndexId(QString id){
    int i = -1;
    do {
        i++;
    }while (this->indexId[i] != id && i < this->indexId.size());
    return i;
}

std::vector<QString> NotesManager::getAscendants(Note* note, Relation* relation){
    std::vector<QString> ascendants;

    // -- LA NOTE DONT ON CHERCHE LES ASCENDANTS -- //
    QString idNote = note->getId();

    for (RelationIterator ri = relation->begin(); ri != relation->end(); ri++){
        if ((*ri)->getNote2() == idNote) ascendants.push_back((*ri)->getNote1());
    }

    return ascendants;
}

std::vector<QString> NotesManager::getDescendants(Note* note, Relation* relation){
    std::vector<QString> descendants;

    // -- LA NOTE DONT ON CHERCHE LES ASCENDANTS -- //
    QString idNote = note->getId();

    for (RelationIterator ri = relation->begin(); ri != relation->end(); ri++){
        if ((*ri)->getNote1() == idNote) descendants.push_back((*ri)->getNote2());
    }

    return descendants;
}
