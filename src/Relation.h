#ifndef RELATION_H
#define RELATION_H

#include "Note.h"
#include <QString>

class Relation {
private:
    QString titre;
    QString description;
    bool oriente;
    Note** notes[2];
public:
    static Relation reference;
    Relation(QString t, QString d = NULL, bool o = true): titre(t), description(d), oriente(o) {}
    void setDescription(QString d) { description = d; }
    void orienter(bool o) { oriente = o; }
    QString getTitre() const { return titre; }
    QString getDescription() const { return description; }
    bool estOriente() const { return oriente; }
};

#endif // RELATION_H
