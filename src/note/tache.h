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

    QFormLayout* getLayout();
    QSqlQuery prepareQuery();
public:
    static unsigned int idIncrement;

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

    void setAction(QString a) { action = a; }
    void setPriorite(unsigned int p) { priorite = p; }
    void setDateEcheance(QDateTime d) { dateEcheance = d; }
    void setStatut(Statut s) { statut = s; }

    QString getAction() const { return action; }
    int getPriorite() const { return priorite; }
    QDateTime getDateEcheance() const { return dateEcheance; }
    Statut getStatut() const { return statut; }

    static QSqlTableModel* getTableModel(QSqlDatabase db);
    static QTableView* getTableView(QSqlTableModel* table);

    QString getClassName() { return "tache"; }
    const QString getTableName() const { return "Tache"; }
};

#endif // TACHE_H
