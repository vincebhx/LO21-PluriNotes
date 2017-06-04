#include "Note.h"
#include <QLabel>
#include <QLineEdit>
#include <QSqlQuery>

const QString Note::dateFormat = "ddd dd MMMM yyyy à hh:mm:ss";

//Template Method
QWidget* Note::getNoteView() {
    //Date de création
    QLabel* dateCreatEdit = new QLabel(dateCreation.toString(Note::dateFormat));

    //Date de dernière modification
    QLabel* dateModifEdit = new QLabel(dateLastModification.toString(Note::dateFormat));

    //Titre
    QLineEdit* titleEdit = new QLineEdit(titre);
    titleEdit->setFixedWidth(300);

    //Layout
    QFormLayout* layout = getLayout();
    layout->insertRow(0, "Identificateur", new QLabel(id));
    layout->insertRow(1, "Création", dateCreatEdit);
    layout->insertRow(2, "Dernière modification", dateModifEdit);
    layout->insertRow(3, "Titre", titleEdit);

    //Vue et retour
    QWidget* view = new QWidget;
    view->setLayout(layout);
    return view;
}

QSqlQuery Note::getQuery() {
    QSqlQuery query = prepareQuery();
    query.bindValue(":id", id);
    query.bindValue(":version", version);
    query.bindValue(":titre", titre);
    query.bindValue(":dateCreation", dateCreation.toString("dd/MM/yyyy hh:mm:ss"));
    query.bindValue(":dateModification", dateLastModification.toString("dd/MM/yyyy hh:mm:ss"));
    return query;
}
