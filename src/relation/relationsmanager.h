#ifndef RELATIONSMANAGER_H
#define RELATIONSMANAGER_H

#include <QPair>
#include "relation.h"
#include "./src/dbmanager.h"

typedef std::vector<Relation*>::iterator RMIterator;

/**
 * @brief La classe RelationsManager : elle gère les relations et s'occupe également de charger les couples de ces relations.
 */

class RelationsManager {

// friend class RMIterator;

private:
    static RelationsManager* _instance;
    std::vector<Relation*> relations;
    RelationsManager();
    ~RelationsManager();
    /**
     * @brief loadCouples charge les couples depuis la base de données.
     */
    void loadCouples();
    /**
     * @brief loadRelations charge les relations depuis la base de données.
     */
    void loadRelations();
public:
    ///Singleton accessor
    static RelationsManager& instance();
    /**
     * @brief load permet, à la création du RelationsManager, de charger les relations et couples depuis la base de données.
     */
    void load();
    void free();

    RMIterator begin() { return relations.begin(); }
    RMIterator end() { return relations.end(); }

    /**
     * @brief Permet de retourner le pointeur de la relation portant le titre donnée en argument.
     * @param titre de type QString, il s'agit de celui que doit porter la relation à retourner.
     * @return Un pointeur sur la relation à trouver avec son titre.
    */
    Relation* findRelation(QString titre);

    /**
     * @brief addRelation, permet de rajouter la relation (dont le pointeur est en argument) dans le RelationsManager.
     * @param r, un pointeur sur la relation à ajouter dans le RelationsManager.
     */
    bool addRelation(Relation* r);


    /**
     * @brief addCouple ajoute le couple dans la relation (qui sont en paramètres) dans la base de données, et charge les nouvelles informations dans le RelationsManager.
     * @param titreRelation est le QString correspondant à la relation dans laquelle on doit rajouter le couple. S'il s'agit d'une relation qui n'existe pas, on la crée dans la base de données et on la charge dans le RelationsManager.
     * @param c est le pointeur sur le couple à rajouter.
     * @return addCouple renvoie un booléen qui renseigne sur le bon déroulement du processus.
     */
    bool addCouple(QString titreRelation, Couple* c);

    /**
     * @brief numberOfRelations renseigne sur le nombre de relations contenu par le RelationsManager.
     * @return Un entier correspondant au nombre de relations que contient le RelationsManager.
     */
    int numberOfRelations() { return relations.size(); }

    /**
     * @brief supprimerRelation supprime la relation dont le pointeur est passé en paramètre du RelationsManager. La fonction vérifie que la relation n'est pas Reference, qu'on ne doit jamais supprimer.
     * @param r, un pointeur sur la relation à supprimer.
     */
    void supprimerRelation(Relation* r);

    /**
     * @brief nomRelations renvoie un vecteur de QString correspondant au titre de toutes les relations contenues dans le RelationsManager.
     * @return Un vecteur de QString
     */
    std::vector<QString> nomRelations();

    /**
     * @brief noteImpliqueeDansRelation : la note est-elle impliquée dans une quelconque relation ?
     * @param Un pointeur sur la note dont on doit vérifier si elle est impliquée dans une relation.
     * @return Un booléen renseignant sur l'implication (en tant qu'ascendant ou descendant) de la note dans une quelconque relation.
     */
    bool noteImpliqueeDansRelation(Note* note);

    void supprimerCouple(Relation* r, Couple* c);
    void supprimerCouples(Relation* r);

    QSqlTableModel* getTableModel(QSqlDatabase db);
    QTableView* getCoupleView(QSqlTableModel *table);

};

#endif // RELATIONSMANAGER_H
