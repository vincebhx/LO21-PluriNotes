#include "corbeille.h"
#include "ui_corbeille.h"
#include <iostream>

Corbeille::Corbeille(QWidget *parent) : Widget(),
    QMainWindow(parent),
    ui(new Ui::Corbeille), nm(NotesManager::instance())
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);

    QStringList headerTable1;
    headerTable1 << "ID" << "Titre" << "Date de creation" << "Date de modification";
    ui->tableWidget->setHorizontalHeaderLabels(headerTable1);
    loadTable();
}

Corbeille::~Corbeille()
{
    delete ui;
}

void Corbeille::loadTable() {
    std::vector<QTableWidgetItem*> id;
    std::vector<QTableWidgetItem*> titre;
    std::vector<QTableWidgetItem*> dateC;
    std::vector<QTableWidgetItem*> dateM;


    ui->tableWidget->setRowCount(NotesManager::instance().nbNotes(CORBEILLE));
    for(NMIterator it = nm.begin(CORBEILLE); it!= nm.end(CORBEILLE); it++){
            id.push_back(new QTableWidgetItem((*it)->currentVersion()->getId()));
            titre.push_back((new QTableWidgetItem((*it)->currentVersion()->getTitre())));
            dateC.push_back(new QTableWidgetItem((*it)->currentVersion()->getDateCreat().toString()));
            dateM.push_back(new QTableWidgetItem((*it)->currentVersion()->getDateModif().toString()));
    }

    for (unsigned int i=0; i < ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->setItem(i, 0, id[i]);
        ui->tableWidget->setItem(i, 1, titre[i]);
        ui->tableWidget->setItem(i, 2, dateC[i]);
        ui->tableWidget->setItem(i, 3, dateM[i]);
    }
}

void Corbeille::on_pushButton_4_clicked()
{
    sendMessage("Corbeille");
    this->close();
}

void Corbeille::restaurer() {
    if (nm.nbNotes(CORBEILLE) != 0 && ui->tableWidget->currentItem()) {
        QString id = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();
        VersionIndex* vClicked = nm.findVersionIndex(id);
        nm.changeState(ACTIVES, vClicked); //Changement d'état !
        loadTable();
    }
}



void Corbeille::on_pushButton_clicked()
{
    restaurer();
}

void Corbeille::receiveMessageCorbeille() {
    loadTable();
    this->show();
}

void Corbeille::supprimerNote() {
    if (ui->tableWidget->currentItem()) {
        QString id = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();
        VersionIndex* vClicked = nm.findVersionIndex(id);
        nm.deleteNote(vClicked);
    }
}

void Corbeille::on_pushButton_2_clicked()
{
     supprimerNote();
     loadTable();
}

void Corbeille::on_pushButton_3_clicked()
{
    for (int i=0; i< ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->setCurrentCell(i,0);
        supprimerNote();
    }
    loadTable();
}
