#ifndef TACHE_H
#define TACHE_H

#include "note.h"
#include "notesmanager.h"

typedef enum {EN_ATTENTE = 0, EN_COURS = 1, TERMINE = 2} Statut;
static const QString StatutStr[3] = {"enAttente", "enCours", "termine"};

///Décrit une tâche
class Tache: public Note
{
private:
    QString action;
    unsigned int priorite;
    QDateTime dateEcheance;
    Statut statut;

    QFormLayout* getLayout();
    QSqlQuery prepareQuery();
public:
    Tache(const QString id,
          unsigned int version,
          QString titre,
          QDateTime dateCreat = QDateTime::currentDateTime(),
          QDateTime dateModif = QDateTime::currentDateTime(),
          QString action = "",
          unsigned int priorite = 0,
          QDateTime dateEch = QDateTime::currentDateTime(),
          Statut statut = EN_ATTENTE):
        Note(id, version, titre, dateCreat, dateModif), action(action), priorite(priorite), dateEcheance(dateEch), statut(statut) {}

    void setAction(QString a) { action = a; }
    void setPriorite(unsigned int p) {priorite = p; }
    void setDateEcheance(QDateTime d) { dateEcheance = d; }
    void setStatut(Statut s) { statut = s; }

    QString getAction() const { return action; }
    int getPriorite() const { return priorite; }
    QDateTime getDateEcheance() const { return dateEcheance; }
    Statut getStatut() const { return statut; }

    static void load(NotesManager& nm);
};

#endif // TACHE_H
