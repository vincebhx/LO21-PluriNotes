#include "mainwindow.h"
#include "../src/dbmanager.h"
#include "../src/note/notesmanager.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onClose() {
    NotesManager::instance().free();
    DbManager::instance().free();
    std::cout<<"Fin de l'exécution."<<std::endl;
}
