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
#include <QTreeWidget>
#include <iostream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : Widget(),
    QMainWindow(parent),
    ui(new Ui::MainWindow), nm(NotesManager::instance())
{
    ui->setupUi(this);
    //setCentralWidget(ui->stackedWidget);
    //NoteTableModel* model = new NoteTableModel;


    ui->tableWidget->setColumnCount(4); //notes actives
    ui->tableWidget_2->setColumnCount(1); //version
    ui->tableWidget_3->setColumnCount(5); //taches
    ui->archive->setColumnCount(4);



    ui->comboBox->addItem("En attente");
    ui->comboBox->addItem("En cours");
    ui->comboBox->addItem("Terminé");

    QStringList headerTable1;
    headerTable1 << "ID" << "Titre" << "Date de creation" << "Date de modification";
    QStringList headerTable2;
    headerTable2 << "Date de derniere modification";
    QStringList headerTable3;
    headerTable3 << "ID" << "Titre" << "Date Echeance" << "Action" << "Priorite";

    ui->tableWidget->setHorizontalHeaderLabels(headerTable1);
    ui->tableWidget_2->setHorizontalHeaderLabels(headerTable2);
    ui->tableWidget_3->setHorizontalHeaderLabels(headerTable3);
    ui->archive->setHorizontalHeaderLabels(headerTable1);

    ui->treeWidget->setColumnCount(1);

    loadTableWidgetActives();
    loadTableTache();
    loadTableWidgetArchive();

}

void MainWindow::loadTableWidgetActives() {

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
    std::vector<QTableWidgetItem*> dateE;
    std::vector<QTableWidgetItem*> action;
    std::vector<QTableWidgetItem*> priorite;
    std::vector<VersionIndex*> list = nm.getTasks();
    ui->tableWidget_3->setRowCount(list.size());
    for (unsigned int i = 0; i < list.size(); i++) {
        Tache* tache = dynamic_cast<Tache*>(list[i]->currentVersion());
        id.push_back(new QTableWidgetItem(tache->getId()));
        titre.push_back((new QTableWidgetItem(tache->getTitre())));
        dateE.push_back(new QTableWidgetItem(tache->getDateEcheance().toString()));
        action.push_back(new QTableWidgetItem(tache->getAction()));
        priorite.push_back(new QTableWidgetItem(QString::number(tache->getPriorite())));

    }

    for (unsigned int i=0; i < ui->tableWidget_3->rowCount(); i++) {
        ui->tableWidget_3->setItem(i, 0, id[i]);
        ui->tableWidget_3->setItem(i, 1, titre[i]);
        ui->tableWidget_3->setItem(i, 2, dateE[i]);
        ui->tableWidget_3->setItem(i, 3, action[i]);
        ui->tableWidget_3->setItem(i, 3, priorite[i]);
    }

}

void MainWindow::loadTableWidgetArchive() {

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
    //Dialog* createnote = new Dialog;
    //createnote->show();
    sendMessage();
}


void MainWindow::onClose()
{
    NotesManager::instance().free();
    DbManager::instance().free();
    std::cout<<"Fin de l'exécution."<<std::endl;
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    if (index.column() != 0) {
        ui->tableWidget->setCurrentCell(index.row(), 0);
    }
    QString id = ui->tableWidget->currentItem()->text();
    std::cout << "cell id : "<<id.toStdString() << "\n";
    VersionIndex* vClicked = nm.findVersionIndex(id);
    Note* clicked = vClicked->currentVersion();
    std::cout << "clicked : " <<clicked->getId().toStdString() << "\n";
    QString type = clicked->getClassName();
    std::cout << "clicked type : " <<type.toStdString() << "\n";
    //loadClicked(clicked, type);
    loadClicked(clicked, type);
    loadVersion(vClicked);
    std::vector<QString> relations = clicked->implicationRelation();
   /* QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);

    for (unsigned int i=0; i< relations.size(); i++){
        //item->setText(0, relations[i]);
        //ui->treeWidget->addTopLevelItem(item);
    }*/

}

void MainWindow::loadClicked(Note* clicked, QString type) {
   loadNote(clicked, type);

}

void MainWindow::loadNote(Note* note, QString type) {
    Article* article;
    Tache* tache;
    Image* image;
    Video* video;
    Audio* audio;
    if (type == "article") {
        article = dynamic_cast<Article*>(note);
        ui->a_titre->setText(note->getTitre());
        ui->a_creation->setText(note->getDateCreat().toString());
        ui->a_modif->setText(note->getDateLastModif().toString());
        ui->a_text->setText(article->getTexte());
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(type == "tache"){
        tache = dynamic_cast<Tache*>(note);
        ui->t_titre->setText(note->getTitre());
        ui->t_creation->setText(note->getDateCreat().toString());
        ui->t_modif->setText(note->getDateLastModif().toString());
        ui->t_action->setText(tache->getAction());
        ui->dateTimeEdit->setDateTime(tache->getDateCreat());
        ui->dateTimeEdit_2->setDateTime(tache->getDateEcheance());
        ui->comboBox->setCurrentIndex(tache->getStatut());
        ui->spinBox->setValue(tache->getPriorite());
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (type == "image") {
        image = dynamic_cast<Image*>(note);
        ui->i_titre->setText(note->getTitre());
        ui->i_creation->setText(note->getDateCreat().toString());
        ui->i_modif->setText(note->getDateLastModif().toString());
        ui->i_desc->setText(image->getDescription());
        ui->i_path->setText(image->getFilePath());
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if (type == "audio"){
        audio = dynamic_cast<Audio*>(note);
        ui->au_titre->setText(note->getTitre());
        ui->au_creat->setText(note->getDateCreat().toString());
        ui->au_modif->setText(note->getDateLastModif().toString());
        ui->au_desc->setText(audio->getDescription());
        ui->au_path->setText(audio->getFilePath());
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if (type == "video"){
        video = dynamic_cast<Video*>(note);
        ui->v_titre->setText(note->getTitre());
        ui->v_creation->setText(note->getDateCreat().toString());
        ui->v_modif->setText(note->getDateLastModif().toString());
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
        ui->tableWidget_2->setItem(vClicked->nbOfVersions()-1-i, 0, new QTableWidgetItem(vClicked->at(i)->getDateLastModif().toString()));
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
    QDateTime creat = clicked->getDateCreat();
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

    Note* newV = new Tache(id, version, titre, clicked->getDateCreat(), QDateTime::currentDateTime(), action, priorite, echeance, statut);
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

    Note* newV = new Image(id, version, titre, clicked->getDateCreat(), QDateTime::currentDateTime(), desc, path);
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

    Note* newV = new Video(id, version, titre, clicked->getDateCreat(), QDateTime::currentDateTime(), desc, path);
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

    Note* newV = new Audio(id, version, titre, clicked->getDateCreat(), QDateTime::currentDateTime(), desc, path);
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



void MainWindow::on_pushButton_5_clicked()
{
    loadTableWidgetActives();
}

void MainWindow::receiveMessage() {
    std::cout << "msg recu par mainwindow \n";
    loadTableWidgetActives();
    loadTableTache();
    Note* note= nm.getNote(nm.nbNotes((Etat)0) -1)->currentVersion();
    QString type = note->getClassName();
    loadNote(note, type);
    loadVersion(nm.getNote(nm.nbNotes((Etat)0) -1));
    ui->tableWidget->setCurrentCell(nm.nbNotes((Etat)0) -1, 0);

}

void MainWindow::on_tableWidget_3_doubleClicked(const QModelIndex &index)
{
    if (index.column() != 0) {
        ui->tableWidget_3->setCurrentCell(index.row(), 0);
    }
    QString id = ui->tableWidget_3->currentItem()->text();
    std::cout << "cell id : "<<id.toStdString() << "\n";
    VersionIndex* vClicked = nm.findVersionIndex(id);
    Note* clicked = vClicked->currentVersion();
    std::cout << "clicked : " <<clicked->getId().toStdString() << "\n";
    QString type = clicked->getClassName();
    std::cout << "clicked type : " <<type.toStdString() << "\n";
    //loadClicked(clicked, type);
    loadClicked(clicked, type);
    loadVersion(vClicked);
}

void MainWindow::addRoot(QString name, QString description, Note* n) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    std::vector<QString> relations = n->implicationRelation();
    for (unsigned int i=0; i< relations.size(); i++){
        item->setText(0, relations[i]);
        ui->treeWidget->addTopLevelItem(item);
    }
    /*item->setText(0, name);
    ui->treeWidget->addTopLevelItem(item);
    addChild(item, "one");
    addChild(item, "two");*/

}

void MainWindow::addChild (QTreeWidgetItem *parent,QString name, QString description) {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QTreeWidgetItem* item2 = new QTreeWidgetItem();
    item->setText(0, name);
    parent->addChild(item);
}




void MainWindow::loadRelationView(Note* n) {
    /* Récuperer list des relations ou la note est impliquée
     * un treewidgetItem par relation; setTopLevelItem
     * pour chaque relation :  sous-level ascendant et descendant
     * pour ascendant et descedant treewidgetitem avec la note en question */

    std::vector<QString> relationName = n->implicationRelation();
    /*QStringList relationList;
    for (unsigned int i=0; i<relationName.size(); i++) {
        relationList << relationName[i];
    }*/



}

void MainWindow::on_pushButton_2_clicked()
{

}
