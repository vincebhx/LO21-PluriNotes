#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NoteSelector.h"
#include "../src/dbmanager.h"
#include "../src/note/notesmanager.h"
#include "dialog.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*NotesManager& nm = NotesManager::instance();

    NoteSelector* noteselec = new NoteSelector(nm);

    ui->tableView->setModel(noteselec);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Dialog* createnote = new Dialog;
    createnote->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onClose()
{
    NotesManager::instance().free();
    DbManager::instance().free();
    std::cout<<"Fin de l'exécution."<<std::endl;
}
