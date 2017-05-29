#include <iostream>
#include <QApplication>
#include <QObject>
#include "Date.h"
#include "Note.h"
#include "NotesManager.h"
#include "DbManager.h"
#include "../gui/MainWindow.h"

using namespace std;

int main(int argc, char* argv[]) {
    DbManager("notes.db");
    QApplication app(argc, argv);
    MainWindow fenetre;
    QObject::connect(&app, SIGNAL(aboutToQuit()), &fenetre, SLOT(onClose()));
    fenetre.show();
    return app.exec();
}
