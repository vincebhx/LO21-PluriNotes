#include "Version.h"

Note* Version::currentNote() {
    return notes.back();
}

Note* Version::firstNote() {
    return notes.front();
}

void Version::addNote(Note* n) { ///Les versions commencent à 1 !
    notes.push_back(n);
    n->setVersion(notes.size());
}
