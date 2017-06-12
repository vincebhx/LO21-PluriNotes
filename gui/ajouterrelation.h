#ifndef AJOUTERRELATION_H
#define AJOUTERRELATION_H

#include <QDialog>
#include "../src/note/notesmanager.h"
namespace Ui {
class AjouterRelation;
}

class AjouterRelation : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterRelation(QWidget *parent = 0);
    ~AjouterRelation();

private:
    Ui::AjouterRelation *ui;
    NotesManager& nm;
};

#endif // AJOUTERRELATION_H
