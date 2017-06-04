#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "../src/NotesManager.h"
#include "NoteViewer.h"
#include <QDockWidget>
#include "NoteSelector.h"

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
}

void MainWindow::onClose() {
    DbManager::instance().free();
    NotesManager::instance().free();
    cout<<"Fin de l'exécution."<<endl;
}
