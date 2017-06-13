#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include "mediator.h"
#include "src/note/notesmanager.h"
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Widget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void receiveMessage();
    QString getCode() {return "mainwindow";}

private slots:

    void on_pushButton_clicked();

    void onClose();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void loadClicked(Note* clicked, QString type);

    void loadVersion(VersionIndex *vClicked);

    void on_tableWidget_2_doubleClicked(const QModelIndex &index);

    void on_enregistrer_clicked();

    void saveNewVersionArticle();

    void loadTableWidgetActives();

    void loadTableWidgetArchive();

    void loadTableTache();

    void saveNewVersionTache();

    void saveNewVersionImage();

    void saveNewVersionVideo();

    void saveNewVersionAudio();

    void on_pushButton_5_clicked();

    void loadNote(Note* note, QString type);

    void on_tableWidget_3_doubleClicked(const QModelIndex &index);

    void changeStateButton(Etat etat);

    void on_archiver_clicked();

    void on_supprimer_clicked();

private:
    Ui::MainWindow *ui; // //
    NotesManager& nm;
};



#endif // MAINWINDOW_H
