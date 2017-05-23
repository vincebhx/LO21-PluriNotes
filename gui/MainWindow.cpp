#include "MainWindow.h"

#include "NoteViewer.h"
#include <QDockWidget>
#include "../src/Note.h"

MainWindow::MainWindow()
{

    NoteViewer* nv = new NoteViewer;
    setCentralWidget(nv);

    //QDockWidget* leftDock = new QDockWidget;
}

void MainWindow::onClose() {
    cout<<"Fin de l'exécution !\n";
}
