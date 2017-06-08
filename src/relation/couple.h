#ifndef COUPLE_H
#define COUPLE_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QTableView>
#include <QString>
#include "../note/note.h"


class Couple {
private:
    Note* note1;
    Note* note2;
    QString label;
public:
    Couple(Note* n1, Note* n2, QString l): note1(n1), note2(n2), label(l){}
    ~Couple();
    QString getLabel(Couple& c){ return c.label; }
    void setLabel(Couple& c, QString& l) { c.label = l; }

    // -- RECUPERATION DES DONNEES DANS LA BDD -- //
    static QSqlTableModel* getTableModel(QSqlDatabase db);
    static QTableView* getCoupleView(QSqlTableModel *table);
};

#endif // COUPLE_H
