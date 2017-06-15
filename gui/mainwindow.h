#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include <QTreeWidget>
#include "mediator.h"
#include "src/note/notesmanager.h"
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Widget
{
    Q_OBJECT

public:
    /*!
     * \brief MainWindow : Le constructeur initialise les nombres de colonnes et les en-têtes dans chaque tableWidget
      et effectue le chargement des différents tableaux
     * \param parent = 0
     */
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    /*!
     * \brief getCode : fonction héritée de la classe Widget, code utilisé lors de la distribution
     * des messages par le mediator
     * \return un code au format String
     */
    QString getCode() {return "mainwindow";}

    /*!
     * \brief receiveMessage : contient les instructions à effectuer lorsqu'un message est envoyé
     * par la fenêtre de création de note
     */
    void receiveMessage();

    /*!
     * \brief receiveMessageCorbeille : contient les instructions à effectuer lorsqu'un message est envoyé
     * par la corbeille
     */
    void receiveMessageCorbeille();

    /*!
     * \brief receiveMessageMRelation : : contient les instructions à effectuer lorsqu'un message est envoyé
     * par la fenetre de modification d'une relation
     */
    void receiveMessageMRelation();
private :
    /*!
     * \brief loadTableWidgetActives : charge à partir du NotesManager toutes les notes actives
     * dans le premier tableWidget
     */
    void loadTableWidgetActives();

    /*!
     * \brief loadTableWidgetArchive :charge à partir du NotesManager toutes les notes archivées
     * dans le quatrième tableWidget
     */
    void loadTableWidgetArchive();

    /*!
     * \brief loadTableTache : charge à partir du NotesManager toutes les tâches dans
     * dans le troisième tableWidget
     */
    void loadTableTache();

    /*!
     * \brief saveNewVersionTache : enregistre une nouvelle version de la tache affichée
     * en récupérant les informations de chaque champ
     */
    void saveNewVersionTache();

    /*!
     * \brief saveNewVersionImage : enregistre une nouvelle version de la note image affichée
     * en récupérant les informations de chaque champ
     */
    void saveNewVersionImage();

    /*!
     * \brief saveNewVersionVideo : enregistre une nouvelle version de la note video affichée
     * en récupérant les informations de chaque champ
     */
    void saveNewVersionVideo();

    /*!
     * \brief saveNewVersionAudio : enregistre une nouvelle version de la note audio affichée
     * en récupérant les informations de chaque champ
     */
    void saveNewVersionAudio();

    /*!
     * \brief saveNewVersionArticle : enregistre une nouvelle version de l'article affiché
     * en récupérant les informations de chaque champ
     */
    void saveNewVersionArticle();

    /*!
     * \brief loadClicked : affiche à l'écran la note qui a été passée en paramètre (note selectionnée par l'utilisateur)
     * \param clicked : Note selectionnée
     * \param type : renseigne sur le type de la note (Article, Tâche, Audio, Vidéo, Image)
     */
    void loadClicked(Note* clicked, QString type);

    /*!
     * \brief loadVersion : charge dans le 2eme tableWidget les différentes version d'une note selectionnée
     * \param vClicked : correspond à la VersionIndex à charger
     */
    void loadVersion(VersionIndex *vClicked);

    /*!
     * \brief loadNote : charge la note passée en paramètre à l'écran
     * \param note : correspond à la note à charger
     * \param type : renseigne sur le type de la note (Article, Tâche, Audio, Vidéo, Image)
     */
    void loadNote(Note* note, QString type);

    /*!
     * \brief loadRelation : charge l'arborescence des relations à droite de l'écran
     * \param n : correspond à la note dont on doit charger les relations
     */
    void loadRelation(Note *n);


private slots:
    /*!
     * \brief on_pushButton_clicked : envoie le message permettant l'ouveture de la fenêtre de création
     * de nouvelle note
     */
    void on_pushButton_clicked();
    /*!
     * \brief onClose : libèration des Managers et fin du programme
     */
    void onClose();
    /*!
     * \brief on_tableWidget_doubleClicked : charge la version la plus récente de la note sélectionnée ainsi que ses différentes versions et relations
     * \param index
     */
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    /*!
     * \brief on_tableWidget_2_doubleClicked : charge la version sélectionnée d'une note actuellement à l'écran
     * \param index
     */
    void on_tableWidget_2_doubleClicked(const QModelIndex &index);
    /*!
     * \brief on_enregistrer_clicked : fait appel à la fonction de sauvegarde de nouvelle version en fonction du type
     */
    void on_enregistrer_clicked();

    /*!
     * \brief on_tableWidget_3_doubleClicked : charge la version la plus récente de la tâche sélectionnée dans le troisième tableWidget
     * \param index
     */
    void on_tableWidget_3_doubleClicked(const QModelIndex &index);
    /*!
     * \brief changeStateButton : permet de changer l'état de la note sélectionnée en l'état passé en paramètre
     * \param etat : etat cible
     */
    void changeStateButton(Etat etat);
    /*!
     * \brief on_archiver_clicked : change l'état de la note courrante en ARCHIVES
     */
    void on_archiver_clicked();
    /*!
     * \brief on_supprimer_clicked : change l'état de la note courrante en CORBEILLE
     */
    void on_supprimer_clicked();
    /*!
     * \brief on_ajouterR_clicked : envoie le message "Ajout Relation" au mediator
     */
    void on_ajouterR_clicked();
    /*!
     * \brief on_pushButton_6_clicked : envoie le message "Corbeille" au mediator
     */
    void on_pushButton_6_clicked();
    /*!
     * \brief on_modifierR_clicked : envoie le message "Modifier Relation" au mediator
     */
    void on_modifierR_clicked();
    /*!
     * \brief on_treeWidget_doubleClicked : charge la note sélectionnée dans l'arborescence
     * \param index
     */
    void on_treeWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    NotesManager& nm;
};



#endif // MAINWINDOW_H
