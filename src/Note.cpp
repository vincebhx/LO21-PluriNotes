#include "Note.h"
#include <QLineEdit>
#include <QTextEdit>

//Template Method
QWidget* Note::getNoteView() {
    QWidget* view = new QWidget;
    QFormLayout* layout = getLayout();
    layout->insertRow(0, "Identificateur", new QLineEdit(id));
    layout->insertRow(1, "Titre", new QLineEdit(titre));
    view->setLayout(layout);
    return view;
}

QFormLayout* Article::getLayout() {
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Texte", new QTextEdit(texte));
    return layout;
}

QFormLayout* Tache::getLayout() {
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Action", new QLineEdit(action));
    return layout;
}

QFormLayout* Media::getLayout() {
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Description", new QLineEdit(description));
    layout->addRow("Fichier", new QLineEdit(filePath));
    return layout;
}
