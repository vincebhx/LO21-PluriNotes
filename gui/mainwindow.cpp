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
    Note* clicked = nm.getNote(indice)->currentVersion();
    QString type = clicked->getClassName();
    int id_type; // 0: article; 1: tache; 2: image; 3: audio; 4:video
    Article* article;
    Tache* tache;
    Image* image;
    Video* video;
    Audio* audio;

    if (type == "article") {
        id_type = 0;
        article = dynamic_cast<Article*>(clicked);
    }
    else if(type == "tache"){
        id_type = 1;
        tache = dynamic_cast<Tache*>(clicked);
    }
    else if (type == "image") {
        id_type =2;
        image = dynamic_cast<Image*>(clicked);
    }
    else if (type == "audio"){
        id_type = 3;
        audio = dynamic_cast<Audio*>(clicked);
    }
    else if (type == "video"){
        id_type = 4;
        video = dynamic_cast<Video*>(clicked);
    }

    ui->stackedWidget->setCurrentIndex(id_type);
    switch (id_type) {
    case 0:
        ui->a_titre->setText(clicked->getTitre());
        ui->a_creation->setText(clicked->getDateCreat().toString());
        ui->a_modif->setText(clicked->getDateLastModif().toString());
        ui->a_text->setText(article->getTexte());
        break;
    case 1 :
        ui->t_titre->setText(clicked->getTitre());
        ui->t_creation->setText(clicked->getDateCreat().toString());
        ui->t_modif->setText(clicked->getDateLastModif().toString());
        ui->dateTimeEdit->setDateTime(tache->getDateCreat());
        ui->dateTimeEdit_2->setDateTime(tache->getDateEcheance());
        ui->comboBox->setCurrentIndex(tache->getStatut());
        break;

    case 2:
        ui->i_titre->setText(clicked->getTitre());
        ui->i_creation->setText(clicked->getDateCreat().toString());
        ui->i_modif->setText(clicked->getDateLastModif().toString());
        ui->i_desc->setText(image->getDescription());
        ui->i_path->setText(image->getFilePath());
        break;

    case 3:
        ui->au_titre->setText(clicked->getTitre());
        ui->au_creat->setText(clicked->getDateCreat().toString());
        ui->au_modif->setText(clicked->getDateLastModif().toString());
        ui->au_desc->setText(audio->getDescription());
        ui->au_path->setText(audio->getFilePath());
        break;
    case 4:
        ui->v_titre->setText(clicked->getTitre());
        ui->v_creation->setText(clicked->getDateCreat().toString());
        ui->v_modif->setText(clicked->getDateLastModif().toString());
        ui->v_desc->setText(video->getDescription());
        ui->v_path->setText(video->getFilePath());
        break;

    default :
        break;
    }
}


