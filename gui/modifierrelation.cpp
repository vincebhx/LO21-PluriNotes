#include "modifierrelation.h"
#include "ui_modifierrelation.h"
#include "../src/relation/relationsmanager.h"
#include <iostream>

ModifierRelation::ModifierRelation(QWidget *parent) : Widget(),
    QDialog(parent),
    ui(new Ui::ModifierRelation), nm(NotesManager::instance()), RM(RelationsManager::instance())
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    QStringList headerTable;
    headerTable << "ID Note 1" << "ID Note 2" << "Label Couple";
    ui->tableWidget->setHorizontalHeaderLabels(headerTable);
    loadRelations();
}

void ModifierRelation::loadRelations() {
    for(RMIterator it = RM.begin(); it!= RM.end(); it++){
        ui->comboBox->addItem((*it)->getTitre());
    }
}

void ModifierRelation::loadTable() {
    ui->tableWidget->clear();
    Relation* relation = RM.findRelation(ui->comboBox->currentText());
    ui->tableWidget->setRowCount(relation->getNbCouples());
    for(RelationIterator it = relation->begin(); it != relation->end(); it++){
        for (unsigned int i =0; i< ui->tableWidget->rowCount(); i++) {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem((*it)->getNote1()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem((*it)->getNote2()));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem((*it)->getLabel()));
        }
    }
}

ModifierRelation::~ModifierRelation()
{
    delete ui;
}

void ModifierRelation::on_comboBox_currentIndexChanged(int index)
{
   loadTable();
}

void ModifierRelation::receiveMessageMRelation() {
    //ui->comboBox->clear();
    for(NMIterator it = nm.begin(ACTIVES); it!= nm.end(ACTIVES); it++){
         ui->Note1->addItem((*it)->currentVersion()->getId());
         ui->Note2->addItem((*it)->currentVersion()->getId());
    }
    loadRelations();
    this->show();
}

void ModifierRelation::on_buttonBox_clicked(QAbstractButton *button)
{
    sendMessage("Modifier Relation");
}

void ModifierRelation::on_pushButton_2_clicked()
{
    Relation* relation = RM.findRelation(ui->comboBox->currentText());
    RM.supprimerRelation(relation);
    loadTable();
}

void ModifierRelation::on_pushButton_3_clicked()
{
    Relation* relation = RM.findRelation(ui->comboBox->currentText());
    Note* n1 =nm.findNote(ui->Note1->currentText());
    Note* n2 =nm.findNote(ui->Note2->currentText());
    QString label = ui->lineEdit_2->text();
    Couple* couple = new Couple(n1->getId(), n2->getId(), label);
    relation->addCouple(couple);
    loadTable();


}

void ModifierRelation::on_pushButton_clicked()
{
    QString id1 = ui->tableWidget->itemAt(ui->tableWidget->currentRow(), 0)->text();
    QString id2 = ui->tableWidget->itemAt(ui->tableWidget->currentRow(), 1)->text();
    Relation* relation = RM.findRelation(ui->comboBox->currentText());
    Couple* c =relation->findCouple(id1, id2);
    //supprimer couple

}
