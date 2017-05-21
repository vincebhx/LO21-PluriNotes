#include "ApplicationGui.h"

#include "NoteViewer.h"
#include <QDockWidget>
#include "../src/Note.h"

ApplicationGui::ApplicationGui()
{
    Article n("testarticle", "Ceci est un test.", "Bienvenue dans ce test. Ca marche bien, n'est-ce pas ? ");
    //Tache n("testtache", "Ceci est un test de tâche.", "Coder le projet d'LO21", 42, Date(13, 6, 2017, 23, 59, 59), enCours);
    //Image n("testimage", "Image 1", "Un poisson avec un sombrero.", "/home/vbaheux/poisson.png");
    setCentralWidget(n.getNoteView());

    //QDockWidget* leftDock = new QDockWidget;
}
