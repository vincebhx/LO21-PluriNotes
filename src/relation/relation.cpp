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
    QString t = getTitre();
    QString d = getDescription();

    QString str = "INSERT INTO Relation (titre, description, oriente) VALUES ('" + getTitre() + "', '" + getDescription() + "', " + QString::number(orientation) + ")";
    //query.prepare("INSERT INTO Relation (titre, description, oriente) VALUES (:titre, :description, :orientation");
    //query.bindValue(":titre", getTitre());
    //query.bindValue(":description", getDescription());
    //query.bindValue(":orientation", orientation);
    query.prepare(str);

    return query;
}


QSqlQuery Relation::getDeleteQuery() {
    QSqlQuery query;
    QString str = "DELETE FROM Relation WHERE titre = '" + titre +"'";
    query.prepare(str);
    return query;
}

Couple* Relation::findCouple(QString id1, QString id2) {
    for (RelationIterator it = this->begin(); it != this->end(); it++) {
        QString note1 =(*it)->getNote1();
        QString note2 =(*it)->getNote2();
        if (note1==id1 && note2==id2) {
            return (*it);
        }
    }

    return NULL;
}

void Relation::supprimerCouple(Couple* c){
    couples.erase(std::remove(couples.begin(), couples.end(), c), couples.end());
}
