#ifndef NOTE_H
#define NOTE_H

#include <Qt>
#include <QDateTime>
#include <QFormLayout>
#include <QSqlQuery>
#include <QString>

///Décrit une Note (interface, classe abstraite)
class Note
{
protected:
    const QString id;               ///Identifiant de la note
    unsigned int version;           ///Numéro de version
    QString titre;                  ///Titre de la note
    const QDateTime dateCreation;   ///Date de création
    QDateTime dateModification;     ///Date de dernière modification

    Note(const QString id,
         unsigned int version,
         QString titre,
         QDateTime dateCreat = QDateTime::currentDateTime(),
         QDateTime dateModif = QDateTime::currentDateTime()):
        id(id), version(version), titre(titre), dateCreation(dateCreat), dateModification(dateModif) {}

    virtual QFormLayout* getLayout() = 0;
    virtual QSqlQuery prepareQuery() = 0;

public:
    static const QString dateDisplayFormat;
    static const QString dateStorageFormat;

    void setVersion(unsigned int i) { version = i; }
    void setTitre(QString t) { titre = t; }

    const QString& getId() const { return id; }
    unsigned int getVersion() const { return version; }
    QString getTitre() const { return titre; }
    const QDateTime& getDateCreat() const {return dateCreation; }
    QDateTime getDateLastMOdif() const {return dateModification; }

    QWidget* getNoteView();
    QSqlQuery getQuery();
};

#endif // NOTE_H