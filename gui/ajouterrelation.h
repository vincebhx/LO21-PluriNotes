#ifndef AJOUTERRELATION_H
#define AJOUTERRELATION_H

#include <QDialog>
#include "../src/note/notesmanager.h"
#include "mediator.h"

namespace Ui {
class AjouterRelation;
}
/*!
 * \brief The AjouterRelation class : correspond à la fenêtre d'ajout de relation
 */
class AjouterRelation : public QDialog, public Widget
{
    Q_OBJECT

public:
    /*!
     * \brief AjouterRelation : constructeur de la classe
     * \param parent
     */
    explicit AjouterRelation(QWidget *parent = 0);
    ~AjouterRelation();
    /*!
     * \brief getCode : fonction héritée de la classe Widget, code utilisé lors de la distribution
     * des messages par le mediator
     * \return un code au format String
     */
    QString getCode() {return "ajouterR";}

    /*!
     * \brief receiveMessageARelation : contient les instructions à effectuer si le messager "Ajout Relation" est reçue
     */
    void receiveMessageARelation();

private slots:
    /*!
     * \brief on_pushButton_clicked : instancie la Relation à partir des informations entrée et ajoute le premier couple à la relation à partir des notes sélectionnées
     */
    void on_pushButton_clicked();

private:
    Ui::AjouterRelation *ui;
    NotesManager& nm;
};

#endif // AJOUTERRELATION_H
