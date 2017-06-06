#include "note.h"
#include "../../ui/noteviewer.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

const QString Note::dateDisplayFormat = "ddd dd MMMM yyyy à hh:mm:ss";
const QString Note::dateStorageFormat = "dd/MM/yyyy hh:mm:ss";

NoteViewer* Note::getNoteView() {
    NoteViewer* view = new NoteViewer;

    //Date de création
    QLabel* dateCreatEdit = new QLabel(dateCreation.toString(dateDisplayFormat), view);

    //Date de modification
    QLabel* dateModifEdit = new QLabel(dateModification.toString(dateDisplayFormat), view);

    //Titre
    QLineEdit* titreEdit = new QLineEdit(titre, view);
    titreEdit->setFixedWidth(300);

    //Layout
    QFormLayout* formLayout = getLayout();
    formLayout->insertRow(0, "Identificateur", new QLabel(id, view));
    formLayout->insertRow(1, "Création", dateCreatEdit);
    formLayout->insertRow(2, "Dernière modification", dateModifEdit);
    formLayout->insertRow(3, "Titre", titreEdit);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addItem(formLayout);

    //Bouton
    QPushButton* saveButton = new QPushButton("Sauver", view);
    layout->addWidget(saveButton);
    QObject::connect(saveButton, SIGNAL(clicked()), view, SLOT(saveNote()));

    //Vue et retour
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
