#include "../exception.h"
#include "tache.h"

#include <QComboBox>
#include <QDateTimeEdit>
#include <QLineEdit>

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

    query.prepare("INSERT INTO Tache VALUES (:id, :version, :titre, :dateCreation, :dateModification, :action, :priorite, :statut)");
    query.bindValue(":action", action);
    query.bindValue(":priorite", priorite);
    query.bindValue(":statut", StatutStr[statut]);

    return query;
}

void Tache::load() {

}
