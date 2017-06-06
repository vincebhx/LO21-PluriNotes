#ifndef NOTEVIEWER_H
#define NOTEVIEWER_H

#include <QObject>
#include <QWidget>
#include <iostream>

class NoteViewer: public QWidget
{
    Q_OBJECT
public:
    NoteViewer() {}

public slots:
    void saveNote();
};

#endif // NOTEVIEWER_H
