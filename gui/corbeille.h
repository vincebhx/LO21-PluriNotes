#ifndef CORBEILLE_H
#define CORBEILLE_H

#include <QMainWindow>
#include "mediator.h"
#include "../src/note/notesmanager.h"


namespace Ui {
class Corbeille;
}
/*!
 * \brief The Corbeille class : correspond à la fenêtre de corbeille
 */
class Corbeille : public QMainWindow, public Widget
{
    Q_OBJECT

public:
    explicit Corbeille(QWidget *parent = 0);
    ~Corbeille();
    /*!
     * \brief loadTable : charge la table des notes dont l'état est "CORBEILLE" dans le NotesManager
     */
    void loadTable();
    /*!
     * \brief getCode : fonction héritée de la classe Widget, code utilisé lors de la distribution
     * des messages par le mediator
     * \return un code au format String
     */
    QString getCode() {return "corbeille";}
    /*!
     * \brief receiveMessageCorbeille: contient les instructions à effectuer si le messager "Ajout Relation" est reçue
     */
    void receiveMessageCorbeille();
    /*!
     * \brief supprimerNote : permet de supprimer une note de NotesManager ainsi que de la base de données
     */
    void supprimerNote();
    /*!
     * \brief restaurer : change l'état de la note sélectionnée de "CORBEILLE" à "ACTIVES"
     */
    void restaurer();


private slots:
    /*!
     * \brief on_pushButton_4_clicked : envoie le message "CORBEILLE" au mediator
     */
    void on_pushButton_4_clicked();
    /*!
     * \brief on_pushButton_clicked : restaure la note selectionnée
     */
    void on_pushButton_clicked();
    /*!
     * \brief on_pushButton_3_clicked : supprime définitivement toutes les notes de la corbeille
     */

    void on_pushButton_3_clicked();
    /*!
     * \brief on_pushButton_2_clicked : supprime définitivement la note sélectionnée
     */
    void on_pushButton_2_clicked();

private:
    Ui::Corbeille *ui;
    NotesManager& nm;
};

#endif // CORBEILLE_H
