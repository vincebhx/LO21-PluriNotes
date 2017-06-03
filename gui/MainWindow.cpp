#include "MainWindow.h"
#include "../src/NotesManager.h"
#include "NoteViewer.h"
#include <QDockWidget>
#include "../src/Note.h"
#include "NoteSelector.h"
#include <QTableView>

MainWindow::MainWindow()
{
    NotesManager& nm = NotesManager::instance();
    NoteSelector* noteselec = new NoteSelector(nm);
    QTableView* view = new QTableView;

    view->setModel(noteselec);

    view->show();


    NoteViewer* nv = new NoteViewer;
    setCentralWidget(nv);

}

void MainWindow::onClose() {
    cout<<"Fin de l'exécution !\n";
}
