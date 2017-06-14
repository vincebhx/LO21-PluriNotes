#include "note.h"
#include "notesmanager.h"
#include "./src/relation/relationsmanager.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <QDebug>

#include <iostream>

const QString Note::dateDisplayFormat = "ddd dd MMMM yyyy à hh:mm:ss";
const QString Note::dateStorageFormat = "dd/MM/yyyy hh:mm:ss";

QSqlQuery Note::getInsertQuery() {
    QSqlQuery query = prepareInsertQuery();
    query.bindValue(":etat", parent->getEtat());
    query.bindValue(":id", id);
    query.bindValue(":version", version);
    query.bindValue(":titre", titre);
    query.bindValue(":dateCreation", dateCreation.toString(dateStorageFormat));
    query.bindValue(":dateModification", dateModification.toString(dateStorageFormat));
    return query;
}

QSqlQuery Note::getUpdateStateQuery() {
    QSqlQuery query;
    QString str = "UPDATE " + getTableName() + " SET etat = "+ QString::number(parent->getEtat())
            + " WHERE id = '" + id + "' AND version = " + QString::number(version);
    query.prepare(str);
    return query;
}

QSqlQuery Note::getDeleteQuery() {
    QSqlQuery query;
    QString str = "DELETE FROM " + getTableName() + " WHERE id = '" + id +"' AND version = " + QString::number(version);
    query.prepare(str);
    return query;
}

bool Note::referencee(){
    RelationsManager& rm = RelationsManager::instance();
    QString reference("Reference");
    Relation* ref = rm.findRelation(reference);
    bool resultat = false;

    for (RelationIterator ri = ref->begin(); ri != ref->end(); ri++){
        if ((*ri)->getNote2() == getId()) resultat = true;
    }
    return resultat;
}

bool Note::archivee(){
    NotesManager& nm = NotesManager::instance();
    bool resultat = false;

    for(NMIterator it = nm.begin(ARCHIVES); it!= nm.end(ARCHIVES); it++){
        Note* n = (*it)->currentVersion();
        if (n->getId() == id) resultat = true;
    }
    return resultat;
}

bool Note::supprimee(){
    NotesManager& nm = NotesManager::instance();
    bool resultat = false;

    for(NMIterator it = nm.begin(CORBEILLE); it!= nm.end(CORBEILLE); it++){
        Note* n = (*it)->currentVersion();
        if (n->getId() == id) resultat = true;
    }
    return resultat;
}

bool Note::activee(){
    NotesManager& nm = NotesManager::instance();
    bool resultat = false;

    for(NMIterator it = nm.begin(ACTIVES); it!= nm.end(ACTIVES); it++){
        Note* n = (*it)->currentVersion();
        if (n->getId() == id) resultat = true;
    }
    return resultat;
}

bool Note::implicationRelation(Relation* rel){
    bool resultat = false;
    for (RelationIterator ri = rel->begin(); ri != rel->end(); ri++){
        if ((*ri)->getNote1() == getId() || (*ri)->getNote2() == getId()) resultat = true;
    }
    return resultat;
}

std::vector<Relation *> Note::implicationRelation(){
    std::vector<Relation*> listRelation;

    RelationsManager& rm = RelationsManager::instance();

    for (RMIterator RMit = rm.begin(); RMit != rm.end(); RMit++){
        for (RelationIterator ri = (*RMit)->begin(); ri != (*RMit)->end(); ri++){
            if ((*ri)->getNote1() == id || (*ri)->getNote2() == id){
                listRelation.push_back(*RMit);
            }
        }
    }
    return listRelation;
}

/*
bool Note::referencesTerminees(){
    bool resultat = true;

    RelationsManager& rm = RelationsManager::instance();
    NotesManager& nm = NotesManager::instance();

    // -- Est-elle référencée? -- //
    if (referencee()){
        QString titre("Reference");
        Relation* ref = rm.findRelation(titre);

        for (RelationIterator ri = ref->begin(); ri != ref->end(); ri++){
            if ((*ri)->getNote2() == getId()){
                // -- Référencée dans ce couple : l'ascendant est-il dans les archives ? -- /
                Note* asc = nm.findNote((*ri)->getNote1());
                if (asc->activee()){
                    resultat = false;
                }
            }
=======
        if (implicationRelation(*RMit)){
            relations.push_back((*RMit)->getTitre());
>>>>>>> 5d5c3ef9d84815ed1c3f9bca436dff7a95827056
        }
    }
    return resultat;
}*/
