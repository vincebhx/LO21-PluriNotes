#ifndef RELATION_H
#define RELATION_H
#include "./src/note/note.h"
#include "couple.h"
#include <QString>
#include <QPair>

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
    Relation(QString t, QString d = NULL, bool o = true): titre(t), description(d), oriente(o) {}
    void setDescription(QString d) { description = d; }
    void orienter(bool o) { oriente = o; }
    QString getTitre() const { return titre; }
    QString getDescription() const { return description; }
    bool estOriente() const { return oriente; }
    void addCouple(QPair<Note*, Note*> c);

    /*class RelationIterator{
        friend class Relation;
    private:
        const Relation* relation;
        unsigned int index;
        RelationIterator(const Relation* rel): relation(rel), index(0) {}
    public:
        void first() { index = 0; }
        void next() { index++; }
        bool isDone() { if (relation->nbCouples == 0) return true; else return (index + 1 == relation->nbCouples); }
        QPair<Note*, Note*> currentItem(){ return relation->couples[index]; }
    };

    RelationIterator* iterator() { return new RelationIterator(this); }*/
};

#endif // RELATION_H
