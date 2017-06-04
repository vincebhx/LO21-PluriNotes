#ifndef MEDIA_H
#define MEDIA_H

#include "Note.h"

///Décrit un Média
class Media: public Note {
protected:
    QString description;
    QString filePath;
    Media(const QString id, unsigned int version = 0, QString t = NULL, QString desc = NULL, QString file = NULL,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Note(id, version, t, creat, modif), description(desc), filePath(file) {}
    QFormLayout* getLayout();
    QSqlQuery prepareQuery();
public:
    void setDescription(QString d) { description = d; }
    void setFilePath(QString f) { filePath = f; }
    QString getDescription() const { return description; }
    QString getFilePath() const { return filePath; }
    virtual QString typeToString() const = 0;
};

///Décrit une image
class Image: public Media {
public:
    Image(const QString id, unsigned int version = 0, QString t = NULL, QString desc = NULL, QString file = NULL,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Media(id, version, t, desc, file, creat, modif) {}
    QString typeToString() const { return "image"; }
};

///Décrit un fichier audio
class Audio: public Media {
public:
    Audio(const QString id, unsigned int version = 0, QString t = NULL, QString desc = NULL, QString file = NULL,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Media(id, version, t, desc, file, creat, modif) {}
    QString typeToString() const { return "audio"; }
};

///Décrit un fichier vidéo
class Video: public Media {
public:
    Video(const QString id, unsigned int version = 0, QString t = NULL, QString desc = NULL, QString file = NULL,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Media(id, version, t, desc, file, creat, modif) {}
    QString typeToString() const { return "video"; }
};

#endif // MEDIA_H
