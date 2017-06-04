#ifndef ARTICLE_H
#define ARTICLE_H

#include "Note.h"

///Décrit un Article
class Article: public Note {
private:
    QString texte;
    QFormLayout* getLayout();
    QSqlQuery prepareQuery();
public:
    Article(const QString id, unsigned int version = 0, QString t = NULL, QString te = NULL,
            QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Note(id, version, t, creat, modif), texte(te) {}
    void setTexte(QString t) { texte = t; }
    QString getTexte() const { return texte; }
};

#endif // ARTICLE_H
