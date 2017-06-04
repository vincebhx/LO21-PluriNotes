#include "NoteViewer.h"
#include "../src/Version.h"
#include "../src/NotesManager.h"

NoteViewer::NoteViewer(NotesManager& nm) {
   QVBoxLayout* layout = new QVBoxLayout;

   nm.currentNote()->getId().toStdString();

   layout->addWidget(nm.currentNote()->getNoteView());
   cout<<"Layout++"<<endl;

   setLayout(layout);
}

