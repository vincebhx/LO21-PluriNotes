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
    /**
     * @brief prepareInsertQuery Renvoie la requête permettant d'insérer le média dans la base de données
     * @return Retourne la quête sous forme de QSqlQuery
     */
    QSqlQuery prepareInsertQuery();

public:
    /**
     * @brief setDescription : changer la description de l'objet appelant.
     * @param d Nouvelle description
     */
    void setDescription(QString d) { description = d; }
    /**
     * @brief setFilePath : change le filepath de l'objet appelant
     * @param f le nouveau filepath
     */
    void setFilePath(QString f) { filepath = f; }
    /**
     * @brief getDescription Récupère la description du média appelant
     * @return Retourne la description sous forme de QString.
     */
    QString getDescription() const { return description; }
    /**
     * @brief getFilePath : retourne le filepath de l'objet appelant
     * @return Retour sous forme de QString
     */
    QString getFilePath() const {return filepath; }

    virtual const QString getTypeStr() const = 0;
    static QSqlTableModel* getTableModel(QSqlDatabase db);
    /**
     * @brief getTableView : récupère la vue de la table table passée en paramètre.
     * @param table : Table dont on veut récupérer la vue.
     * @return Retourne la vue de la table choisie.
     */
    static QTableView* getTableView(QSqlTableModel* table);

    /**
    * @brief getTableName : permet d'accéder au nom de la table Article pour pouvoir faire des requêtes selon la classe.
    * @return Retourne le nom de la table dans laquelle insérer les requêtes pour la classe courante (ici "Article).
    *
    * Voir Note::getTableName().
    */
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
    /**
     * @brief Image Premier constructeur de Image
     */
    Image(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) { }
    /**
     * @brief Image Deuxième constructeur de Image
     */
    Image(unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(idStem + QString::number(idIncrement), version, titre, dateCreat, dateModif, description, filepath) { idIncrement++; }

    /**
     * @brief getTypeStr retourne le type de Note sous chaîne de caractère.
     * @return Le type est retourné sous forme de QString.
     */
    const QString getTypeStr() const { return TypeStr[IMAGE]; }
    /**
     * @brief getClassName renvoie le nom de la classe de l'image
     * @return Retour sous forme de QString
     */
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
    /**
     * @brief Audio Premier constructeur de Audio
     */
    Audio(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) { }
    /**
     * @brief Audio Deuxième constructeur de Audio
     */
    Audio(unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(idStem + QString::number(idIncrement), version, titre, dateCreat, dateModif, description, filepath) { idIncrement++; }

    /**
     * @brief getTypeStr retourne le type de Note sous chaîne de caractère.
     * @return Le type est retourné sous forme de QString.
     */
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
    /**
     * @brief Video Premier constructeur de Video
     */
    Video(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(id, version, titre, dateCreat, dateModif, description, filepath) { }
    /**
     * @brief Video Deuxième constructeur de Video
     */
    Video(unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString description = "",
          QString filepath = ""):
        Media(idStem + QString::number(idIncrement), version, titre, dateCreat, dateModif, description, filepath) { idIncrement++; }

    /**
     * @brief getTypeStr retourne le type de Note sous chaîne de caractère.
     * @return Le type est retourné sous forme de QString.
     */
    const QString getTypeStr() const { return TypeStr[VIDEO]; }
    /**
     * @brief getClassName renvoie le nom de la classe.
     * @return Renvoi sous forme de QString.
     */
    QString getClassName() { return "video";}
};

#endif // MEDIA_H
