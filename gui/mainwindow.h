#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include "src/note/notesmanager.h"

namespace Ui {
class MainWindow;
//class NoteTableModel;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void onClose();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void loadClicked(Note* clicked, QString type);

    void loadVersion(VersionIndex *vClicked);

    void on_tableWidget_2_doubleClicked(const QModelIndex &index);

    void on_enregistrer_clicked();

    void saveNewVersionArticle();

    void loadTableWidget1();

    void saveNewVersionTache();

private:
    Ui::MainWindow *ui; // //
    NotesManager& nm;
};

/*class NoteTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    NoteTableModel(QObject *parent) {

    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return NotesManager::instance().nbNotes(ACTIVES);
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 5;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

};*/

#endif // MAINWINDOW_H
