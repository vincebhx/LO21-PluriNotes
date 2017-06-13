#ifndef AJOUTERRELATION_H
#define AJOUTERRELATION_H

#include <QDialog>
#include "../src/note/notesmanager.h"
#include "mediator.h"

namespace Ui {
class AjouterRelation;
}

class AjouterRelation : public QDialog, public Widget
{
    Q_OBJECT

public:
    explicit AjouterRelation(QWidget *parent = 0);
    ~AjouterRelation();
    QString getCode() {return "ajouterR";}
    void receiveMessage() {};
    void receiveMessageARelation();

private:
    Ui::AjouterRelation *ui;
    NotesManager& nm;
};

#endif // AJOUTERRELATION_H
