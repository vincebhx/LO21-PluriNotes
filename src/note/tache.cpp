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

QFormLayout* Tache::getLayout() {
    //Sélection du statut
    QComboBox* statutBox = new QComboBox;
    statutBox->addItem("En attente");
    statutBox->addItem("En cours");
    statutBox->addItem("Terminé");

    switch (statut) {
    case EN_ATTENTE:
        statutBox->setCurrentIndex(EN_ATTENTE);
        break;
    case EN_COURS:
        statutBox->setCurrentIndex(EN_COURS);
        break;
    case TERMINE:
        statutBox->setCurrentIndex(TERMINE);
        break;
    default:
        throw Exception("Statut invalide lors de la création du layout de la tâche " + this->getId() + " v" + this->getVersion());
    }

    //Action
    QLineEdit* actionEdit = new QLineEdit(action);
    actionEdit->setFixedWidth(300);

    //Date d'échéance
    QDateTimeEdit* echeanceEdit = new QDateTimeEdit(dateEcheance);
    echeanceEdit->setFixedWidth(300);

    //Layout
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Action", actionEdit);
    layout->addRow("Date d'échéance", echeanceEdit);
    layout->addRow("Statut", statutBox);

    return layout;
}

QSqlQuery Tache::prepareQuery() {
    QSqlQuery query;

    query.prepare("INSERT INTO Tache VALUES (:etat, :id, :version, :titre, :dateCreation, :dateModification, :action, :priorite, :statut)");
    query.bindValue(":action", action);
    query.bindValue(":priorite", priorite);
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
