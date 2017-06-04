#ifndef NOTEVIEWER_H
#define NOTEVIEWER_H

#include <QWidget>
#include <QVBoxLayout>
#include "../src/NotesManager.h"

class NoteViewer: public QWidget {
private:
    /*Macros*/
    /*Layouts*/
    /*Widgets*/
    /*Signaux*/
public:
    NoteViewer(NotesManager& nm);
};

#endif // NOTEVIEWER_H
