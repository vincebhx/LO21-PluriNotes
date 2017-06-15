#ifndef MODIFIERRELATION_H
#define MODIFIERRELATION_H

#include <QDialog>
#include "mediator.h"
#include "../src/note/notesmanager.h"
#include <QAbstractButton>

namespace Ui {
class ModifierRelation;
}

/*!
 * \brief The ModifierRelation class : fenêtre permettant de modifier une relation : ajouter un couple, supprimer un couple, supprimer la relation
 */
class ModifierRelation : public QDialog, public Widget
{
    Q_OBJECT

public:
    /*!
     * \brief ModifierRelation : constructeur de la classe
     * \param parent
     */
    explicit ModifierRelation(QWidget *parent = 0);
    ~ModifierRelation();
    /*!
     * \brief getCode : fonction héritée de la classe Widget, code utilisé lors de la distribution
     * des messages par le mediator
     * \return
     */
    QString getCode() {return "modifierR"; }
    /*!
     * \brief loadRelations : charge la liste de l'ensemble des relations existantes
     */
    void loadRelations();
    /*!
     * \brief loadTable : charge les couples dans le tableau pour une relation donnée
     */
    void loadTable();
    /*!
     * \brief receiveMessageMRelation : contient les instructions à exécuter lorsque le message "Modifier Relation" est reçu
     */
    void receiveMessageMRelation();

private slots:
    /*!
     * \brief on_comboBox_currentIndexChanged : lorsqu'une relation est selectionnée on charge le tableau des couples
     * \param index
     */
    void on_comboBox_currentIndexChanged(int index);
    /*!
     * \brief on_buttonBox_clicked : envoie le message "Modifier Relation"
     * \param button
     */
    void on_buttonBox_clicked(QAbstractButton *button);
    /*!
     * \brief on_pushButton_2_clicked : supprime la relation courrante
     */
    void on_pushButton_2_clicked();
    /*!
     * \brief on_pushButton_3_clicked : permet d'ajouter un couple à la relation courrante
     */
    void on_pushButton_3_clicked();
    /*!
     * \brief on_pushButton_clicked : permet de supprimer un couple selectionnée à la relation courrante
     */
    void on_pushButton_clicked();

private:
    Ui::ModifierRelation *ui;
    NotesManager& nm;
    RelationsManager& RM;
};

#endif // MODIFIERRELATION_H
