#include "NotesManager.h"
#define DYN_ALLOC_STEP 5

NotesManager* NotesManager::_instance = 0;

NotesManager& NotesManager::instance() {
    if(_instance == 0) _instance = new NotesManager;
    return *_instance;
}

NotesManager::~NotesManager() {
    for(unsigned int i = 0; i < nbMaxNotes; i++)
        delete notes[i];
    delete [] notes;
}

bool NotesManager::NoteIterator::isDone() {
    if (nbNotes == 0) return true;
    return nbNotes == index + 1;
}

void NotesManager::addNote(Version* n) {
    for(unsigned int i = 0; i < nbNotes; i++)
        if (notes[i]->currentNote()->getId() == n->currentNote()->getId())
            throw NoteException("Une note possédant cet id existe déjà.");

    if (nbNotes == nbMaxNotes) {
        Version** newNotes = new Version*[nbMaxNotes + DYN_ALLOC_STEP];
        for(unsigned int i = 0; i < nbNotes; i++)
            newNotes[i] = notes[i];
        Version** oldNotes = notes;
        notes = newNotes;
        nbMaxNotes += DYN_ALLOC_STEP;
        if(oldNotes) delete[] oldNotes;
    }

    notes[nbNotes++] = n;
}

void NotesManager::load() {

}
