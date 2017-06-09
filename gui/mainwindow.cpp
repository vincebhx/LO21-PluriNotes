#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NoteSelector.h"
#include "../src/dbmanager.h"
#include "../src/note/notesmanager.h"
#include "../src/note/note.h"
#include "../src/note/article.h"
#include "../src/note/tache.h"
#include "../src/note/media.h"
#include "dialog.h"
#include "../src/note/versionindex.h"
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

    ui->comboBox->addItem("En attente");
    ui->comboBox->addItem("En cours");
    ui->comboBox->addItem("Terminé");
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
    VersionIndex* vClicked = nm.getNote(indice);
    Note* clicked = nm.getNote(indice)->currentVersion();
    QString type = clicked->getClassName();
    loadClicked(clicked, type);
    loadVersion(vClicked);

}

void MainWindow::loadClicked(Note* clicked, QString type) {
    Article* article;
    Tache* tache;
    Image* image;
    Video* video;
    Audio* audio;
    if (type == "article") {
        article = dynamic_cast<Article*>(clicked);
        ui->a_titre->setText(clicked->getTitre());
        ui->a_creation->setText(clicked->getDateCreat().toString());
        ui->a_modif->setText(clicked->getDateLastModif().toString());
        ui->a_text->setText(article->getTexte());
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(type == "tache"){
        tache = dynamic_cast<Tache*>(clicked);
        ui->t_titre->setText(clicked->getTitre());
        ui->t_creation->setText(clicked->getDateCreat().toString());
        ui->t_modif->setText(clicked->getDateLastModif().toString());
        ui->dateTimeEdit->setDateTime(tache->getDateCreat());
        ui->dateTimeEdit_2->setDateTime(tache->getDateEcheance());
        ui->comboBox->setCurrentIndex(tache->getStatut());
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (type == "image") {
        image = dynamic_cast<Image*>(clicked);
        ui->i_titre->setText(clicked->getTitre());
        ui->i_creation->setText(clicked->getDateCreat().toString());
        ui->i_modif->setText(clicked->getDateLastModif().toString());
        ui->i_desc->setText(image->getDescription());
        ui->i_path->setText(image->getFilePath());
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if (type == "audio"){
        audio = dynamic_cast<Audio*>(clicked);
        ui->au_titre->setText(clicked->getTitre());
        ui->au_creat->setText(clicked->getDateCreat().toString());
        ui->au_modif->setText(clicked->getDateLastModif().toString());
        ui->au_desc->setText(audio->getDescription());
        ui->au_path->setText(audio->getFilePath());
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if (type == "video"){
        video = dynamic_cast<Video*>(clicked);
        ui->v_titre->setText(clicked->getTitre());
        ui->v_creation->setText(clicked->getDateCreat().toString());
        ui->v_modif->setText(clicked->getDateLastModif().toString());
        ui->v_desc->setText(video->getDescription());
        ui->v_path->setText(video->getFilePath());
        ui->stackedWidget->setCurrentIndex(4);
    }

}

void MainWindow::loadVersion(VersionIndex* vClicked) {
    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_2->setRowCount(vClicked->nbOfVersions());
    for (unsigned int i=0; i < vClicked->nbOfVersions(); i++) {
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(vClicked->at(i)->getDateCreat().toString()));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(vClicked->at(i)->getDateLastModif().toString()));
    }
}

void MainWindow::on_tableWidget_2_doubleClicked(const QModelIndex &index)
{
    NotesManager& nm = NotesManager::instance();
    int indice = index.row();
    int indiceN = ui->tableWidget->currentRow();
    Note* clicked = nm.getNote(indiceN)->at(indice);
    QString type = clicked->getClassName();
    loadClicked(clicked, type);
    }
