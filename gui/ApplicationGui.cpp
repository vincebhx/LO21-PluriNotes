#include "ApplicationGui.h"

#include "NoteViewer.h"
#include <QDockWidget>

ApplicationGui::ApplicationGui()
{
    NoteViewer* noteViewer = new NoteViewer;
    setCentralWidget(noteViewer);

    QDockWidget* leftDock = new QDockWidget;
}
