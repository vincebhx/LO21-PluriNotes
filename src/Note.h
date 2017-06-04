#ifndef Note_h
#define Note_h

#include "Date.h"
#include <iostream>

#include <Qt>
#include <QDateTime>
#include <QFormLayout>
#include <QSqlQuery>
#include <QString>
#include <QWidget>

using namespace std;
using namespace TEMPS;

enum Statut {enAttente, enCours, termine};

///Décrit une Note (interface, classe abstraite)
class Note {
protected:
    const QString id;
    unsigned int version;
    QString titre;
    const QDateTime dateCreation;
    QDateTime dateLastModification;

    virtual QFormLayout* getLayout() = 0;
    Note(const QString i, unsigned int vers = 0, QString t = NULL,
         QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        id(i), version(vers), titre(t), dateCreation(creat), dateLastModification(modif) {}
    virtual QSqlQuery prepareQuery() = 0;
public:
    static const QString dateFormat;

    void setTitre(QString t) { titre = t; }
    void setVersion(unsigned int i) { version = i; }

    const QString& getId() const { return id; }
    QString getTitre() const { return titre; }
    unsigned int getVersion() const { return version; }
    const QDateTime& getDateCreat() const { return dateCreation; }
    QDateTime getDateLastModif() const { return dateLastModification; }
    QWidget* getNoteView();
    QSqlQuery getQuery();
};

#endif /* Note_h */
