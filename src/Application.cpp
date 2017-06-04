#include <iostream>
#include <QApplication>
#include <QObject>
#include "Date.h"
#include "Note.h"
#include "NotesManager.h"
#include "DbManager.h"
#include "../gui/MainWindow.h"
#include "../gui/CreateNote.h"
using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow fenetre;
    CreateNote fenetre2;
    QObject::connect(&app, SIGNAL(aboutToQuit()), &fenetre, SLOT(onClose()));
    fenetre.show();
    fenetre2.show();
    return app.exec();
}
