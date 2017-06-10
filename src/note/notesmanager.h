#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "versionindex.h"

typedef std::vector<VersionIndex*>::iterator NMIterator;
typedef enum { ACTIVES = 0, ARCHIVES = 1, CORBEILLE = 2 } Etat;

class NotesManager
{
private:
    std::vector<VersionIndex*> actives;
    std::vector<VersionIndex*> archives;
    std::vector<VersionIndex*> corbeille;

    static NotesManager* _instance;
    NotesManager();
    ~NotesManager();

    static Etat toEtat(int i) { return static_cast<Etat>(i); }

public:
    static NotesManager& instance();
    void free();
    Note* findNote(QString id);

    Note* currentVersion(Etat e) {
        switch(e) {
        case ACTIVES: return actives.back()->currentVersion();
        case ARCHIVES: return archives.back()->currentVersion();
        case CORBEILLE: return corbeille.back()->currentVersion();
        }
    }
    VersionIndex* currentNote(Etat e) {
        switch(e) {
        case ACTIVES: return actives.back();
        case ARCHIVES: return archives.back();
        case CORBEILLE: return corbeille.back();
        }
    }

    NMIterator begin(Etat e) {
        switch(e) {
        case ACTIVES: return actives.begin();
        case ARCHIVES: return archives.begin();
        case CORBEILLE: return corbeille.begin();
        }
    }
    NMIterator end(Etat e) {
        switch(e) {
        case ACTIVES: return actives.end();
        case ARCHIVES: return archives.end();
        case CORBEILLE: return corbeille.end();
        }
    }

    unsigned int nbNotes(Etat e) {
        switch(e) {
        case ACTIVES: return actives.size();
        case ARCHIVES: return archives.size();
        case CORBEILLE: return corbeille.size();
        }
    }

    void addNote(Etat e, VersionIndex* v);
    void load();

    VersionIndex* getNote(int i) { return actives[i];}

    std::vector<VersionIndex*> getTasks();
};

#endif // NOTESMANAGER_H
