#ifndef TACHE_H
#define TACHE_H

#include "note.h"
#include "notesmanager.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

typedef enum {EN_ATTENTE = 0, EN_COURS = 1, TERMINE = 2} Statut;
static const QString StatutStr[3] = {"enAttente", "enCours", "termine"};

///Décrit une tâche
class Tache: public Note
{
private:
    static const QString idStem;

    QString action;
    unsigned int priorite;
    QDateTime dateEcheance;
    Statut statut;

    QSqlQuery prepareInsertQuery();
public:
    static unsigned int idIncrement;
    /**
     * @brief Tache Premier constructeur de Tache
     */
    Tache(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString action = "",
          unsigned int priorite = 0,
          QDateTime dateEch = QDateTime::currentDateTime(),
          Statut statut = EN_ATTENTE):
        Note(id, version, titre, dateCreat, dateModif),
        action(action), priorite(priorite), dateEcheance(dateEch), statut(statut) { }
    /**
     * @brief Tache Deuxième constructeur de Tache
     */
    Tache(unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString action = "",
          unsigned int priorite = 0,
          QDateTime dateEch = QDateTime::currentDateTime(),
          Statut statut = EN_ATTENTE):
        Note(idStem + QString::number(idIncrement), version, titre, dateCreat, dateModif),
        action(action), priorite(priorite), dateEcheance(dateEch), statut(statut) { idIncrement++; }

    /**
     * @brief setAction change l'action de la tache
     * @param a : nouvelle action
     */
    void setAction(QString a) { action = a; }
    /**
     * @brief setPriorite  change la priorité de la tache
     * @param p : nouvelle priorité
     */
    void setPriorite(unsigned int p) { priorite = p; }
    /**
     * @brief setDateEcheance change la date d'échéance de la tache
     * @param d : nouvelle date d'échéance
     */
    void setDateEcheance(QDateTime d) { dateEcheance = d; }
    /**
     * @brief setStatut change le statut de la tache
     * @param s : nouveau statut
     */
    void setStatut(Statut s) { statut = s; }
    /**
     * @brief getAction récupère l'action de la tache
     * @return Retour sous forme QString
     */
    QString getAction() const { return action; }
    /**
     * @brief getPriorite récupère la priorité de la tache
     * @return Retour sous forme entier
     */
    int getPriorite() const { return priorite; }
    /**
     * @brief getDateEcheance récupère la date d'échéance
     * @return Retour sous forme de QDateTime
     */
    QDateTime getDateEcheance() const { return dateEcheance; }
    /**
     * @brief getStatut récupère le statut
     * @return Retourne le statut
     */
    Statut getStatut() const { return statut; }

    static QSqlTableModel* getTableModel(QSqlDatabase db);
    /**
     * @brief getTableView : récupère la vue de la table table passée en paramètre.
     * @param table : Table dont on veut récupérer la vue.
     * @return Retourne la vue de la table choisie.
     */
    static QTableView* getTableView(QSqlTableModel* table);

    QString getClassName() { return "tache"; }
    const QString getTableName() const { return "Tache"; }
};

#endif // TACHE_H
