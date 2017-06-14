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
    Relation(QString t, QString d = NULL, bool o = true): titre(t), description(d), oriente(o) {}
    void setDescription(QString d) { description = d; }
    void orienter(bool o) { oriente = o; }
    QString getTitre() const { return titre; }
    QString getDescription() const { return description; }
    bool estOriente() const { return oriente; }

    RelationIterator begin() { return couples.begin(); }
    RelationIterator end() { return couples.end(); }

    QSqlQuery getInsertQuery();
    QSqlQuery getDeleteQuery();

    void addCouple(Couple* c);
    void deleteCouples() { couples.clear(); }

    int getNbCouples() {return couples.size();}
};




#endif // RELATION_H
