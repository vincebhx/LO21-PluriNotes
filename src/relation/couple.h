#ifndef COUPLE_H
#define COUPLE_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QTableView>
#include <QPair>
#include "../note/note.h"
#include "relation.h"


class Couple
{
private:
    QPair<Note*, Note*> couple;
public:
    Couple();
    ~Couple();

    // -- RECUPERATION DES DONNEES DANS LA BDD -- //
    QSqlTableModel* getTableModel(QSqlDatabase db);
    QTableView* getCoupleView(QSqlTableModel *table);
};

#endif // COUPLE_H
