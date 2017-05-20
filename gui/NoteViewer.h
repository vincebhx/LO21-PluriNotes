#ifndef NOTEVIEWER_H
#define NOTEVIEWER_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "../src/Note.h"

class NoteViewer: public QWidget {
private:
    /*Macros*/
    Q_OBJECT
    /*Layouts*/
    QFormLayout* layout;
    /*Widgets*/
    QLabel* idLabel;
    QLabel* titleLabel;
    QLabel* textLabel;
    QLineEdit* id;
    QLineEdit* title;
    QTextEdit* text;
    QPushButton* save;
public:
    NoteViewer();
    void ViewNote(Note* n);
};

#endif // NOTEVIEWER_H
