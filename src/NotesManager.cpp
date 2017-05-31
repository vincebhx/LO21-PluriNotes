#include "NotesManager.h"

#define DYN_ALLOC_STEP 5

NotesManager* NotesManager::_instance = 0;

NotesManager& NotesManager::instance() {
    if(_instance == 0) _instance = new NotesManager;
    return *_instance;
}

NotesManager::~NotesManager() {
    for(unsigned int i = 0; i < nbMaxNotes; i++)
        delete notes[i];
    delete [] notes;
}

bool NotesManager::NoteIterator::isDone() {
    if (nbNotes == 0) return true;
    return nbNotes == index - 1;
}

void NotesManager::addNote(Version* n) {
    for(unsigned int i = 0; i < nbNotes; i++)
        if (notes[i]->currentNote()->getId() == n->currentNote()->getId())
            throw NoteException("Une note possédant cet id existe déjà.");

    if (nbNotes == nbMaxNotes) {
        Version** newNotes = new Version*[nbMaxNotes + DYN_ALLOC_STEP];
        for(unsigned int i = 0; i < nbNotes; i++)
            newNotes[i] = notes[i];
        Version** oldNotes = notes;
        notes = newNotes;
        nbMaxNotes += DYN_ALLOC_STEP;
        if(oldNotes) delete[] oldNotes;
    }

    notes[nbNotes++] = n;
}


void load() {
    QSqlQuery query("SELECT * FROM Article ORDER BY id, version ASC");

    int id = query.record().indexOf("id");
    int version = query.record().indexOf("version");
    int titre = query.record().indexOf("titre");
    int creat = query.record().indexOf("dateCreation");
    int modif = query.record().indexOf("dateModification");
    int texte = query.record().indexOf("texte");
    Version *v = new Version;

    while (query.next())
    {
           //while (meme id) {
            /*
           id = query.value(id).toString();
           version = query.value(version);
           titre = query.value(titre);
                  texte = query.value(texte).toString();
           creation = creation.fromString(query.value(dateCreation).toString(), "dd/MM/yyyy hh:mm:ss");
           modification = modification.fromString(query.value(dateModification).toString(), "dd/MM/yyyy hh:mm:ss");

    */
        std::cout<<query.value(id).toString().toStdString()<<" "<<query.value(version).toInt()<<std::endl;
        Article* a = new Article(
            query.value(id).toString(),
            query.value(version).toInt(),
            query.value(titre).toString(),
            query.value(texte).toString(),
            QDateTime::fromString(query.value(creat).toString(), "dd/MM/yyyy hh:mm:ss"),
            QDateTime::fromString(query.value(modif).toString(), "dd/MM/yyyy hh:mm:ss")
        );
           //}
        v->addNote(a);
    }
    NotesManager::instance().addNote(v);
}
