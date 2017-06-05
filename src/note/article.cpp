#include "article.h"

#include <iostream>
#include <QTextEdit>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

QFormLayout* Article::getLayout() {
    //Texte
    QTextEdit* textEdit = new QTextEdit(texte);
    textEdit->setFixedWidth(300);

    //Layout
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

void Article::load() {

}

