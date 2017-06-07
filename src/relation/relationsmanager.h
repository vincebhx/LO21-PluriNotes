#ifndef RELATIONSMANAGER_H
#define RELATIONSMANAGER_H

#include <QPair>
#include "relation.h"
#include "./src/dbmanager.h"

typedef std::vector<Relation*>::iterator RMIterator;

class RelationsManager {

// friend class RMIterator;

private:
    static RelationsManager* _instance;
    std::vector<Relation*> relations;
    RelationsManager();
    ~RelationsManager();

    void loadCouples();
    void loadRelations();
public:
    ///Singleton accessor
    static RelationsManager& instance();
    void load();
    void free();

    RMIterator begin() { return relations.begin(); }
    RMIterator end() { return relations.end(); }
    Relation* findRelation(QString titre);
    void addRelation(Relation* r);
    int numberOfRelations() { return relations.size(); }
};

#endif // RELATIONSMANAGER_H
