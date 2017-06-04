#ifndef MEDIA_H
#define MEDIA_H

#include "Note.h"
#include "NotesManager.h"

///Décrit un Média
class Media: public Note {
protected:
    QString description;
    QString filePath;

    Media(const QString id,
          unsigned int version = 0,
          QString titre = NULL,
          QString description = NULL,
          QString file = NULL,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime()):
        Note(id, version, titre, dateCreat, dateModif), description(description), filePath(file) {}

    QFormLayout* getLayout();
    QSqlQuery prepareQuery();

public:
    void setDescription(QString d) { description = d; }
    void setFilePath(QString f) { filePath = f; }
    QString getDescription() const { return description; }
    QString getFilePath() const { return filePath; }

    virtual QString typeToString() const = 0;
    static bool load(NotesManager& nm, QString type);
};

///Décrit une image
class Image: public Media {
public:
    Image(const QString id,
          unsigned int version = 0,
          QString titre = NULL,
          QString description = NULL,
          QString file = NULL,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime()):
        Media(id, version, titre, description, file, dateCreat, dateModif) {}

    QString typeToString() const { return "image"; }
};

///Décrit un fichier audio
class Audio: public Media {
public:
    Audio(const QString id,
          unsigned int version = 0,
          QString titre = NULL,
          QString description = NULL,
          QString file = NULL,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime()):
        Media(id, version, titre, description, file, dateCreat, dateModif) {}

    QString typeToString() const { return "audio"; }
};

///Décrit un fichier vidéo
class Video: public Media {
public:
    Video(const QString id,
          unsigned int version = 0,
          QString titre = NULL,
          QString description = NULL,
          QString file = NULL,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime()):
        Media(id, version, titre, description, file, dateCreat, dateModif) {}

    QString typeToString() const { return "video"; }
};

#endif // MEDIA_H
