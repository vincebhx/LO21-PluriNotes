#ifndef ARTICLE_H
#define ARTICLE_H

#include "note.h"
#include "notesmanager.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

///Décrit un article
class Article: public Note
{
private:
    QString texte;

    QFormLayout* getLayout();
    QSqlQuery prepareQuery();

public:
    Article(const QString id,
            unsigned int version,
            QString titre,
            QDateTime dateCreat = QDateTime::currentDateTime(),
            QDateTime dateModif = QDateTime::currentDateTime(),
            QString texte = ""):
        Note(id, version, titre, dateCreat, dateModif), texte(texte) {}

    void setTexte(QString t) { texte = t; }
    QString getTexte() const { return texte; }

    static void load(NotesManager& nm);
    static QSqlTableModel* getTableModel(QSqlDatabase db);
    static QTableView* getTableView(QSqlTableModel* table);
};

#endif // ARTICLE_H
