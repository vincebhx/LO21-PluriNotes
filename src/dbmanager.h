#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "note/note.h"
#include "./src/relation/relation.h"

#include <QSqlDatabase>
#include <QString>

class DbManager
{
private:
    /**
     * @brief _instance est l'instance unique de DbManager
     */
    static DbManager* _instance;
    /**
     * @brief DbManager est le constructeur de la classe.
     * @param path constitue le chemin jusque la base de données.
     */
    DbManager(const QString& path);

    /**
     * @brief ~DbManager() est le destructeur de la classe DbManager
     */
    ~DbManager();

public:
    QSqlDatabase db;
    /**
     * @brief instance() permet de récupérer l'instance de DbManager.
     * @return instance() retourne l'unique instance de DbManager.
     */
    static DbManager& instance();
    void free();

    /**
     * @brief saveNote() permet de sauvegarder une note dans la base de données.
     * @param saveNote() prend le pointeur de la Note à sauvegarder dans la base de données.
     * @return Retourne un booléen : vrai si la note a été sauvegardée, faux sinon.
     */
    bool saveNote(Note* n);
    /**
     * @brief saveRelation() permet de sauvegarder une relation dans la base de données.
     * @param saveRelation() prend le pointeur de la relation à sauvegarder.
     * @return Retourne un booléen : vrai si la relation a été sauvegardée, faux sinon.
     */
    bool saveRelation(Relation* r);
    /**
     * @brief saveCouple() permet de sauvegarder un couple dans la base de données.
     * @param saveCouple() prend le pointeur du couple à sauvegarder.
     * @return Retourne un booléen : vrai si le couple a été sauvegardée, faux sinon.
     */
    bool saveCouple(Relation* r, Couple* c);
    /**
     * @brief changeNoteState change l'état (Actif - Archivé - Dans la corbeille) de la note en paramètre.
     * @param n : pointeur de la note dont on souhaite changer le statut dans la base de donnée.
     * @return Retourne un booléen : vrai si l'état a bien été changé, faux sinon.
     */
    bool changeNoteState(Note* n);

    bool deleteNote(Note* n);
    /**
     * @brief deleteRelation() permet de retirer une relation de la base de données.
     * @param deleteRelation() prend le pointeur de la relation à effacer.
     * @return Retourne un booléen : vrai si la relation a été retirée, faux sinon.
     */
    bool deleteRelation(Relation* r);
    /**
     * @brief deleteCouple() permet de retirer un couple de la base de données.
     * @param c : pointeur sur le couple à supprimer.
     * @param r : pointeur sur la relation delaquelle on doit supprimer le couple.
     * @return Retourne un booléen : vrai si le couple a été retirée, faux sinon.
     */
    bool deleteCouple(Couple* c, Relation* r);
    /**
     * @brief deleteCouples() permet de retirer tous les couples d'une relation de la base de données.
     * @param r : pointeur de la relation de laquelle on doit retirer tous les couples.
     * @return Retourne un booléen : vrai si les couples ont été retirés, faux sinon.
     */
    bool deleteCouples(Relation* r);
    /**
     * @brief getLastQuery() permet de récupérer la dernière requête exécutée sous l'objet passé en paramètre.
     * @param query : l'objet sous lequel on souhaite récupérer la dernière requête exécutée.
     * @return Retourne sous forme de QString la dernière requête exécutée sous l'objet query.
     */
    QString getLastQuery(const QSqlQuery& query);
};

#endif // DBMANAGER_H
