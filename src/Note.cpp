#include "Note.h"
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>

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

QFormLayout* Article::getLayout() {
    //Texte
    QTextEdit* textEdit = new QTextEdit(texte);

    //Layout et retour
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Texte", textEdit);
    return layout;
}

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
    QDateTimeEdit* echeanceEdit = new QDateTimeEdit(dateEcheance.toQDateTime());
    echeanceEdit->setFixedWidth(300);

    //Layout et retour
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Action", actionEdit);
    layout->addRow("Date d'échéance", echeanceEdit);
    layout->addRow("Statut", statutBox);
    return layout;
}

QFormLayout* Media::getLayout() {
    //Description
    QLineEdit* descEdit = new QLineEdit(description);

    //Fichier
    QLineEdit* fileEdit = new QLineEdit(filePath);

    //Layout et retour
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Description", descEdit);
    layout->addRow("Fichier", fileEdit);
    return layout;
}
