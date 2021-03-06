#include "versionindex.h"
#include "../dbmanager.h"

VersionIndex::VersionIndex(Note* n) {
    std::vector<Note*> ver(1, n);   //On initialise ver avec 1 fois n (équivalent à ver.push_back(n);)
    n->setVersion(1);
    n->setParent(this);
    versions = ver;
}

void VersionIndex::addVersion(Note* n) {
    n->setVersion(versions.size() + 1);
    n->setParent(this);
    versions.push_back(n);
}
