#include "NoteViewer.h"
#include "../src/Version.h"

NoteViewer::NoteViewer() {
   Article n("testarticle", "Ceci est un test.", "Bienvenue dans ce test. Ca marche bien, n'est-ce pas ? ");
   Tache n2("testtache", "Ceci est un test de tâche.", "Coder le projet d'LO21", 42, Date(13, 6, 2017, 23, 59, 59), enCours);
   //Image n("testimage", "Image 1", "Un poisson avec un sombrero.", "/home/vbaheux/poisson.png");

   Version v;
   v.addNote(&n);
   v.addNote(&n2);
   v.parcourir();
   std::cout<<v.getNoteByVersion(0)->getId().toStdString()<<std::endl;

   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(n.getNoteView());
   setLayout(layout);
}
