#include "Article.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QTextEdit>

using namespace std;

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

bool Article::load(NotesManager& nm)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Article ORDER BY id, version ASC");
    bool success = query.exec();

    if (!success) throw query.lastError();

    int* index = new int;
    index[0] = query.record().indexOf("id");
    index[1] = query.record().indexOf("version");
    index[2] = query.record().indexOf("titre");
    index[3] = query.record().indexOf("dateCreation");
    index[4] = query.record().indexOf("dateModification");
    index[5] = query.record().indexOf("texte");

    QString id, currentId = 0;
    unsigned int sizeCount = 0;
    Version* v = new Version;
    Note* n;

    while (query.next())
    {
        sizeCount++;
        id = query.value(index[0]).toString();

        if(currentId != id) {
            if (currentId != 0) {
               nm.addNote(v);
               v = new Version;
            }
            cout<<"Nouvelle note :"<<endl;
            currentId = id;
        }

        n = new Article(
            id,  //ID
            query.value(index[1]).toInt(),     //Version
            query.value(index[2]).toString(),  //Titre
            query.value(index[5]).toString(),  //Texte
            QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
            QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
        );

        cout<<"Chargement de "<<id.toStdString()<<" v"<<query.value(index[1]).toInt()<<endl;
        v->addNote(n);
    }
    if (sizeCount != 0) nm.addNote(v);

    query.finish();

    return true;
}
