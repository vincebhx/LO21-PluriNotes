#include "relationsmanager.h"
#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QVariant>


RelationsManager* RelationsManager::_instance = 0;

RelationsManager& RelationsManager::instance() {
    if(_instance == 0) {
        _instance = new RelationsManager;
    }
    return *_instance;
}

RelationsManager::RelationsManager() {
    std::cout<<"Construction du RelationsManager."<<std::endl;
    DbManager::instance();
    RelationsManager::load();
}

RelationsManager::~RelationsManager() {
    relations.clear();
    std::cout<<"RelationsManager détruit."<<std::endl;
}

void RelationsManager::free() {
    delete this;
}

void RelationsManager::load() {
    std::cout<<"Chargement des relations..."<<std::endl;

    RelationsManager::loadRelations();
    //RelationsManager::loadCouples();

    std::cout<<"Chargement des relations effectué."<<std::endl;
}

void RelationsManager::loadRelations(){
    QSqlRecord rec;
    QSqlTableModel* rel = Relation::getTableModel(DbManager::instance().db);

    // -- On devrait en avoir 2... -- //
    std::cout<<"Relations à charger: "<<rel->rowCount()<<std::endl;

    for (int i = 0; i < rel->rowCount(); i++){
        rec = rel->record(i);
        QString titre = rec.value(0).toString();
        std::cout<<"Chargement de la relation "<<titre.toStdString()<<std::endl;
        Relation* r = new Relation(titre,
                         rec.value(1).toString(),
                         rec.value(2).toBool());
        //addRelation(r);
        //loadCouples(r);
    }
    std::cout<<"Fin de loadRelations()"<<std::endl;
}

void RelationsManager::addRelation(Relation* r){
    relations.push_back(r);
}

Relation* RelationsManager::findRelation(QString titre){
    Relation* resultat = nullptr;
    int trouve = 0;

    // -- RECHERCHE DE LA NOTE DANS LES ACTIVES -- //
    for(RMIterator it = this->begin(); it!= this->end(); it++){
        Relation* r = (*it);
        if (r->getTitre() == titre){
            trouve = 1;
            resultat = r;
        }
    }
    return resultat;
}

/*
void RelationsManager::loadCouples(){
    //std::cout<<"Chargement des couples des relations...\n";
    NotesManager& nm = NotesManager::instance();
    QSqlTableModel* couples = Couple::getTableModel(DbManager::instance().db);
    QSqlRecord rec;

    for (int i = 0; i < couples->rowCount(); i++){
        rec = couples->record(i);

        // -- RECUPERATION DU TUPLE RELATION/NOTE1/NOTE2 -- //
        QString relation = rec.value(0).toString();
        QString note1 = rec.value(1).toString();
        QString note2 = rec.value(2).toString();

        // -- RECUPERATION DE LA RELATION IMPLIQUEE -- //


        // -- RECUPERATION DE LA NOTE1 -- //

        // -- RECUPERATION DE LA NOTE2 -- //

    }
}
*/

