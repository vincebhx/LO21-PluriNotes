#include "note.h"
#include "notesmanager.h"
#include "./src/relation/relationsmanager.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

const QString Note::dateDisplayFormat = "ddd dd MMMM yyyy à hh:mm:ss";
const QString Note::dateStorageFormat = "dd/MM/yyyy hh:mm:ss";

QWidget* Note::getNoteView() {
    QWidget* view = new QWidget;

    //Date de création
    QLabel* dateCreatEdit = new QLabel(dateCreation.toString(dateDisplayFormat));

    //Date de modification
    QLabel* dateModifEdit = new QLabel(dateModification.toString(dateDisplayFormat));

    //Titre
    QLineEdit* titreEdit = new QLineEdit(titre);
    titreEdit->setFixedWidth(300);

    //Layout
    QFormLayout* formLayout = getLayout();
    formLayout->insertRow(0, "Identificateur", new QLabel(id, view));
    formLayout->insertRow(1, "Version", new QLabel(QString::number(version), view));
    formLayout->insertRow(2, "Création", dateCreatEdit);
    formLayout->insertRow(3, "Dernière modification", dateModifEdit);
    formLayout->insertRow(4, "Titre", titreEdit);
    formLayout->setHorizontalSpacing(10);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addItem(formLayout);

    //Bouton
    QPushButton* saveButton = new QPushButton("Sauver", view);
    layout->addWidget(saveButton);
    //Le slot saveNote() n'est pas encore défini
    //QObject::connect(saveButton, SIGNAL(clicked()), view, SLOT(saveNote()));

    //Vue et retour
    view->setLayout(layout);
    return view;
}

QSqlQuery Note::getQuery() {
    QSqlQuery query = prepareQuery();
    query.bindValue(":etat", parent->getEtat());
    query.bindValue(":id", id);
    query.bindValue(":version", version);
    query.bindValue(":titre", titre);
    query.bindValue(":dateCreation", dateCreation.toString(dateStorageFormat));
    query.bindValue(":dateModification", dateModification.toString(dateStorageFormat));
    return query;
}
