#include "MainWindow.h"
#include "NoteViewer.h"
#include <QDockWidget>
#include "NoteSelector.h"
#include <QTableView>
#include <QHBoxLayout>

using namespace std;

MainWindow::MainWindow(NotesManager& nm)
{
    NoteViewer* nv = new NoteViewer(nm);
    setCentralWidget(nv);
    cout<<"MainWindow : c'est tout bon !"<<endl;
}

void MainWindow::onClose() {
    DbManager::instance().free();
    NotesManager::instance().free();
    cout<<"Fin de l'exécution."<<endl;
}
