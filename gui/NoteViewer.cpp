#include "NoteViewer.h"
#include "../src/Version.h"
#include "../src/NotesManager.h"

NoteViewer::NoteViewer(NotesManager& nm) {
   QLayout* layout = new QVBoxLayout();

   layout->addWidget(nm.currentNote()->getNoteView());
   cout<<"NoteViewer : Ajout du layout"<<endl;

   this->setLayout(layout);
}

