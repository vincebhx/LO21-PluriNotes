#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "Note.h"
#include "Version.h"
#include "NoteException.h"
#include "DbManager.h"
#include <QFileDialog>
#include <QString>
#include <QDateTime>
#include <QSqlRecord>
#include <QVariant>
#include <iostream>

class NotesManager {
friend class NoteIterator;
private:
    Version** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    static NotesManager* _instance;
    NotesManager(): notes(nullptr), nbNotes(0), nbMaxNotes(0) {
        DbManager::instance();
        NotesManager::load();
    }
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
        void first() { index = 0; std::cout<<"index = 0 - nbNotes = "<<nbNotes<<" "; }
        void next() { index++; std::cout<<"index = "<<index<<" "; }
        bool isDone();
        Note* currentNote() { return instance().notes[index]->currentNote(); }
        Version* currentVersion() { return instance().notes[index]; }
    };

    NoteIterator iterator() const { return NoteIterator(nbNotes); }
    void addNote(Version* n);
    void load();
};

#endif // NOTESMANAGER_H
