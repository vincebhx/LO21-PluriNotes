#include "NotesManager.h"

NotesManager::~NotesManager() {
    for(unsigned int i = 0; i < nbMaxNotes; i++)
        delete notes[i];
    delete [] notes;
}

bool NotesManager::NoteIterator::isDone() {
    if (nbNotes == 0) return true;
    return nbNotes == index + 1;
}
