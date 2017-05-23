#include "Version.h"

Version::Version() {

}

Note* Version::currentNote() {
    return notes.front();
}

void Version::addNote(Note* n) {
    notes.push_front(n);
}

void Version::parcourir() {
for(list<Note*>::iterator it = notes.begin(); it != notes.end(); ++it)
    std::cout<<(*it)->getId().toStdString()<<std::endl;
}

Note* Version::getNoteByVersion(int version) {
    list<Note*>::iterator it = notes.begin();
    std::advance(it, version);
    return *it;
}
