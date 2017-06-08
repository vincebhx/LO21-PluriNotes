#include "relationsmanager.h"
#include "./src/note/notesmanager.h"
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
    std::cout<<"Chargement des relations et de leurs couples..."<<std::endl;

    RelationsManager::loadRelations();
    RelationsManager::loadCouples();

    std::cout<<"Chargement des relations et de leurs couples effectué.\n\n"<<std::endl;
}

void RelationsManager::loadRelations(){
    QSqlRecord rec;
    QSqlTableModel* rel = Relation::getTableModel(DbManager::instance().db);

    for (int i = 0; i < rel->rowCount(); i++){
        rec = rel->record(i);
        QString titre = rec.value(0).toString();
        Relation* r = new Relation(titre,
                         rec.value(1).toString(),
                         rec.value(2).toBool());
        addRelation(r);
    }
}

void RelationsManager::addRelation(Relation* r){
    relations.push_back(r);
}

Relation* RelationsManager::findRelation(QString titre){
    Relation* resultat = nullptr;

    for(RMIterator it = this->begin(); it!= this->end(); it++){
        Relation* r = (*it);
        if (r->getTitre() == titre){
            resultat = r;
        }
    }
    return resultat;
}


void RelationsManager::loadCouples(){

    NotesManager& nm = NotesManager::instance();
    QSqlTableModel* couples = Couple::getTableModel(DbManager::instance().db);
    QSqlRecord rec;

    std::cout<<"\n\nOn va charger "<<couples->rowCount()<<" tuples."<<std::endl;

    for (int i = 0; i < couples->rowCount(); i++){
        rec = couples->record(i);

        // -- RECUPERATION DU TUPLE RELATION/NOTE1/NOTE2 -- //
        QString relation = rec.value(0).toString();
        QString note1 = rec.value(1).toString();
        QString note2 = rec.value(2).toString();
        QString label = rec.value(3).toString();

        std::cout<<"--->"<<relation.toStdString()<<"(("<<note1.toStdString()<<", "<<note2.toStdString()<<")"<<label.toStdString()<<")\n";
        //std::cout<<note1.toStdString()<<std::endl;
        //std::cout<<note2.toStdString()<<std::endl;

        // -- RECUPERATION DE LA RELATION IMPLIQUEE -- //
        Relation* rel = findRelation(relation);
        //std::cout<<"Couples de la relation = "<<rel->getTitre().toStdString()<<std::endl;

        Couple* nouveauCouple = new Couple(note1, note2, label);
        rel->addCouple(nouveauCouple);

        // -- INSERTION DE DEUX COUPLES SI RELATION ORIENTEE -- //
        if (rel->estOriente()){
            Couple* nouveauCouple2 = new Couple(note2, note1, label);
            rel->addCouple(nouveauCouple2);
        }
    }
}


bool RelationsManager::noteImpliqueeDansRelation(Note* note){
    bool resultat = false;
    // -- ON OBSERVE CHAQUE RELATION -- //
    for (RMIterator it = this->begin(); it != this->end(); it++){
        // -- LA NOTE Y EST ELLE IMPLIQUEE ? -- //
        for (RelationIterator itCouple = (*it)->begin(); itCouple != (*it)->end(); itCouple++){
            if ((*itCouple)->getNote1() == note->getId() || (*itCouple)->getNote2() == note->getId()) resultat = true;
        }
    }
    return resultat;
}


QSqlTableModel* RelationsManager::getTableModel(QSqlDatabase db){
        QSqlTableModel* modelCouple = new QSqlTableModel(0, db);
        modelCouple->setTable("RelationNote");
        modelCouple->setEditStrategy(QSqlTableModel::OnManualSubmit);
        modelCouple->select();
        modelCouple->setHeaderData(0, Qt::Horizontal, QObject::tr("relation"));
        modelCouple->setHeaderData(1, Qt::Horizontal, QObject::tr("note1"));
        modelCouple->setHeaderData(2, Qt::Horizontal, QObject::tr("note2"));
        return modelCouple;
};

QTableView* RelationsManager::getCoupleView(QSqlTableModel *table) {
    QTableView *viewCouple = new QTableView;
    viewCouple->setModel(table);
    return viewCouple;
}

