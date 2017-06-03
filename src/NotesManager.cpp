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

void NotesManager::load() {
    std::cout<<"Chargement des données..."<<std::endl;

    load(article);
    load(tache);
    load(image);
    load(audio);
    load(video);


    std::cout<<"Chargement effectué."<<std::endl;
}

void NotesManager::load(NoteType nt) {
     QString q;
     switch (nt) {
     case article:
         q = "SELECT * FROM Article ORDER BY id, version ASC";
         break;
     case tache:
         q = "SELECT * FROM Tache ORDER BY id, version ASC";
         break;
     case image:
         q = "SELECT * FROM Media WHERE type = 'image' ORDER BY id, version ASC";
         break;
     case audio:
         q = "SELECT * FROM Media WHERE type = 'audio' ORDER BY id, version ASC";
         break;
     case video:
         q = "SELECT * FROM Media WHERE type = 'video' ORDER BY id, version ASC";
     }
     QSqlQuery query(q);

     int* index = new int;
     index[0] = query.record().indexOf("id");
     index[1] = query.record().indexOf("version");
     index[2] = query.record().indexOf("titre");
     index[3] = query.record().indexOf("dateCreation");
     index[4] = query.record().indexOf("dateModification");

     switch (nt) {
     case article:
         index[5] = query.record().indexOf("texte");
         break;
     case tache:
         index[5] = query.record().indexOf("action");
         index[6] = query.record().indexOf("priorite");
         index[7] = query.record().indexOf("dateEcheance");
         index[8] = query.record().indexOf("statut");
         break;
     default:   //Média
         index[5] = query.record().indexOf("description");
         index[6] = query.record().indexOf("filePath");
     }

     Version* v = new Version;
     QString currentId = 0;
     unsigned int sizeCount = 0;

     while (query.next())
     {
         sizeCount++;
         QString id = query.value(index[0]).toString();
         Note* n;

         if(currentId != id) {
             cout<<"Nouvelle note :"<<endl;
             if (currentId != 0) {
                 addNote(v);
                v = new Version;
             }
             currentId = id;
         }

         switch(nt) {
         case article:
             n = new Article(
                 id,  //ID
                 query.value(index[1]).toInt(),     //Version
                 query.value(index[2]).toString(),  //Titre
                 query.value(index[5]).toString(),  //Texte
                 QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                 QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
             );
             break;
         case tache: {
             Statut statut;
             QString s = query.value(index[8]).toString();
             if (s == "enAttente") statut = enAttente;
             else statut = termine;

             n = new Tache(
                 id,  //ID
                 query.value(index[1]).toInt(),     //Version
                 query.value(index[2]).toString(),  //Titre
                 query.value(index[5]).toString(),  //Action
                 query.value(index[6]).toInt(),     //Priorité
                 QDateTime::fromString(query.value(index[7]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date d'échéance
                 statut, //Statut
                 QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                 QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
            );
            break;
         }
         case image:
             n = new Image(
                 id,  //ID
                 query.value(index[1]).toInt(),     //Version
                 query.value(index[2]).toString(),  //Titre

                 query.value(index[5]).toString(),  //Description
                 query.value(index[6]).toString(),  //Filepath
                 QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                 QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
             );
             break;
         case audio:
             n = new Audio(
                 id,  //ID
                 query.value(index[1]).toInt(),     //Version
                 query.value(index[2]).toString(),  //Titre

                 query.value(index[5]).toString(),  //Description
                 query.value(index[6]).toString(),  //Filepath
                 QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                 QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
             );
             break;
         case video:
             n = new Video(
                 id,  //ID
                 query.value(index[1]).toInt(),     //Version
                 query.value(index[2]).toString(),  //Titre

                 query.value(index[5]).toString(),  //Description
                 query.value(index[6]).toString(),  //Filepath
                 QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                 QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
             );
             break;
         }

         cout<<"Chargement de "<<id.toStdString()<<" v"<<query.value(index[1]).toInt()<<endl;
         v->addNote(n);
     }
     if (sizeCount != 0) addNote(v);
}
