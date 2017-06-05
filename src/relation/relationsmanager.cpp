#include "RelationsManager.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

void RelationsManager::load() {
    std::cout<<"Chargement des relations..."<<std::endl;

    RelationsManager::loadRelations();
    RelationsManager::loadCouples();

    std::cout<<"Chargement des relations effectué."<<std::endl;
}

void RelationsManager::loadRelations(){
    QSqlQuery query("SELECT * FROM RelationNote ORDER BY titre ASC");

    int titre = query.record().indexOf("relation");
    int description = query.record().indexOf("description");
    int oriente = query.record().indexOf("oriente");

    while (query.next()){
        cout<<"Chargement de la relation "<<query.value(titre).toString().toStdString()<<endl;
        Relation* r = new Relation(
                    query.value(titre).toString(),
                    query.value(description).toString(),
                    query.value(oriente).toBool());
        std::cout<<"Chargement de "<<r->getTitre().toStdString()<<" effectué."<<std::endl;
        addRelation(r);
    }
}


/*
void NotesManager::loadArticles() {


    Version *v = new Version;
    QString currentId = 0;

    while (query.next())
    {
        if(currentId != query.value(id).toString()) {
            cout<<"Nouvelle note :"<<endl;
            if(currentId != 0) {
                addNote(v);
                v = new Version;
            }
            currentId = query.value(id).toString();
        }

        cout<<"Chargement de "<<query.value(id).toString().toStdString()<<" v"<<query.value(version).toInt()<<endl;

        Article* a = new Article(
            query.value(id).toString(),
            query.value(version).toInt(),
            query.value(titre).toString(),
            query.value(texte).toString(),
            QDateTime::fromString(query.value(creat).toString(), "dd/MM/yyyy hh:mm:ss"),
            QDateTime::fromString(query.value(modif).toString(), "dd/MM/yyyy hh:mm:ss")
        );
        v->addNote(a);
    }
    addNote(v);
}*/

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
