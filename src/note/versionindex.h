#ifndef VERSIONINDEX_H
#define VERSIONINDEX_H

#include "note.h"

typedef std::vector<Note*>::iterator VersionIterator;

class VersionIndex
{
private:
    std::vector<Note*> versions;

public:
    VersionIndex() {}

    Note* firstVersion() { return versions.front(); }
    Note* currentVersion() { return versions.back(); }
    Note* at(unsigned int version) { return versions.at(version); }

    VersionIterator begin() { return versions.begin(); }
    VersionIterator end() { return versions.end(); }

    unsigned int nbOfVersions() { return versions.size(); }

    void addVersion(Note* n);
};

#endif // VERSIONINDEX_H
