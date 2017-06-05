#include "versionindex.h"

void VersionIndex::addVersion(Note *n) {
    n->setVersion(versions.size() + 1);
    versions.push_back(n);
}
