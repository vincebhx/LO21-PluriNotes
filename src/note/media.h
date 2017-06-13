#ifndef MEDIA_H
#define MEDIA_H

#include "note.h"
#include "notesmanager.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

typedef enum { IMAGE = 0, AUDIO = 1, VIDEO = 2 } Type;
static const QString TypeStr[3] = {"image", "audio", "video"};

///Décrit un média
class Media: public Note
{
protected:
    QString description;
    QString filepath;

    Media(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Note(id, version, titre, dateCreat, dateModif), description(description), filepath(filepath) {}

    QFormLayout* getLayout();
    QSqlQuery prepareQuery();

public:
    void setDescription(QString d) { description = d; }
    void setFilePath(QString f) { filepath = f; }

    QString getDescription() const { return description; }
    QString getFilePath() const {return filepath; }

    virtual const QString getTypeStr() const = 0;
    static QSqlTableModel* getTableModel(QSqlDatabase db);
    static QTableView* getTableView(QSqlTableModel* table);

    const QString getTableName() const { return "Media"; }
};

///Décrit une image
class Image: public Media {
private:
    static const QString idStem;
public:
    static unsigned int idIncrement;

    Image(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) { }

    Image(unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(idStem + QString::number(idIncrement), version, titre, dateCreat, dateModif, description, filepath) { idIncrement++; }

    const QString getTypeStr() const { return TypeStr[IMAGE]; }
    QString getClassName() {return "image";}
};

///Décrit un fichier audio
class Audio: public Media {
private:
    static const QString idStem;
public:
    static unsigned int idIncrement;

    Audio(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) { }

    Audio(unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(idStem + QString::number(idIncrement), version, titre, dateCreat, dateModif, description, filepath) { idIncrement++; }

    const QString getTypeStr() const { return TypeStr[AUDIO]; }
    QString getClassName() {return "audio";}
};

///Décrit un fichier vidéo
class Video: public Media {
private:
    static const QString idStem;
public:
    static unsigned int idIncrement;

    Video(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) { }

    Video(unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(idStem + QString::number(idIncrement), version, titre, dateCreat, dateModif, description, filepath) { idIncrement++; }

    const QString getTypeStr() const { return TypeStr[VIDEO]; }
    QString getClassName() { return "video";}
};

#endif // MEDIA_H
