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
    modelRelation->setTable("Relation");
    modelRelation->select();
    modelRelation->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelRelation->setHeaderData(0, Qt::Horizontal, QObject::tr("relation"));
    modelRelation->setHeaderData(1, Qt::Horizontal, QObject::tr("description"));
    modelRelation->setHeaderData(2, Qt::Horizontal, QObject::tr("orientation"));

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
    int orientation;
    if (estOriente()){
        orientation = 1;
    }
    else {
        orientation = 0;
    }
    query.prepare("INSERT INTO Relation VALUES (':titre', ':description', :orientation)");
    query.bindValue(":titre", getTitre());
    query.bindValue(":description", getDescription());
    query.bindValue(":orientation", orientation);
    //query.prepare(str);

    return query;
}

QSqlQuery Relation::getDeleteQuery() {
    QSqlQuery query;
    QString str = "DELETE FROM Relation WHERE titre = '" + titre +"'";
    query.prepare(str);
    return query;
}


