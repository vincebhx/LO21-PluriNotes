#include "ajouterrelation.h"
#include "ui_ajouterrelation.h"

AjouterRelation::AjouterRelation(QWidget *parent) : Widget(),
    QDialog(parent),
    ui(new Ui::AjouterRelation),nm(NotesManager::instance())
{
    ui->setupUi(this);
    for(NMIterator it = nm.begin(ACTIVES); it!= nm.end(ACTIVES); it++){
         ui->Note1->addItem((*it)->currentVersion()->getId());
         ui->Note2->addItem((*it)->currentVersion()->getId());
    }

}

AjouterRelation::~AjouterRelation()
{
    delete ui;
}
