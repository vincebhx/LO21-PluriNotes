#include "dialog.h"
#include "ui_dialog.h"
#include "../src/note/note.h"
#include "../src/note/versionindex.h"
#include "../src/dbmanager.h"
#include "../src/note/notesmanager.h"
#include "../src/note/note.h"
#include "../src/note/article.h"
#include "../src/note/tache.h"
#include "../src/note/media.h"

Dialog::Dialog(QWidget *parent) : Widget(),
    QDialog(parent),
    ui(new Ui::Dialog), nm(NotesManager::instance())
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

void Dialog::createArticle() {
    Note* newN;
    QString titre = ui->a_titre->text();
    QString text = ui->a_text->toPlainText();
    newN = new Article(0, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), text);
    VersionIndex* v = new VersionIndex(newN);
    nm.addNote((Etat)0, v);

}

void Dialog::createTache() {
    Note* newN;
    QString titre = ui->t_titre->text();
    QString action = ui->t_action->text();
    int priorite = ui->spinBox->value();
    QDateTime echeance = ui->t_echance->dateTime();
    Statut statut = Statut(ui->comboBox->currentIndex());
    newN = new Tache(0, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), action, priorite, echeance, statut);
    VersionIndex* v = new VersionIndex(newN);
    nm.addNote((Etat)0, v);
}
void Dialog::createImage() {
    Note* newN;
    QString titre = ui->i_titre->text();
    QString desc = ui->i_desc->toPlainText();
    QString path = ui->i_path->text();
    newN = new Image(0, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), desc, path);
    VersionIndex* v = new VersionIndex(newN);
    nm.addNote((Etat)0, v);
}

void Dialog::createAudio() {
    Note* newN;
    QString titre = ui->au_titre->text();
    QString desc = ui->au_desc->toPlainText();
    QString path = ui->au_path->text();
    newN = new Audio(0, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), desc, path);
    VersionIndex* v = new VersionIndex(newN);
    nm.addNote((Etat)0, v);

}

void Dialog::createVideo(){
    Note* newN;
    QString titre = ui->v_titre->text();
    QString desc = ui->v_desc->toPlainText();
    QString path = ui->v_path->text();
    newN = new Video(0, titre, QDateTime::currentDateTime(), QDateTime::currentDateTime(), desc, path);
    VersionIndex* v = new VersionIndex(newN);
    nm.addNote((Etat)0, v);
}


void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    int index = ui->tabWidget->currentIndex();
    switch (index) {
    case 0:
        createArticle();
        break;
    case 1:
        createTache();
        break;
    case 2:
        createImage();
        break;
    case 3 :
        createAudio();
        break;
    case 4:
        createVideo();
        break;
    default :
        break;
    }

    sendMessage();

    }
