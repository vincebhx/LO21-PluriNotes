#include "relationsmanager.h"

#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QVariant>
#include <QSqlError>

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

void RelationsManager::loadRelations() {
    qDebug()<<"\nChargement des relations...";
    Relation* r;
    QSqlQuery query;

    query.prepare("SELECT * FROM Relation ORDER BY titre");
    if(query.exec()) qDebug() << "Récupération des relations ok.";
    else qDebug() << "Erreur - RelationsManager::loadRelations : "<< query.lastError();

    while(query.next()) {
        r = new Relation(
                    query.value(0).toString(),
                    query.value(1).toString(),
                    query.value(2).toBool()
                    );
        relations.push_back(r);
    }
}

void RelationsManager::loadCouples() {
    qDebug()<<"\nChargement des couples...";
    Relation* rel;
    Couple* couple;
    QSqlQuery query;

    query.prepare("SELECT * FROM RelationNote ORDER BY relation, note1, note2");
    if(query.exec()) qDebug() << "Récupération des couples ok.";
    else qDebug() << "Erreur - RelationsManager::loadCouples : "<< query.lastError();

    while(query.next()) {
        rel = findRelation(query.value(0).toString());
        QString note1 = query.value(1).toString();
        QString note2 = query.value(2).toString();
        QString label = query.value(3).toString();

        couple = new Couple(note1, note2, label);
        rel->addCouple(couple);

        if(!rel->estOriente()) {
            couple = new Couple(note2, note1, label);
            rel->addCouple(couple);
        }
    }
}

/*****TOUT CE QUI EST AU DESSUS DE CE COMMENTAIRE EST OK *****/

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
    for(RelationIterator ri = r->begin(); ri != r->end(); ri++) {
        supprimerCouple(r, (*ri));
    }
    r->deleteCouples();
}

void RelationsManager::supprimerCouple(Relation* r, Couple* c) {
    bool supp = DbManager::instance().deleteCouple(c, r);
    if (supp) {
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
