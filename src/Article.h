#ifndef ARTICLE_H
#define ARTICLE_H

#include "Note.h"
#include "NotesManager.h"

///Décrit un Article
class Article: public Note {
private:
    QString texte;
    QFormLayout* getLayout();
    QSqlQuery prepareQuery();
public:
    Article(const QString id,
            unsigned int version = 0,
            QString titre = NULL,
            QString texte = NULL,
            QDateTime dateCreat = QDateTime::currentDateTime(),
            QDateTime dateModif = QDateTime::currentDateTime()):
        Note(id, version, titre, dateCreat, dateModif), texte(texte) {}
    void setTexte(QString t) { texte = t; }
    QString getTexte() const { return texte; }

    static bool load(NotesManager& nm);
};

#endif // ARTICLE_H
