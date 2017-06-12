#include "couple.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>

QSqlTableModel* Couple::getTableModel(QSqlDatabase db){
        QSqlTableModel* modelCouple = new QSqlTableModel(0, db);
        modelCouple->setTable("RelationNote");
        modelCouple->setEditStrategy(QSqlTableModel::OnManualSubmit);
        modelCouple->select();
        modelCouple->setHeaderData(0, Qt::Horizontal, QObject::tr("relation"));
        modelCouple->setHeaderData(1, Qt::Horizontal, QObject::tr("note1"));
        modelCouple->setHeaderData(2, Qt::Horizontal, QObject::tr("note2"));
        modelCouple->setHeaderData(3, Qt::Horizontal, QObject::tr("label"));
        return modelCouple;
};

QTableView* Couple::getCoupleView(QSqlTableModel *table) {
    QTableView *viewCouple = new QTableView;
    viewCouple->setModel(table);
    return viewCouple;
}

std::vector<QString> Couple::getNotes(){
    std::vector<QString> noms;
    noms.push_back(id1);
    noms.push_back(id2);
    return noms;
}
