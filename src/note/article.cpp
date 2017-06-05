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

void Article::load(NotesManager &nm) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Article ORDER BY id, version ASC");
    bool success = query.exec();
    if(!success) throw query.lastError();

    int* index = new int;
    index[0] = query.record().indexOf("id");
    index[1] = query.record().indexOf("version");
    index[2] = query.record().indexOf("titre");
    index[3] = query.record().indexOf("dateCreation");
    index[4] = query.record().indexOf("dateModification");
    index[5] = query.record().indexOf("texte");

    if (query.first()) {
        QString id;
        QString currentId = query.value(index[0]).toString();
        VersionIndex* vindex = new VersionIndex;
        Note* n;

        do {
            id = query.value(index[0]).toString();

            n = new Article(
                id,  //ID
                query.value(index[1]).toInt(),     //Version
                query.value(index[2]).toString(),  //Titre
                QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de modification
                query.value(index[5]).toString()  //Texte
            );

            if (id != currentId) {
                currentId = id;
                nm.addNote(vindex);
                vindex = new VersionIndex;
            }

            vindex->addVersion(n);
        } while (query.next());
    }

    query.finish();
}

