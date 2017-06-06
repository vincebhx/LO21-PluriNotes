#include "NoteViewer.h"
#include "../src/Version.h"
#include "../src/NotesManager.h"

NoteViewer::NoteViewer() {
   NotesManager& nm = NotesManager::instance();
   QVBoxLayout* layout = new QVBoxLayout;

   for(NMIterator it = nm.begin(); it != nm.end(); it++) {
       layout->addWidget((*it)->currentNote()->getNoteView());
       cout<<"toto"<<endl;
   }

   setLayout(layout);
}

