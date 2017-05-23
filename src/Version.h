#ifndef VERSION_H
#define VERSION_H

#include "Note.h"

class Version {
private:
    list<Note*> notes;
public:
    Version();
    Note* currentNote();
    Note* getNoteByVersion(int version);
    void addNote(Note* n);
    void parcourir();
};

#endif // VERSION_H
