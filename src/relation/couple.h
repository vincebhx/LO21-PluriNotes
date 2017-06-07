#ifndef COUPLE_H
#define COUPLE_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QTableView>
#include <QPair>
#include <QString>
#include "../note/note.h"
#include "relation.h"


class Couple
{
private:
    QPair<Note*, Note*> tuple;
    QString label;
public:
    Couple();
    ~Couple();
    QString getLabel(Couple& c){ return c.label; }
    void setLabel(Couple& c, QString& l) { c.label = l; }

    // -- RECUPERATION DES DONNEES DANS LA BDD -- //
    static QSqlTableModel* getTableModel(QSqlDatabase db);
    static QTableView* getCoupleView(QSqlTableModel *table);
};

#endif // COUPLE_H
