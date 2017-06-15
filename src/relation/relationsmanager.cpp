#include "relationsmanager.h"

#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QVariant>

#include <algorithm>

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
        relations.push_back(r);
    }
}

bool RelationsManager::addRelation(Relation* r){
    QString rel = r->getTitre();
    Relation* relExistante = findRelation(rel);
    if(relExistante){
        qDebug()<<"La relation existe deja !";
    }
    else{
        bool succes = DbManager::instance().saveRelation(r);
        if (succes) relations.push_back(r);
    }
}

/*
bool RelationsManager::addRelationBDD(Relation* r){
    bool insertion = DbManager::instance().saveRelation(r);
    if (!insertion) qDebug()<<"Insertion de la relation impossible.";
    else addRelation(r);
}*/

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
        Couple* nouveauCouple2 = new Couple(note2, note1, label);
        if (!rel->estOriente()) rel->addCouple(nouveauCouple2);
    }
}


bool RelationsManager::noteImpliqueeDansRelation(Note *note){
    bool resultat = false;
    // -- ON OBSERVE CHAQUE RELATION -- //
    for (RMIterator it = relations.begin(); it != relations.end(); it++){
        // -- LA NOTE Y EST ELLE IMPLIQUEE ? -- //
        for (RelationIterator it2 = (*it)->begin(); it2 != (*it)->end(); it2++){
            if ((*it2)->getNote1() == note->getId() || (*it2)->getNote2() == note->getId()) {
                qDebug()<<(*it2)->getNote1()<<" "<<(*it2)->getNote2()<<" "<<note->getId()<<" TRUE";
                resultat = true;
                break;
            }
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

std::vector<QString> RelationsManager::nomRelations(){
    std::vector<QString> noms;

    for (RMIterator RMit = this->begin(); RMit != this->end(); RMit++){
        noms.push_back((*RMit)->getTitre());
    }
    return noms;
}

bool RelationsManager::addCouple(QString titreRelation, Couple* c){
    Relation* rel = findRelation(titreRelation);
    if (rel){
        bool succesCouple = DbManager::instance().saveCouple(rel, c);
    }
    else{
        // -- LA RELATION N'EXISTE PAS : ON LA CREE ... peut ne pas servir. -- //
        bool succesRelation = addRelation(rel);
        if (succesRelation){
            bool succesCouple = DbManager::instance().saveCouple(rel, c);
            if (succesCouple) rel->addCouple(c);
        }
        else{
            qDebug()<<"Impossibilité de rajouter dans la BDD la relation.";
        }

    }
}

void RelationsManager::supprimerCouples(Relation* r){
    for(RelationIterator ri = r->begin(); ri != r->end(); ri++){
        supprimerCouple(r, (*ri));
    }
    r->deleteCouples();
}

void RelationsManager::supprimerCouple(Relation* r, Couple* c){
    bool supp = DbManager::instance().deleteCouple(c, r);
    if (supp){
        r->supprimerCouple(c);
    }
}

void RelationsManager::supprimerRelation(Relation* r){
    // -- PERMET DE SUPPRIMER UNE RELATION R DU RELATIONS MANAGER
    QString titre = r->getTitre();

    // -- R EST-ELLE LA RELATION REFERENCE A NE JAMAIS SUPPRIMER ? -- //
    if (titre.toStdString() == "Reference"){
        qDebug()<<"Impossible de supprimer la relation Référence.\n";
    }
    else{
        bool suppression = DbManager::instance().deleteRelation(r);
        if (suppression){
            r->deleteCouples();


            relations.erase(std::remove(begin(), end(), r), end());
            std::cout<<"Après suppression...\n";
        }
        else {
            qDebug()<<"Problème dans la suppression de la relation";
        }
    }
}
