#include "MainWindow.h"
<<<<<<< HEAD
#include "ui_mainwindow.h"
#include "../src/NotesManager.h"
=======
>>>>>>> 5eb5a1e91a14df14f24c07ac42ff73d80cd00401
#include "NoteViewer.h"
#include <QDockWidget>
#include "NoteSelector.h"

<<<<<<< HEAD
//toto

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    NotesManager& nm = NotesManager::instance();

    NoteSelector* noteselec = new NoteSelector(nm);

    ui->tableView->setModel(noteselec);
}

MainWindow::~MainWindow()
{
    delete ui;
=======
using namespace std;

MainWindow::MainWindow(NotesManager& nm)
{
    NoteViewer* nv = new NoteViewer(nm);
    setCentralWidget(nv);
    cout<<"MainWindow : c'est tout bon !"<<endl;
>>>>>>> 5eb5a1e91a14df14f24c07ac42ff73d80cd00401
}

void MainWindow::onClose() {
    DbManager::instance().free();
    NotesManager::instance().free();
    cout<<"Fin de l'exécution."<<endl;
}
