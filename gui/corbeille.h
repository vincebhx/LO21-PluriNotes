#ifndef CORBEILLE_H
#define CORBEILLE_H

#include <QMainWindow>
#include "mediator.h"
#include "../src/note/notesmanager.h"


namespace Ui {
class Corbeille;
}

class Corbeille : public QMainWindow, public Widget
{
    Q_OBJECT

public:
    explicit Corbeille(QWidget *parent = 0);
    ~Corbeille();
    void loadTable();
    QString getCode() {return "corbeille";}
    void receiveMessageCorbeille();

    void receiveMessage() {};

    void supprimerNote();

    void restaurer();


private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Corbeille *ui;
    NotesManager& nm;
};

#endif // CORBEILLE_H
