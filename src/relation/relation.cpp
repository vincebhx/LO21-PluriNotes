#include "relation.h"
#include "relationsmanager.h"
#include "../note/note.h"
#include "../note/notesmanager.h"
#include "couple.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>
#include <QString>
#include <QPair>
#include <iostream>
#include "relation.h"
#include "couple.h"
#include<QSqlError>
#include <QDebug>

using namespace std;

QSqlTableModel* Relation::getTableModel(QSqlDatabase db){
    QSqlTableModel* modelRelation = new QSqlTableModel(0, db);
    modelRelation->setTable("RelationNote");
    modelRelation->select();
    modelRelation->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelRelation->setHeaderData(0, Qt::Horizontal, QObject::tr("relation"));
    modelRelation->setHeaderData(1, Qt::Horizontal, QObject::tr("note1"));
    modelRelation->setHeaderData(2, Qt::Horizontal, QObject::tr("note2"));

    return modelRelation;
}

QTableView* Relation::getRelationView(QSqlTableModel *table) {
    QTableView *viewRelation = new QTableView;
    viewRelation->setModel(table);
    return viewRelation;
}


void Relation::addCouple(Couple *c){
    couples.push_back(c);
}

void Relation::loadMatrice(){
    NotesManager& nm = NotesManager::instance();

    // -- MATRICE DEJA OCCUPEE ? -- //
    if (!matriceAdjacence.empty()){
        int size = matriceAdjacence[0].size();
        for (int i = 0; i < size; i++){
            matriceAdjacence[i].clear();
        }
    }

    int sizeMatrice = nm.nbNotes(ACTIVES) + nm.nbNotes(ARCHIVES);
    if (sizeMatrice != 0){
        // -- SUPPRESSION DE LA MATRICE AUPARAVANT EXISTANTE -- //
        for (int i = 0; i < sizeMatrice; i++){
            matriceAdjacence[i].clear();
        }
    }
    // -- INITIALISATION DE LA MATRICE -- //
    matriceAdjacence.resize(sizeMatrice, vector<int> (sizeMatrice,0));

    // -- REMPLISSAGE DE LA MATRICE : ETUDE DE CHAQUE COUPLE -- //
    for (RelationIterator ri = Relation::begin(); ri != Relation::end(); ri++){

        // -- ID DES NOTES IMPLIQUEES -- //
        QString& note1 = (*ri)->getNote1();
        QString& note2 = (*ri)->getNote2();

        // -- INDEX MATRICIEL DES NOTES IMPLIQUEES -- //
        int index1 = nm.getIndexId(note1);
        int index2 = nm.getIndexId(note2);

        matriceAdjacence[index1][index2] = 1;
        if (this->estOriente()) matriceAdjacence[index2][index1] = 1;
    }
}


