#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "../src/note/notesmanager.h"
#include "mediator.h"
#include <iostream>


namespace Ui {
class Dialog;
}
/*!
 * \brief The Dialog class : correspond à la fenêtre permettant de créer une note
 */
class Dialog : public QDialog, public Widget
{
    Q_OBJECT

public:
    /*!
     * \brief Dialog : le constructeur initialise les champs par défaut
     * \param parent
     */
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    /*!
     * \brief receiveMessage : contient les instructions à suivre lorsque le message "Ajout Note" est reçu
     */
    void receiveMessage() {this->show();}
    /*!
     * \brief getCode : fonction héritée de la classe Widget, code utilisé lors de la distribution
     * des messages par le mediator
     * \return un code au format String
     */
    QString getCode() {return "dialog";}

private :
    /*!
     * \brief createArticle : Ajoute une nouvelle note de type Article au NotesManager et à la base de données
     */
    void createArticle();
    /*!
     * \brief createTache : Ajoute une nouvelle note de type Tache au NotesManager et à la base de données
     */
    void createTache();
    /*!
     * \brief createImage : Ajoute une nouvelle note de type Image au NotesManager et à la base de données
     */
    void createImage();
    /*!
     * \brief createAudio : Ajoute une nouvelle note de type Audio au NotesManager et à la base de données
     */
    void createAudio();
    /*!
     * \brief createVideo : Ajoute une nouvelle note de type Video au NotesManager et à la base de données
     */
    void createVideo();


private slots:
    /*!
     * \brief on_buttonBox_clicked : appel la fonction d'ajout de nouvelle note en fonction du type
     * \param button
     */
    void on_buttonBox_clicked(QAbstractButton *button);


private:
    Ui::Dialog *ui;
    NotesManager& nm;
};

#endif // DIALOG_H
