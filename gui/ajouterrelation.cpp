#include "ajouterrelation.h"
#include "ui_ajouterrelation.h"

AjouterRelation::AjouterRelation(QWidget *parent) : Widget(),
    QDialog(parent),
    ui(new Ui::AjouterRelation),nm(NotesManager::instance())
{
    ui->setupUi(this);
}

AjouterRelation::~AjouterRelation()
{
    delete ui;
}

void AjouterRelation::receiveMessageARelation() {
    for(NMIterator it = nm.begin(ACTIVES); it!= nm.end(ACTIVES); it++){
         ui->Note1->addItem((*it)->currentVersion()->getId());
         ui->Note2->addItem((*it)->currentVersion()->getId());
    }
    this->show();
}

void AjouterRelation::on_pushButton_clicked()
{
    QString titre = ui->nomRelation->text();
    QString cLabel = ui->lineEdit->text();
    Note* n1 = nm.findNote(ui->Note1->currentText());
    Note* n2 = nm.findNote(ui->Note2->currentText());
    bool oriented = false;
    if (ui->checkBox->isChecked())
        oriented = true;
    Couple* couple = new Couple(n1->getId(), n2->getId());
    Relation* relation = new Relation(titre, "", oriented);
    RelationsManager::instance().addRelation(relation);
    relation->addCouple(couple);

}
