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
    NoteViewer* nv = new NoteViewer;

    QDockWidget *dockWidget = new QDockWidget(tr("Dock Widget"), this);
    QTableView* view = new QTableView(dockWidget);

    QHBoxLayout* layoutH = new QHBoxLayout;

    view->setModel(noteselec);
    //view->show();

    setCentralWidget(nv);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    //dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //dockWidget->setWidget(noteselec);

    /*
    layoutH->addWidget(view);
    layoutH->addWidget(nv);
    noteselec->setLayout(layoutH);
    */

}

void MainWindow::onClose() {
    cout<<"Fin de l'exécution !\n";
}
