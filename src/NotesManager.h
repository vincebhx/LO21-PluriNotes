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


typedef vector<Version*>::iterator NMIterator;

class NotesManager {
friend class NoteIterator;
private:
    vector<Version*> notes;
    static NotesManager* _instance;
    NotesManager() {
        DbManager::instance();
        NotesManager::load();
    }
    ~NotesManager();
    void loadArticles();
    void loadTaches();
    void loadMedia();
public:
    ///Singleton accessor
    static NotesManager& instance();

    void addNote(Version* n);
    void load();
    Note* currentNote() { return notes.back()->currentNote(); }
    Version* currentVersion() { return notes.back(); }
    NMIterator begin() { return notes.begin(); }
    NMIterator end() { return notes.end(); }
};

#endif // NOTESMANAGER_H
