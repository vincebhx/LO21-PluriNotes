#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NoteSelector.h"
#include "../src/dbmanager.h"
#include "../src/note/notesmanager.h"
#include "../src/note/note.h"
#include "dialog.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->stackedWidget);
    //NoteTableModel* model = new NoteTableModel;
    NotesManager& nm = NotesManager::instance();

    std::vector<QTableWidgetItem*> id;
    std::vector<QTableWidgetItem*> titre;
    std::vector<QTableWidgetItem*> dateC;
    std::vector<QTableWidgetItem*> dateM;


    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(NotesManager::instance().nbNotes(ACTIVES));
    for(NMIterator it = nm.begin(ACTIVES); it!= nm.end(ACTIVES); it++){
        id.push_back(new QTableWidgetItem((*it)->currentVersion()->getId()));
        titre.push_back((new QTableWidgetItem((*it)->currentVersion()->getTitre())));
        dateC.push_back(new QTableWidgetItem((*it)->currentVersion()->getDateCreat().toString()));
        dateM.push_back(new QTableWidgetItem((*it)->currentVersion()->getDateLastModif().toString()));
    }

    for (unsigned int i=0; i < ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->setItem(i, 0, id[i]);
        ui->tableWidget->setItem(i, 1, titre[i]);
        ui->tableWidget->setItem(i, 2, dateC[i]);
        ui->tableWidget->setItem(i, 3, dateM[i]);
    }
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

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    NotesManager& nm = NotesManager::instance();
    int indice = index.row();
    Note* clicked = nm.getNote(indice)->currentVersion();
    QString type = clicked->getClassName();
    int id_type; // 0: article; 1: tache; 2: image; 3: audio; 4:video
    if (type == "article")
        id_type = 0;
    else if(type == "tache")
        id_type = 1;
    else if (type == "image")
        id_type =2;
    else if (type == "audio")
        id_type = 3;
    else if (type == "video")
        id_type = 4;

    ui->stackedWidget->setCurrentIndex(id_type);
    if (id_type == 0) {
        ui->a_titre->setText(clicked->getTitre());
        ui->a_creation->setText(clicked->getDateCreat().toString());
        ui->a_modif->setText(clicked->getDateLastModif().toString());
        //ui->a_text->setText(clicked->getTexte());

    }
}


