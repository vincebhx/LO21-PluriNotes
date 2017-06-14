#include "modifierrelation.h"
#include "ui_modifierrelation.h"
#include "../src/relation/relationsmanager.h"

ModifierRelation::ModifierRelation(QWidget *parent) : Widget(),
    QDialog(parent),
    ui(new Ui::ModifierRelation), nm(NotesManager::instance()), RM(RelationsManager::instance())
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    QStringList headerTable;
    headerTable << "ID Note 1" << "ID Note 2";
    ui->tableWidget->setHorizontalHeaderLabels(headerTable);
    loadRelations();
}

void ModifierRelation::loadRelations() {

    for(RMIterator it = RM.begin(); it!= RM.end(); it++){
        ui->comboBox->addItem((*it)->getTitre());
    }
}

void ModifierRelation::loadTable() {
    Relation* relation = RM.findRelation(ui->comboBox->currentText());
    ui->tableWidget->setRowCount(RM.numberOfRelations());
    for(RelationIterator it = relation->begin(); it != relation->end(); it++){
        for (unsigned int i =0; i< ui->tableWidget->rowCount(); i++) {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem((*it)->getNote1()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem((*it)->getNote2()));
        }
    }
}

ModifierRelation::~ModifierRelation()
{
    delete ui;
}

void ModifierRelation::on_comboBox_currentIndexChanged(int index)
{
    ui->tableWidget->clear();
    loadTable();
}

void ModifierRelation::receiveMessageMRelation() {
    for(NMIterator it = nm.begin(ACTIVES); it!= nm.end(ACTIVES); it++){
         ui->Note1->addItem((*it)->currentVersion()->getId());
         ui->Note2->addItem((*it)->currentVersion()->getId());
    }
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

}
