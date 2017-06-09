#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->comboBox->addItem("En attente");
    ui->comboBox->addItem("En cours");
    ui->comboBox->addItem("Terminé");

    ui->a_titre->setText("Sans Titre");
    ui->a_text->setText("Votre texte.");

    ui->t_titre->setText("Sans Titre");
    ui->t_action->setText("Votre texte.");
    ui->t_echance->setDateTime(QDateTime::currentDateTime());
    ui->comboBox->setCurrentIndex(0);

    ui->i_titre->setText("Sans Titre");
    ui->i_path->setText("");
    ui->i_desc->setPlainText("Votre texte.");

    ui->v_titre->setText("Sans Titre");
    ui->v_path->setText("");
    ui->v_desc  ->setPlainText("Votre texte.");

    ui->au_titre->setText("Sans Titre");
    ui->au_path->setText("");
    ui->au_desc->setPlainText("Votre texte.");


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_buttonBox_accepted()
{
    //
}
