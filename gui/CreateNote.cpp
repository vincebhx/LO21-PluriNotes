#include "CreateNote.h"
#include "ui_createnote.h"
#include <iostream>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
CreateNote::CreateNote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNote)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Article");
    ui->comboBox->addItem("Tache");
    ui->comboBox->addItem("Image");
    ui->comboBox->addItem("Audio");
    ui->comboBox->addItem("Video");


}


CreateNote::~CreateNote()
{
    delete ui;
}



void CreateNote::on_pushButton_clicked()
{
    QTextEdit* edit = new QTextEdit;

    QLabel* debut = new QLabel;
    QLabel* echeance = new QLabel;
    QDateEdit* deb = new QDateEdit;
    QDateEdit* fin = new QDateEdit;

    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    QVBoxLayout* layout = new QVBoxLayout;

    switch(ui->comboBox->currentIndex()) {
    case 0 :
        std::cout << "article";
        ui->verticalLayout->addWidget(edit);
        break;
    case 1 :
        layout1->addWidget(debut);
        layout1->addWidget(echeance);
        layout2->addWidget(deb);
        layout2->addWidget(fin);
        ui->verticalLayout->addLayout(layout1);
        ui->verticalLayout->addLayout(layout2);
        break;
    case 2 :
        break;
    case 3 :
        break;
    case 4 :
        break;

    }
}
