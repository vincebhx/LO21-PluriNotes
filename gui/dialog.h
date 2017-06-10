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

class Dialog : public QDialog, public Widget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void validForm();
    ~Dialog();
    void receiveMessage() { std::cout << "message recu dialog" << std::endl;
                          this->show();}

    /*void sendMessage() {

        std::cout << "message envoye par dialog" << std::endl;
                       }*/

    QString getCode() {return "dialog";}


private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void createArticle();

    void createTache();

    void createImage();

    void createAudio();

    void createVideo();

private:
    Ui::Dialog *ui;
    NotesManager& nm;
};

#endif // DIALOG_H
