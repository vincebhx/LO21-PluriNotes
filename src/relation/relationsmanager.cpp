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
    // suppression des couples
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

/*
void RelationsManager::loadCouples(){
    QSqlTableModel* couples = Couple::getTableModel(DbManager::instance().db);
    QSqlRecord rec;

    for (int i = 0; i < couples->rowCount(); i++){
        rec = couples->record(i);
        QString relation = rec.value(0).toString();
        QString note1 = rec.value(1).toString();
        // On recherche les notes + la relation dont il s'agit
    }
}*/

void RelationsManager::loadRelations(){
    QSqlRecord rec;
    QSqlTableModel* relations = Relation::getTableModel(DbManager::instance().db);
    std::cout<<"Relations à charger: "<<relations->rowCount()<<std::endl;
    std::cout<<relations->record(0).value(0).toString().toStdString()<<std::endl;
    for (int i = 0; i < relations->rowCount(); i++){
        rec = relations->record(i);
        QString titre = rec.value(0).toString();
        std::cout<<"Chargement de la relation "<<titre.toStdString()<<std::endl;
        Relation* r = new Relation(titre,
                         rec.value(1).toString(),
                         rec.value(2).toBool());
        addRelation(r);
        //loadCouples(r);
    }
    std::cout<<"Fin de loadRelations()"<<std::endl;
}

void RelationsManager::addRelation(Relation* r){
    if (nbRelations == nbMaxRelations){
        nbMaxRelations += 5;
        Relation** newRelations = new Relation* [nbMaxRelations];
        for (unsigned int i = 0; i < nbRelations; i++){
            newRelations[i] = relations[i];
        }
        Relation** oldRelations = relations;

        relations = newRelations;

        if (oldRelations){
            delete[] oldRelations;
        }
    }
    relations[nbRelations++] = r;
}
