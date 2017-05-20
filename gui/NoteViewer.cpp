#include "NoteViewer.h"

NoteViewer::NoteViewer()
{
    QLineEdit *nom = new QLineEdit;
    QLineEdit *prenom = new QLineEdit;
    QLineEdit *age = new QLineEdit;

    QFormLayout *layout = new QFormLayout;
    layout->addRow("Votre nom", nom);
    layout->addRow("Votre prénom", prenom);
    layout->addRow("Votre âge", age);

    this->setLayout(layout);
}

void NoteViewer::ViewNote(Note *n) {
    QLineEdit* id;
    QLineEdit* titre;
    QTextEdit* text;
}
