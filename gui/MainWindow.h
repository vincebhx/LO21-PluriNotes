#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
public slots:
    void onClose();
};

#endif // MAINWINDOW_H
