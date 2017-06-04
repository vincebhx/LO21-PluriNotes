#include "Tache.h"
#include <QComboBox>
#include <QDateTimeEdit>
#include <QLineEdit>

QFormLayout* Tache::getLayout() {
    //Sélection du statut
    QComboBox* statutBox = new QComboBox;
    statutBox->addItem("En attente");
    statutBox->addItem("En cours");
    statutBox->addItem("Terminé");
    if (statut == enAttente) statutBox->setCurrentIndex(0);     //En attente
    else if (statut == enCours) statutBox->setCurrentIndex(1);  //En cours
    else statutBox->setCurrentIndex(2);                         //Terminé

    //Action
    QLineEdit* actionEdit = new QLineEdit(action);
    actionEdit->setFixedWidth(300);

    //Date d'échéance
    QDateTimeEdit* echeanceEdit = new QDateTimeEdit(dateEcheance);
    echeanceEdit->setFixedWidth(300);

    //Layout et retour
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

    QString s;
    if (statut == enAttente) s = "enAttente";
    else if (statut == enCours) s = "enCours";
    else s = "termine";
    query.bindValue(":statut", s);

    return query;
}
