#ifndef COUPLE_H
#define COUPLE_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QTableView>
#include <QString>
#include "../note/note.h"

class Relation;

class Couple {
private:
    QString id1;
    QString id2;
    QString label;
public:
    // -- CONSTRUCTEURS -- //
    Couple(QString& n1, QString& n2, QString& l): id1(n1), id2(n2), label(l){}
    Couple(QString& n1, QString& n2): id1(n1), id2(n2){
        QString labelVide("");
        setLabel(labelVide);
    }
    ~Couple();

    // -- SETTERS, GETTERS -- //
    QString getLabel(){ return label; }
    void setLabel(QString& l) { label = l; }
    QString& getNote1() { return id1; }
    QString& getNote2() { return id2; }
    std::vector<QString> getNotes();

    // -- RECUPERATION DES DONNEES DANS LA BDD -- //
    static QSqlTableModel* getTableModel(QSqlDatabase db);
    static QTableView* getCoupleView(QSqlTableModel *table);

    QSqlQuery getQuery(Relation* r);
};

#endif // COUPLE_H
