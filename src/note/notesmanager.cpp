#include "article.h"
#include "media.h"
#include "notesmanager.h"
#include "tache.h"
#include "../exception.h"

#include <iostream>

NotesManager* NotesManager::_instance = 0;

NotesManager::NotesManager() {
    std::cout<<"Construction du NotesManager."<<std::endl;
}

NotesManager::~NotesManager() {
    notes.clear();
    std::cout<<"NotesManager détruit."<<std::endl;
}

NotesManager& NotesManager::instance() {
    if(_instance == 0) {
        _instance = new NotesManager;
    }
    return *_instance;
}

void NotesManager::free() {
    delete this;
}

void NotesManager::addNote(VersionIndex* n) {
    for(unsigned int i = 0; i < notes.size(); i++)
        if (notes.at(i)->currentVersion()->getId() == n->currentVersion()->getId())
            throw Exception("Une note possédant l'id " + n->currentVersion()->getId() + " existe déjà.");
    notes.push_back(n);
}

void NotesManager::load() {
    std::cout<<"Chargement des données depuis la base..."<<std::endl;

    Article::load(*this);
    Image::load(*this);
    Audio::load(*this);
    Video::load(*this);
    Tache::load(*this);

    std::cout<<"Chargement effectué."<<std::endl;
}
