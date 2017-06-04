#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../src/NotesManager.h"

#include <QMainWindow>
#include <QObject>

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(NotesManager& nm);
public slots:
    void onClose();
};

#endif // MAINWINDOW_H
