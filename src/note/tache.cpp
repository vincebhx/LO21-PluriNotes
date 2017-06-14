#include "../exception.h"
#include "tache.h"

#include <QComboBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QSqlError>
#include <QSqlRecord>

#include <iostream>

const QString Tache::idStem  = "TCH_";
unsigned int Tache::idIncrement = 0;

QSqlQuery Tache::prepareInsertQuery() {
    QSqlQuery query;

    query.prepare("INSERT INTO Tache VALUES (:etat, :id, :version, :titre, :dateCreation, :dateModification, :action, :priorite, :dateEcheance, :statut)");
    query.bindValue(":action", action);
    query.bindValue(":priorite", priorite);
    query.bindValue(":dateEcheance", dateEcheance.toString(dateStorageFormat));
    query.bindValue(":statut", StatutStr[statut]);

    return query;
}

QSqlTableModel* Tache::getTableModel(QSqlDatabase db) {
    QSqlTableModel* modelTache = new QSqlTableModel(0, db);
    modelTache->setTable("Tache");
    modelTache->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelTache->select();
    modelTache->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modelTache->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
    modelTache->sort(1, Qt::AscendingOrder);    //ORDER BY version ASC
    modelTache->sort(0, Qt::AscendingOrder);    //ORDER BY id ASC
    return modelTache;
}

QTableView* Tache::getTableView(QSqlTableModel *table) {
    QTableView *viewTache = new QTableView;
    viewTache->setModel(table);
    viewTache->hideColumn(0); // don't show the ID
    return viewTache;
}
