#include "ajouterrelation.h"
#include "ui_ajouterrelation.h"

AjouterRelation::AjouterRelation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterRelation)
{
    ui->setupUi(this);
}

AjouterRelation::~AjouterRelation()
{
    delete ui;
}
