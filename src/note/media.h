#ifndef MEDIA_H
#define MEDIA_H

#include "note.h"
#include "notesmanager.h"

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

    static void load(NotesManager& nm, Type type);

    virtual const QString getTypeStr() const = 0;
};

///Décrit une image
class Image: public Media {
public:
    Image(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) {}

    const QString getTypeStr() const { return TypeStr[IMAGE]; }
};

///Décrit un fichier audio
class Audio: public Media {
public:
    Audio(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) {}

    const QString getTypeStr() const { return TypeStr[AUDIO]; }
};

///Décrit un fichier vidéo
class Video: public Media {
public:
    Video(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) {}

    const QString getTypeStr() const { return TypeStr[VIDEO]; }
};

#endif // MEDIA_H
