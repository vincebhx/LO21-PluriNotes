#include "NoteViewer.h"
#include "../src/Version.h"
#include "../src/NotesManager.h"

NoteViewer::NoteViewer() {
   NotesManager& nm = NotesManager::instance();
   nm.load();

   Article n("testarticle", "Ceci est un test.", "Bienvenue dans ce test. Ca marche bien, n'est-ce pas ? ");
   Tache n2("testtache", "Ceci est un test de tâche.", "Coder le projet d'LO21", 42, Date(13, 6, 2017, 23, 59, 59), enCours);
   //Image n("testimage", "Image 1", "Un poisson avec un sombrero.", "/home/vbaheux/poisson.png");

   Version v;
   v.addNote(&n);
   v.addNote(&n2);
   //nm->addNote(&v);

   for(VersionIterator it = v.begin(); it != v.end(); it++)
       std::cout<<(*it)->getId().toStdString()<<std::endl;
   std::cout<<v.getNoteByVersion(0)->getId().toStdString()<<std::endl;

   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(n.getNoteView());
   setLayout(layout);
}
