#include "Article.h"
#include <QTextEdit>

QFormLayout* Article::getLayout() {
    //Texte
    QTextEdit* textEdit = new QTextEdit(texte);
    textEdit->setFixedWidth(300);

    //Layout et retour
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Texte", textEdit);
    return layout;
}

QSqlQuery Article::prepareQuery() {
    QSqlQuery query;
    query.prepare("INSERT INTO Article VALUES (:id, :version, :titre, :dateCreation, :dateModification, :texte)");
    query.bindValue(":texte", texte);
    return query;
}
