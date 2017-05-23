#include "Version.h"

Note* Version::currentNote() {
    return notes.front();
}

void Version::addNote(Note* n) {
    notes.insert(notes.begin(), n);
}
