#include "note.h"

#include <QLabel>
#include <QLineEdit>

const QString Note::dateDisplayFormat = "ddd dd MMMM yyyy à hh:mm:ss";
const QString Note::dateStorageFormat = "dd/MM/yyyy hh:mm:ss";

QWidget* Note::getNoteView() {
    //Date de création
    QLabel* dateCreatEdit = new QLabel(dateCreation.toString(dateDisplayFormat));

    //Date de modification
    QLabel* dateModifEdit = new QLabel(dateModification.toString(dateDisplayFormat));

    //Titre
    QLineEdit* titreEdit = new QLineEdit(titre);
    titreEdit->setFixedWidth(300);

    //Layout
    QFormLayout* layout = getLayout();
    layout->insertRow(0, "Identificateur", new QLabel(id));
    layout->insertRow(1, "Création", dateCreatEdit);
    layout->insertRow(2, "Dernière modification", dateModifEdit);
    layout->insertRow(3, "Titre", titreEdit);

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
    query.bindValue(":dateCreation", dateCreation.toString(dateStorageFormat));
    query.bindValue(":dateModification", dateModification.toString(dateStorageFormat));
    return query;
}
