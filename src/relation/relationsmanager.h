#ifndef RELATIONSMANAGER_H
#define RELATIONSMANAGER_H

#include <QPair>
#include "relation.h"
#include "./src/dbmanager.h"

class RelationsManager {

friend class RMIterator;

private:
    static RelationsManager* _instance;
    RelationsManager();
    ~RelationsManager();

    Relation** relations;
    unsigned int nbMaxRelations;
    unsigned int nbRelations;

    void loadCouples();
    void loadRelations();
public:
    ///Singleton accessor
    static RelationsManager& instance();
    void load();
    void free();

    void addRelation(Relation* r);

    /// ----- RELATIONMANAGERITERATOR : PERMET DE PARCOURIR LES DIFFERENTES RELATIONS EXISTANTES ----- ///
    class RMIterator{
        friend class RelationsManager;
    private:
        const RelationsManager* instanceRM;
        unsigned int index;
        RMIterator(const RelationsManager* relM): instanceRM(relM), index(0) {}
    public:
        void first() { index = 0; }
        void next() { index++; }
        bool isDone() { if (instanceRM->nbRelations == 0) return true; else return (index + 1 == instanceRM->nbRelations); }
        Relation* currentItem(){ return instanceRM->relations[index]; }

    };
};

#endif // RELATIONSMANAGER_H
