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

QSqlQuery Relation::getInsertQuery(){
    QSqlQuery query;

    query.prepare("INSERT INTO Relation VALUES (:titre, :description, :orientation)");
    query.bindValue(":titre", getTitre());
    query.bindValue(":description", getDescription());
    if (estOriente()) query.bindValue(":orientation", 1);
    else query.bindValue("orientation", 0);

    return query;
}


QSqlQuery Relation::getDeleteQuery(){
    QSqlQuery query;

    query.prepare("DELETE FROM Relation WHERE titre = :titre");
    query.bindValue(":titre", getTitre());

    return query;
}


