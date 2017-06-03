#include "NoteViewer.h"
#include "../src/Version.h"
#include "../src/NotesManager.h"

NoteViewer::NoteViewer() {
   NotesManager& nm = NotesManager::instance();
   QVBoxLayout* layout = new QVBoxLayout;

   for(NMIterator it = nm.begin(); it != nm.end(); it++) {
       cout << (*it)->currentNote()->getId().toStdString();
   }

   layout->addWidget(nm.currentNote()->getNoteView());
   cout<<"Layout++"<<endl;

   setLayout(layout);
}

