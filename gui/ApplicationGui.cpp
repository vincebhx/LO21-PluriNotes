#include "ApplicationGui.h"

#include "NoteViewer.h"
#include <QDockWidget>
#include "../src/Note.h"

ApplicationGui::ApplicationGui()
{
    Article a("test", "Ceci est un test.", "Bienvenue dans ce test. Ca marche bien, n'est-ce pas ?");
    setCentralWidget(a.getNoteView());
    Tache t("test2", "Ceci est un test de tâche.", "Coder le projet d'LO21", 42, Date(20, 5, 2017, 23, 59, 59), enAttente);
    setCentralWidget(t.getNoteView());

    //QDockWidget* leftDock = new QDockWidget;
}
