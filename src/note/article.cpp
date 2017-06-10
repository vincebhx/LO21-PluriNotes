#include "article.h"

#include <iostream>
#include <QTextEdit>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

const QString Article::idStem  = "ART_";
unsigned int Article::idIncrement = 0;

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

QSqlTableModel* Article::getTableModel(QSqlDatabase db) {
    QSqlTableModel* modelArticle = new QSqlTableModel(0, db);
    modelArticle->setTable("Article");
    modelArticle->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelArticle->select();
    modelArticle->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modelArticle->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
    modelArticle->sort(1, Qt::AscendingOrder);    //ORDER BY version ASC
    modelArticle->sort(0, Qt::AscendingOrder);    //ORDER BY id ASC
    return modelArticle;
}

QTableView* Article::getTableView(QSqlTableModel *table) {
    QTableView *viewArticle = new QTableView;
    viewArticle->setModel(table);
    viewArticle->hideColumn(0); // don't show the ID
    return viewArticle;
}

