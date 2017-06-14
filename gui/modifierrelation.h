#ifndef MODIFIERRELATION_H
#define MODIFIERRELATION_H

#include <QDialog>
#include "mediator.h"
#include "../src/note/notesmanager.h"
#include <QAbstractButton>

namespace Ui {
class ModifierRelation;
}

class ModifierRelation : public QDialog, public Widget
{
    Q_OBJECT

public:
    explicit ModifierRelation(QWidget *parent = 0);
    ~ModifierRelation();
    QString getCode() {return "modifierR"; }
    void loadRelations();
    void loadTable();
    void receiveMessageMRelation();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ModifierRelation *ui;
    NotesManager& nm;
    RelationsManager& RM;
};

#endif // MODIFIERRELATION_H
