#include "NotesManager.h"
#include <QDebug>
#define DYN_ALLOC_STEP 5

NotesManager* NotesManager::_instance = 0;

NotesManager& NotesManager::instance() {
    if(_instance == 0) _instance = new NotesManager;
    return *_instance;
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
void NotesManager::loadArticles() {
    QSqlQuery query("SELECT * FROM Article ORDER BY id, version ASC");

    int id = query.record().indexOf("id");
    int version = query.record().indexOf("version");
    int titre = query.record().indexOf("titre");
    int creat = query.record().indexOf("dateCreation");
    int modif = query.record().indexOf("dateModification");
    int texte = query.record().indexOf("texte");

    Version *v = new Version;
    QString currentId = 0;

    while (query.next())
    {
        if(currentId != query.value(id).toString()) {
            cout<<"Nouvelle note :"<<endl;
            if(currentId != 0) {
                addNote(v);
                v = new Version;
            }
            currentId = query.value(id).toString();
        }

        cout<<"Chargement de "<<query.value(id).toString().toStdString()<<" v"<<query.value(version).toInt()<<endl;

        Article* a = new Article(
            query.value(id).toString(),
            query.value(version).toInt(),
            query.value(titre).toString(),
            query.value(texte).toString(),
            QDateTime::fromString(query.value(creat).toString(), "dd/MM/yyyy hh:mm:ss"),
            QDateTime::fromString(query.value(modif).toString(), "dd/MM/yyyy hh:mm:ss")
        );
        v->addNote(a);
    }
    addNote(v);
}

void NotesManager::loadTaches() {

}

void NotesManager::loadMedia() {

}


void NotesManager::load() {
    std::cout<<"Chargement des données..."<<std::endl;

    loadArticles();

    std::cout<<"Chargement effectué."<<std::endl;
}
