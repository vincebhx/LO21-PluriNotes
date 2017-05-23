#include "Version.h"

Note* Version::currentNote() {
    return notes.front();
}

void Version::addNote(Note* n) {
    notes.insert(notes.begin(), n);
}

void Version::parcourir() {
for(VersionIterator it = notes.begin(); it != notes.end(); ++it)
    std::cout<<(*it)->getId().toStdString()<<std::endl;
}
