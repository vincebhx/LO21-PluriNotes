#ifndef NOTE_H
#define NOTE_H

#include <Qt>
#include <QList>
#include <QDateTime>
#include <QSqlQuery>
#include <QString>
#include <QDebug>

class VersionIndex;
class Relation;

/**
 * @brief La classe abstraite Note; elle sert d'interface pour ses classes filles.
 */
class Note
{
protected:
    ///Index de versions auquel appartient la note.
    VersionIndex* parent;
    ///Identifiant de la note
    const QString id;
    ///Numéro de version
    unsigned int version;
    ///Titre de la note
    QString titre;
    ///Date de création
    const QDateTime dateCreation;
    ///Date de dernière modification
    QDateTime dateModification;

    /**
     * @brief Constructeur de Note. Appelé uniquement par les constructeurs de ses classes filles.
     * @param id : identifiant de la note. Unique avec version
     * @param version : version de la note. Unique avec id
     * @param titre : titre de la note. Modifiable par l'utilisateur
     * @param dateCreat : date de création de la note. Générée automatiquement, sauf chargement depuis la BDD.
     * @param dateModif : date de dernière modification de la note. Générée automatiquement, sauf chargement depuis la BDD.
     */
    Note(const QString id,
         unsigned int version,
         QString titre,
         QDateTime dateCreat = QDateTime::currentDateTime(),
         QDateTime dateModif = QDateTime::currentDateTime()):
        id(id), version(version), titre(titre), dateCreation(dateCreat), dateModification(dateModif) {}

    /**
     * @brief prepareInsertQuery : prépare la requête d'insertion d'une Note dans la BDD selon la classe fille.
     * @return Retourne la requête d'insertion avec les attributs spécifiques à la classe fille.
     *
     * prepareInsertQuery n'est utilisée que par la méthode getInsertQuery de la classe Note.
     * Elle est ici virtuelle pure, redéfinie dans les classes filles Article, Media et Tache (Template Method).
     * Ceci permet de factoriser le code pour les attributs communs à toutes les notes.
     */
    virtual QSqlQuery prepareInsertQuery() = 0;

public:

    /**
     * @brief getClassName : permet d'accéder au nom de la classe fille courante.
     * @return Retourne le nom de la classe fille courante ("article", "image", "audio", "video" ou "tache").
     */
    virtual QString getClassName() = 0;

    /**
     * @brief getTableName : permet d'accéder au nom de la table dans laquelle insérer les requêtes pour la classe fille courante.
     * @return Retourne le nom de la table dans laquelle insérer les requêtes pour la classe fille courante ("Article, "Media", "Tache").
     */
    virtual const QString getTableName() const = 0;

    /**
     * @brief setParent : permet d'initialiser le pointeur vers l'index de versions parent de la note.
     * @param v : index de versions dans lequel se trouve la note.
     *
     * setParent est appelée lors de l'ajout de la note dans l'index de versions, ou lors de l'initialisation de l'index avec une première note.
     * Appel dans VersionIndex::VersionIndex(Note* n) et VersionIndex::addVersion(Note* n) .
     */
    void setParent(VersionIndex* v) { parent = v; }

    /**
     * @brief getParent : est le getter de l'attribut parent.
     * @return  Retourne un pointeur sur l'index de versions parent de la Note.
     */
    const VersionIndex* getParent() { return parent; }

    /**
     * @brief dateDisplayFormat : format d'affichage des dates.
     */
    static const QString dateDisplayFormat;

    /**
     * @brief dateStorageFormat : format de stockage des dates dans la BDD.
     */
    static const QString dateStorageFormat;

    /**
     * @brief setVersion est le setter de l'attribut version.
     * @param i : le numéro de version (supérieur ou égal à 1).
     */
    void setVersion(unsigned int i) {
        if (i >= 1) version = i;
        else qDebug()<<"setVersion : le numéro de version ne peut pas être égal à 0.";
    }

    /**
     * @brief setTitre est le setter de l'attribut titre.
     * @param t : le titre
     */
    void setTitre(QString t) { titre = t; }

    /**
     * @brief getId : getter de l'attribut id.
     * @return Retourne l'id de la Note.
     */
    const QString& getId() const { return id; }

    /**
     * @brief getVersion : getter de l'attribut version.
     * @return Retourne la version de la note.
     */
    unsigned int getVersion() const { return version; }

    /**
     * @brief getTitre : getter de l'attribut titre.
     * @return retourne le titre de la Note.
     */
    QString getTitre() const { return titre; }

    /**
     * @brief getDateCreat : getter de l'attribut dateCreation.
     * @return Retourne la date de création de la Note (première version).
     */
    const QDateTime& getDateCreat() const {return dateCreation; }

    /**
     * @brief getDateModif : getter de l'attribut dateModification.
     * @return Retourne la date de dernière modification de la Note.
     */
    QDateTime getDateModif() const {return dateModification; }

    /**
     * @brief implicationRelation
     * @param rel
     * @return
     */
    bool implicationRelation(Relation* rel);

    /**
     * @brief implicationRelation
     * @return
     */
    std::vector<Relation*> implicationRelation();

    /**
     * @brief referencee
     * @return
     */
    bool referencee();

    /**
     * @brief archivee
     * @return
     */
    bool archivee();

    /**
     * @brief activee
     * @return
     */
    bool activee();

    /**
     * @brief supprimee
     * @return
     */
    bool supprimee();

    /**
     * @brief referencesTerminees
     * @return
     */
    bool referencesTerminees();

    /**
     * @brief getInsertQuery : initialise la requête d'insertion de la note.
     * @return Retourne la requête d'insertion de la note dans la BDD.
     */
    QSqlQuery getInsertQuery();

    /**
     * @brief getUpdateStateQuery : initialise la requête de mise à jour de l'état de la note.
     * @return Retourne la requête de mise à jour de l'état de la note dans la BDD.
     */
    QSqlQuery getUpdateStateQuery();

    /**
     * @brief getDeleteQuery : retourne la requête de suppression de la note.
     * @return Retourne la requête de suppression de la note dans la BDD.
     */
    QSqlQuery getDeleteQuery();
};

#endif // NOTE_H
