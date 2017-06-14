#ifndef ARTICLE_H
#define ARTICLE_H

#include "note.h"
#include "notesmanager.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

/**
 * @brief La classe Article; elle définit le type de note Article.
 */
class Article: public Note
{
private:
    /**
     * @brief idStem : Racine des id de notes générés automatiquement. Ici : "ART_"
     */
    static const QString idStem;

    ///Texte de l'article
    QString texte;

    /**
     * @brief prepareInsertQuery : prépare la requête d'insertion d'une Note dans la BDD pour la classe Article.
     * @return Retourne la requête d'insertion avec les attributs spécifiques à la classe Article.
     *
     * Voir Note::prepareInsertQuery().
     */
    QSqlQuery prepareInsertQuery();

public:
    /**
     * @brief idIncrement : Numéro des id de notes générés automatiquement. S'incrémente automatiquement à chaque nouvel index de versions d'Article.
     */
    static unsigned int idIncrement;

    /**
     * @brief Article : Constructeur d'Article avec id en paramètre.
     * @param id : identifiant de l'article. Unique avec version
     * @param version : version de l'article. Unique avec id
     * @param titre : titre de l'article. Modifiable par l'utilisateur
     * @param dateCreat : date de création de l'article. Générée automatiquement, sauf chargement depuis la BDD.
     * @param dateModif : date de dernière modification de l'article. Générée automatiquement, sauf chargement depuis la BDD.
     * @param texte : texte de l'article.
     */
    Article(const QString id,
            unsigned int version,
            QString titre,
            QDateTime dateCreat = QDateTime::currentDateTime(),
            QDateTime dateModif = QDateTime::currentDateTime(),
            QString texte = ""):
        Note(id, version, titre, dateCreat, dateModif), texte(texte) { }

    /**
     * @brief Article : Constructeur d'Article avec id généré automatiquement.
     * @param version : version de l'article. Unique avec id
     * @param titre : titre de l'article. Modifiable par l'utilisateur
     * @param dateCreat : date de création de l'article. Générée automatiquement, sauf chargement depuis la BDD.
     * @param dateModif : date de dernière modification de l'article. Générée automatiquement, sauf chargement depuis la BDD.
     * @param texte : texte de l'article.
     *
     * ATTENTION : Ce constructeur doit être appelé uniquement lors de la création d'un nouvel index de versions.
     */
    Article(unsigned int version,
            QString titre,
            QDateTime dateCreat = QDateTime::currentDateTime(),
            QDateTime dateModif = QDateTime::currentDateTime(),
            QString texte = ""):
        Note(idStem + QString::number(idIncrement), version, titre, dateCreat, dateModif), texte(texte) { idIncrement++; }

    /**
     * @brief setTexte est le setter de l'attribut texte.
     * @param t : le texte de l'article.
     */
    void setTexte(QString t) { texte = t; }

    /**
     * @brief getTexte est le getter de l'attribut texte.
     * @return Retourne le texte de l'Article.
     */
    QString getTexte() const { return texte; }

    /**
     * @brief getTableModel : récupère la table Article depuis la base de données db.
     * @param db : la base de données depuis laquelle récupérer la table.
     * @return Retourne un pointeur vers la table Article sous forme d'objet QSqlTableModel.
     */
    static QSqlTableModel* getTableModel(QSqlDatabase db);

    /**
     * @brief getTableView : récupère la vue de la table table passée en paramètre.
     * @param table : Table dont on veut récupérer la vue.
     * @return Retourne la vue de la table choisie.
     */
    static QTableView* getTableView(QSqlTableModel* table);

    /**
     * @brief getClassName : permet d'accéder au nom de la classe courante.
     * @return Retourne le nom de la classe courante ( ici "article").
     *
     * Voir Note::getClassName().
     */
    QString getClassName() { return "article"; }

    /**
    * @brief getTableName : permet d'accéder au nom de la table Article pour pouvoir faire des requêtes selon la classe.
    * @return Retourne le nom de la table dans laquelle insérer les requêtes pour la classe courante (ici "Article).
    *
    * Voir Note::getTableName().
    */
    const QString getTableName() const { return "Article"; }
};

#endif // ARTICLE_H
