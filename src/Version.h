#ifndef VERSION_H
#define VERSION_H

#include "Note.h"

typedef vector<Note*>::iterator VersionIterator;

class Version {
private:
    vector<Note*> notes;
public:
    Version() {}
    Note* firstNote();  ///Renvoie la première version de la note.
    Note* currentNote();    ///Renvoie la version courante de la note.
    void addNote(Note* n);
    VersionIterator begin() { return notes.begin(); }
    VersionIterator end() { return notes.end(); }
    Note* getNoteByVersion(int version) { return notes.at(version); }
    unsigned int numberOfVersions() { return notes.size(); }
};

#endif // VERSION_H
