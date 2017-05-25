#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "Note.h"
#include "Version.h"
#include "NoteException.h"
#include <QFileDialog>

class NotesManager {
friend class NoteIterator;
private:
    Version** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    static NotesManager* _instance;
    NotesManager(): notes(nullptr), nbNotes(0), nbMaxNotes(0) {}
    ~NotesManager();
public:
    ///Singleton accessor
    static NotesManager& instance();

    ///Iterator class
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
        Note* currentNote() { return instance().notes[index]->currentNote(); }
        Version* currentVersion() { return instance().notes[index]; }
    };

    NoteIterator iterator() const { return NoteIterator(nbNotes); }
    void addNote(Version* n);
};

#endif // NOTESMANAGER_H
