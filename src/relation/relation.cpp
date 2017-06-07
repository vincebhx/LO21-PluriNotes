#include "relation.h"
#include "../note/note.h"
#include "couple.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>
#include <QString>
#include <QPair>
#include <iostream>

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

/*
void Relation::addCouple(QPair<Note*, Note*> c){
    if (nbCouples == nbMaxCouples){
        nbMaxCouples += 5;
        QPair* newCouples = new QPair [nbMaxCouples];
        for (unsigned int i = 0; i < nbCouples; i++){
            newCouples[i] = couples[i];
        }
        QPair* oldCouples = couples;

        couples = newCouples;

        if (oldCouples){
            delete[] oldCouples;
        }
    }
    couples[nbCouples++] = &c;
}
*/
