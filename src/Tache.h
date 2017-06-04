#ifndef TACHE_H
#define TACHE_H

#include "Note.h"
#include "NotesManager.h"

///Décrit une Tâche
class Tache: public Note {
private:
    QString action;
    int priorite;
    QDateTime dateEcheance;
    Statut statut;
    QFormLayout* getLayout();
    QSqlQuery prepareQuery();
public:
    Tache(const QString id, unsigned int version = 0, QString t = NULL, QString act = NULL, int pr = 0, QDateTime dateEch = QDateTime::currentDateTime(),
          Statut s = enAttente, QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Note(id, version, t, creat, modif), action(act), priorite(pr), dateEcheance(dateEch), statut(s) {}
    void setAction(QString a) { action = a; }
    void setPriorite(int p) { priorite = p; }
    void setDateEcheance(QDateTime d) { dateEcheance = d; }
    void setStatut(Statut s) { statut = s; }
    QString getAction() const { return action; }
    int getPriorite() const { return priorite; }
    QDateTime getDateEcheance() const { return dateEcheance; }
    Statut getStatut() const { return statut; }

    static bool load(NotesManager& nm);
};

#endif // TACHE_H
