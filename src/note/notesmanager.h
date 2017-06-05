#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "versionindex.h"

typedef std::vector<VersionIndex*>::iterator NMIterator;

class NotesManager
{
private:
    std::vector<VersionIndex*> notes;

    static NotesManager* _instance;
    NotesManager();
    ~NotesManager();

    void load();

public:
    static NotesManager& instance();
    void free();

    Note* currentVersion() { return notes.back()->currentVersion(); }
    VersionIndex* currentNote() { return notes.back(); }

    NMIterator begin() { return notes.begin(); }
    NMIterator end() { return notes.end(); }

    unsigned int nbOfNotes() { return notes.size(); }

    void addNote(VersionIndex* v);
};

#endif // NOTESMANAGER_H
