#ifndef MEDIA_H
#define MEDIA_H

#include "note.h"
#include "notesmanager.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

typedef enum { IMAGE = 0, AUDIO = 1, VIDEO = 2 } Type;
static const QString TypeStr[3] = {"image", "audio", "video"};

/**
 * @brief La classe abstraite Media; elle définit le type de note Media, et sert d'interface pour ses classes filles.
 */
class Media: public Note
{
protected:
    ///Description du média.
    QString description;

    ///Chemin d'accès au fichier contenant le média.
    QString filepath;

    /**
     * @brief Media : constructeur de Media.
     * @param id : identifiant du média. Unique avec version
     * @param version : version du média. Unique avec id
     * @param titre : titre du média. Modifiable par l'utilisateur
     * @param dateCreat : date de création du média. Générée automatiquement, sauf chargement depuis la BDD.
     * @param dateModif : date de dernière modification du média. Générée automatiquement, sauf chargement depuis la BDD.
     * @param description : description du média.
     * @param filepath : chemin d'accès au fichier contenant le média.
     */
    Media(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Note(id, version, titre, dateCreat, dateModif), description(description), filepath(filepath) {}

    QSqlQuery prepareInsertQuery();

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

/**
 * @brief La classe Image; elle définit le type de note Image.
 */
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

/**
 * @brief La classe Audio; elle définit le type de note Audio.
 */
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

/**
 * @brief La classe Video; elle définit le type de note Video.
 */
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
