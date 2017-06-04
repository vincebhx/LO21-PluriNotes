#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../src/NotesManager.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

=======
    MainWindow(NotesManager& nm);
>>>>>>> 5eb5a1e91a14df14f24c07ac42ff73d80cd00401
public slots:
    void onClose();
};

#endif // MAINWINDOW_H
