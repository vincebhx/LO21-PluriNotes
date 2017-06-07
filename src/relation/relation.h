#ifndef RELATION_H
#define RELATION_H
#include "./src/note/note.h"
#include "couple.h"
#include <QString>
#include <QPair>
#include <QTableView>
#include <QSqlTableModel>

// Notes : On interdit la recopie.

class Relation {
private:
    QString titre;
    QString description;
    bool oriente;
    unsigned int nbCouples; // nombre de couples de type x, y (x, y et y, x) comptent pour deux
    unsigned int nbMaxCouples;
    QPair<Note*, Note*>* couples;
    void operator=(const Relation& r);
    Relation(const Relation& r); // interdiction de la recopie

public:
    static Relation reference;
    static QSqlTableModel* getTableModel(QSqlDatabase db);
    static QTableView* getRelationView(QSqlTableModel *table);
    Relation(QString t, QString d = NULL, bool o = true): titre(t), description(d), oriente(o) {}
    void setDescription(QString d) { description = d; }
    void orienter(bool o) { oriente = o; }
    QString getTitre() const { return titre; }
    QString getDescription() const { return description; }
    bool estOriente() const { return oriente; }

    //void addCouple(Note* n1, Note* n2, QString label);
};

#endif // RELATION_H
