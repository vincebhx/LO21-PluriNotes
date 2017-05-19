#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "Note.h"

class NotesManager {
private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    static NotesManager* INSTANCE;
    NotesManager() {}
public:
    friend class NoteIterator;
    static NotesManager* instance() {
        if(!INSTANCE)
            INSTANCE = new NotesManager;
        return INSTANCE;
    }
    class NoteIterator {
    private:
        unsigned int index;
    public:
        void first() { index = 0; }
        void next() { index++; }
        bool isDone() { return NotesManager().instance()->nbNotes == index + 1; }
        Note* current() { return NotesManager().instance()->notes[index]; }
    };
};

#endif // NOTESMANAGER_H
