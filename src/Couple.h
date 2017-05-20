#ifndef COUPLE_H
#define COUPLE_H
#include <QString>
#include "Note.h"

class Couple{
private:
    QString label;
    Note* noteX;
    Note* noteY;
public:
    Couple(Note& x, Note& y, const QString& lab): label(lab), noteX(&x), noteY(&y){}
    const QString& getLabel() const { return label; }
    const Note* getNoteX() const { return noteX; }
    const Note* getNoteY() const { return noteY; }
};

#endif // COUPLE_H
