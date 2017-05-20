#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "Note.h"

class NotesManager {
friend class NoteIterator;
private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    static NotesManager* INSTANCE;
    NotesManager(): notes(nullptr), nbNotes(0), nbMaxNotes(0) {}
    ~NotesManager();
public:
    static NotesManager* instance() {
        if(!INSTANCE)
            INSTANCE = new NotesManager;
        return INSTANCE;
    }
    class NoteIterator {
    friend class NotesManager;
    private:
        unsigned int index;
        unsigned int nbNotes;
        NoteIterator(unsigned int n): nbNotes(n) {}
    public:
        void first() { index = 0; }
        void next() { index++; }
        bool isDone();
        Note* current() { return instance()->notes[index]; }
    };
    NoteIterator iterator() const { return NoteIterator(nbNotes); }
};

#endif // NOTESMANAGER_H
