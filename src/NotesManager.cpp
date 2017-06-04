#include "Article.h"
#include "Media.h"
#include "NoteException.h"
#include "NotesManager.h"
#include "Tache.h"

#include <QSqlRecord>
#include <QVariant>

#define DYN_ALLOC_STEP 5

NotesManager* NotesManager::_instance = 0;

NotesManager& NotesManager::instance() {
    if(_instance == 0) {
        _instance = new NotesManager;
    }
    return *_instance;
}

NotesManager::NotesManager() {
    cout<<"Construction du NotesManager...";
    load();
    cout<<"NotesManager construit."<<endl;
}

NotesManager::~NotesManager() {
    notes.clear();
}

void NotesManager::addNote(Version* n) {
    for(unsigned int i = 0; i < notes.size(); i++)
        if (notes.at(i)->currentNote()->getId() == n->currentNote()->getId())
            throw NoteException("Une note possédant cet id existe déjà.");
    notes.push_back(n);
}

void NotesManager::free() {
    delete this;
}

void NotesManager::load() {
    cout<<"Chargement des données..."<<endl;

    //Problème actuel : on ne peut charger qu'une seule table, sinon l'appli crashe. :(

    cout<<"Chargement des articles."<<endl;
    Article::load(*this);
    cout<<"Chargement des tâches."<<endl;
    //Tache::load(*this);

    //Media::load(*this, "image");
    //Media::load(*this, "audio");
    //Media::load(*this, "video");

    cout<<"Chargement effectué."<<endl;
}
