#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "../src/note/notesmanager.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void validForm();
    ~Dialog();

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
