#ifndef RELATION_H
#define RELATION_H
#include "./src/note/note.h"
#include "couple.h"
#include <QString>
#include <QPair>
#include <QTableView>
#include <QSqlTableModel>
#include <vector>

typedef std::vector<Couple*>::iterator RelationIterator;

class Relation {
private:
    QString titre;
    QString description;
    bool oriente;
    std::vector<Couple*> couples;

    // -- INTERDICTION DE RECOPIE -- //
    void operator=(const Relation& r);
    Relation(const Relation& r); // interdiction de la recopie

public:
    static Relation reference;

    static QSqlTableModel* getTableModel(QSqlDatabase db);
    static QTableView* getRelationView(QSqlTableModel *table);

    // -- SETTER - GETTER -- //
    /**
     * @brief Il s'agit du constructeur de Relation.
     * @param Le constructeur de Relation prend en paramètre un QString qui correspondra au titre de la relation à créer.
     * @param Le constructeur de Relation prend en paramètre un QString qui correspondra à la description de la relation à créer (par défaut, elle est vide).
     * @param Le constructeur de Relation prend en paramètre un booléen qui correspondra à l'orientation de la relation à créer (par défaut, elle est orientée).
     */
    Relation(QString t, QString d = NULL, bool o = true): titre(t), description(d), oriente(o) {}

    /**
     * @brief setDescription permet de modifier la description de la relation qui l'appelle.
     * @param setDescription prend en paramètre un QString d correspondant à la nouvelle description de la relation.
     */
    void setDescription(QString d) { description = d; }

    /**
     * @brief orienter permet de changer l'orientation de la relation qui l'appelle.
     * @param orienter prend en paramètre un booléen qui correspond à la nouvelle orientation de la relation.
     */
    void orienter(bool o) { oriente = o; }

    /**
     * @brief getTitre retourne le titre de la relation qui l'appelle.
     * @return getTitre retourne le titre de la relation, qui est un QString.
     */
    QString getTitre() const { return titre; }

    /**
     * @brief getDescription renvoie la description de la relation qui l'appelle.
     * @return getDescription renvoie la description de la relation, qui est un QString.
     */
    QString getDescription() const { return description; }

    /**
     * @brief estOriente renvoie l'orientation de la relation qui l'appelle.
     * @return estOriente renvoie la description de la relation, qui est un QString.
     */
    bool estOriente() const { return oriente; }

    /**
     * @brief begin est utilisée pour itérer dans le vecteur de couple de la relation.
     * @return begin renvoie un RelationIterator, dont le pointeur indique le premier couple contenu dans le vecteur de couples de la relation.
     */
    RelationIterator begin() { return couples.begin(); }

    /**
     * @brief end est utilisée pour itérer dans le vecteur de couple de la relation.
     * @return end renvoie un RelationIterator, dont le pointeur indique le dernier couple contenu dans le vecteur de couples de la relation.
     */
    RelationIterator end() { return couples.end(); }

    /**
     * @brief getInsertQuery retourne la requête d'insertion de la note.
     * @return getInsertQuery retourne la requête d'insertion de la note dans la BDD.
     */
    QSqlQuery getInsertQuery();

    /**
     * @brief getDeleteQuery retourne la requête de suppression de la note.
     * @return getDeleteQuery retourne la requête de suppression de la note dans la BDD.
     */
    QSqlQuery getDeleteQuery();

    /**
     * @brief addCouple rajoute dans la relation qui l'appelle le couple dont le pointeur est passé en paramètre.
     * @param addCouple prend en paramètre le pointeur sur le couple à rajouter dans la relation qui l'appelle.
     */
    void addCouple(Couple* c);

    /**
     * @brief deleteCouples supprime tous les couples contenus dans la relation.
     */
    void deleteCouples() { couples.clear(); }
    void supprimerCouple(Couple* c);

    /**
     * @brief getNbCouples retourne le nombre de couples contenus dans la relation.
     * @return getNbCouples retourne le nombre de couples contenus dans la relation sous forme de int.
     */
    int getNbCouples() {return couples.size();}

    Couple* findCouple(QString id1, QString id2);
};




#endif // RELATION_H
