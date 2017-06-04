#include "MainWindow.h"
#include "NoteViewer.h"
#include <QDockWidget>
#include "NoteSelector.h"
#include <QTableView>
#include <QHBoxLayout>

MainWindow::MainWindow(NotesManager& nm)
{
    /*
    NoteSelector* noteselec = new NoteSelector(nm);
    NoteViewer* nv = new NoteViewer(nm);

    setCentralWidget(nv);
    */
}

void MainWindow::onClose() {
    DbManager::instance().free();
    NotesManager::instance().free();
    cout<<"Fin de l'exécution."<<endl;
}
