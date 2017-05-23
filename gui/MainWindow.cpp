#include "ApplicationGui.h"

#include "NoteViewer.h"
#include <QDockWidget>
#include "../src/Note.h"

ApplicationGui::ApplicationGui()
{

    NoteViewer* nv = new NoteViewer;
    setCentralWidget(nv);

    //QDockWidget* leftDock = new QDockWidget;
}
