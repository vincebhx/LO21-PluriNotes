#ifndef VERSION_H
#define VERSION_H

#include "Note.h"

class Version {
private:
    vector<Note*> notes;
public:
    typedef vector<Note*>::iterator VersionIterator;

    Version() {}
    Note* currentNote();
    void addNote(Note* n);
    void parcourir();
    vector<Note*> getNotes() { return notes; }
    Note* getNoteByVersion(int version) { return notes.at(version); }
    unsigned int numberOfVersions() { return notes.size(); }
};

#endif // VERSION_H
