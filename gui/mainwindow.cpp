#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NoteSelector.h"
#include "../src/note/versionindex.h"
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
    ui(new Ui::MainWindow), nm(NotesManager::instance())
{
    ui->setupUi(this);
    //setCentralWidget(ui->stackedWidget);
    //NoteTableModel* model = new NoteTableModel;

    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget->setColumnCount(4);
    ui->archive->setColumnCount(4);
    ui->tableWidget_3->setColumnCount(4);


    ui->comboBox->addItem("En attente");
    ui->comboBox->addItem("En cours");
    ui->comboBox->addItem("Terminé");

    loadTableWidget1();
    loadTableTache();
    loadTableWidget3();

}

void MainWindow::loadTableWidget1() {

    std::vector<QTableWidgetItem*> id;
    std::vector<QTableWidgetItem*> titre;
    std::vector<QTableWidgetItem*> dateC;
    std::vector<QTableWidgetItem*> dateM;


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

void MainWindow::loadTableTache() {
    std::vector<QTableWidgetItem*> id;
    std::vector<QTableWidgetItem*> titre;
    std::vector<QTableWidgetItem*> dateC;
    std::vector<QTableWidgetItem*> dateM;
    std::vector<VersionIndex*> list = nm.getTasks();
    ui->tableWidget_3->setRowCount(list.size());
    for (unsigned int i = 0; i < list.size(); i++) {
        id.push_back(new QTableWidgetItem(list[i]->currentVersion()->getId()));
        titre.push_back((new QTableWidgetItem(list[i]->currentVersion()->getTitre())));
        dateC.push_back(new QTableWidgetItem(list[i]->currentVersion()->getDateCreat().toString()));
        dateM.push_back(new QTableWidgetItem(list[i]->currentVersion()->getDateLastModif().toString()));
    }

    for (unsigned int i=0; i < ui->tableWidget_3->rowCount(); i++) {
        ui->tableWidget_3->setItem(i, 0, id[i]);
        ui->tableWidget_3->setItem(i, 1, titre[i]);
        ui->tableWidget_3->setItem(i, 2, dateC[i]);
        ui->tableWidget_3->setItem(i, 3, dateM[i]);
    }

}

void MainWindow::loadTableWidget3() {

    std::vector<QTableWidgetItem*> id;
    std::vector<QTableWidgetItem*> titre;
    std::vector<QTableWidgetItem*> dateC;
    std::vector<QTableWidgetItem*> dateM;


    ui->archive->setRowCount(NotesManager::instance().nbNotes(ARCHIVES));
    for(NMIterator it = nm.begin(ARCHIVES); it!= nm.end(ARCHIVES); it++){
        id.push_back(new QTableWidgetItem((*it)->currentVersion()->getId()));
        titre.push_back((new QTableWidgetItem((*it)->currentVersion()->getTitre())));
        dateC.push_back(new QTableWidgetItem((*it)->currentVersion()->getDateCreat().toString()));
        dateM.push_back(new QTableWidgetItem((*it)->currentVersion()->getDateLastModif().toString()));
    }

    for (unsigned int i=0; i < ui->archive->rowCount(); i++) {
        ui->archive->setItem(i, 0, id[i]);
        ui->archive->setItem(i, 1, titre[i]);
        ui->archive->setItem(i, 2, dateC[i]);
        ui->archive->setItem(i, 3, dateM[i]);
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


void MainWindow::onClose()
{
    NotesManager::instance().free();
    DbManager::instance().free();
    std::cout<<"Fin de l'exécution."<<std::endl;
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
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
        ui->t_action->setText(tache->getAction());
        ui->dateTimeEdit->setDateTime(tache->getDateCreat());
        ui->dateTimeEdit_2->setDateTime(tache->getDateEcheance());
        ui->comboBox->setCurrentIndex(tache->getStatut());
        ui->spinBox->setValue(tache->getPriorite());
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
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(vClicked->nbOfVersions());
    int j =0;
    for (int i= vClicked->nbOfVersions()-1; i > -1 ; i--) {
        ui->tableWidget_2->setItem(vClicked->nbOfVersions()-1-i, 0, new QTableWidgetItem(vClicked->at(i)->getDateCreat().toString()));
        ui->tableWidget_2->setItem(vClicked->nbOfVersions()-1-i, 1, new QTableWidgetItem(vClicked->at(i)->getDateLastModif().toString()));
        j++;
    }
}

void MainWindow::on_tableWidget_2_doubleClicked(const QModelIndex &index)
{
    int indice = ui->tableWidget_2->rowCount() - 1 - index.row();
    int indiceN = ui->tableWidget->currentRow();
    Note* clicked = nm.getNote(indiceN)->at(indice);
    QString type = clicked->getClassName();
    loadClicked(clicked, type);
    }

void MainWindow::saveNewVersionArticle() {
    Note* clicked = nm.getNote(ui->tableWidget->currentRow())->firstVersion();
    QString id = clicked->getId();
    QString titre = ui->a_titre->text();
    QString texte = ui->a_text->toPlainText();
    QDateTime modif = QDateTime::currentDateTime();
    QDateTime creat = QDateTime::currentDateTime();
    int version = ui->tableWidget_2->rowCount() + 1;


    Note* newV = new Article(id, version, titre, creat, modif, texte);
    nm.getNote(ui->tableWidget->currentRow())->addVersion(newV);
    DbManager::instance().saveNote(newV);
    loadVersion(nm.getNote(ui->tableWidget->currentRow()));

}

void MainWindow::saveNewVersionTache() {
    Note* clicked = nm.getNote(ui->tableWidget->currentRow())->firstVersion();
    QString id = clicked->getId();
    int version = ui->tableWidget_2->rowCount() + 1;
    QString titre = ui->t_titre->text();
    QDateTime echeance = ui->dateTimeEdit_2->dateTime();
    QString action = ui->t_action->text();
    int priorite = ui->spinBox->value();
    Statut statut = Statut(ui->comboBox->currentIndex());

    Note* newV = new Tache(id, version, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), action, priorite, echeance, statut);
    nm.getNote(ui->tableWidget->currentRow())->addVersion(newV);
    DbManager::instance().saveNote(newV);
    loadVersion(nm.getNote(ui->tableWidget->currentRow()));

}

void MainWindow::saveNewVersionImage() {
    Note* clicked = nm.getNote(ui->tableWidget->currentRow())->firstVersion();
    QString id = clicked->getId();
    int version = ui->tableWidget_2->rowCount() + 1;
    QString titre = ui->i_titre->text();
    QString desc = ui->i_desc->toPlainText();
    QString path = ui->i_path->text();

    Note* newV = new Image(id, version, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), desc, path);
    nm.getNote(ui->tableWidget->currentRow())->addVersion(newV);
    DbManager::instance().saveNote(newV);
    loadVersion(nm.getNote(ui->tableWidget->currentRow()));
}

void MainWindow::saveNewVersionVideo(){
    Note* clicked = nm.getNote(ui->tableWidget->currentRow())->firstVersion();
    QString id = clicked->getId();
    int version = ui->tableWidget_2->rowCount() + 1;
    QString titre = ui->v_titre->text();
    QString desc = ui->v_desc->toPlainText();
    QString path = ui->v_path->text();

    Note* newV = new Video(id, version, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), desc, path);
    nm.getNote(ui->tableWidget->currentRow())->addVersion(newV);
    DbManager::instance().saveNote(newV);
    loadVersion(nm.getNote(ui->tableWidget->currentRow()));
}

void MainWindow::saveNewVersionAudio() {
    Note* clicked = nm.getNote(ui->tableWidget->currentRow())->firstVersion();
    QString id = clicked->getId();
    int version = ui->tableWidget_2->rowCount() + 1;
    QString titre = ui->au_titre->text();
    QString desc = ui->au_desc->toPlainText();
    QString path = ui->au_path->text();

    Note* newV = new Audio(id, version, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), desc, path);
    nm.getNote(ui->tableWidget->currentRow())->addVersion(newV);
    DbManager::instance().saveNote(newV);
    loadVersion(nm.getNote(ui->tableWidget->currentRow()));
}

void MainWindow::on_enregistrer_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    switch (index) {
    case 0:
        saveNewVersionArticle();
        break;
    case 1:
        saveNewVersionTache();
        break;
    case 2:
        saveNewVersionImage();
        break;
    case 3:
        saveNewVersionAudio();
        break;
    case 4:
        saveNewVersionVideo();
        break;
    }
}


