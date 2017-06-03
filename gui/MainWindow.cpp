#include "MainWindow.h"
#include "../src/NotesManager.h"
#include "NoteViewer.h"
#include <QDockWidget>
#include "../src/Note.h"
#include "NoteSelector.h"
#include <QTableView>
#include <QHBoxLayout>

MainWindow::MainWindow()
{
    NotesManager& nm = NotesManager::instance();
    NoteSelector* noteselec = new NoteSelector(nm);
    QTableView* view = new QTableView;
    QHBoxLayout* layoutH = new QHBoxLayout;

    view->setModel(noteselec);

    //view->show();


    NoteViewer* nv = new NoteViewer;
    //setCentralWidget(nv);

    layoutH->addWidget(view);
    layoutH->addWidget(nv);


}

void MainWindow::onClose() {
    cout<<"Fin de l'exécution !\n";
}
