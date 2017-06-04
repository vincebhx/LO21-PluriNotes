#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "DbManager.h"
#include "Note.h"
#include "Version.h"

enum NoteType {article = 1, tache = 2, image = 3, audio = 4, video = 5};

typedef vector<Version*>::iterator NMIterator;

class NotesManager {
friend class NoteIterator;
private:
    vector<Version*> notes;
    static NotesManager* _instance;
    NotesManager();
    ~NotesManager();
    void load();
public:
    ///Singleton accessor
    static NotesManager& instance();
    void addNote(Version* n);
    void free();

    Note* currentNote() { return notes.back()->currentNote(); }
    Version* currentVersion() { return notes.back(); }
    NMIterator begin() { return notes.begin(); }
    NMIterator end() { return notes.end(); }
};

#endif // NOTESMANAGER_H
