#include <iostream>
#include <QApplication>
#include <QObject>
#include <QSqlError>
#include "Date.h"
#include "Note.h"
#include "NotesManager.h"
#include "DbManager.h"
#include "NoteException.h"
#include "../gui/MainWindow.h"
#include "../gui/CreateNote.h"
using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    try {
        DbManager& db = DbManager::instance();
        NotesManager& nm = NotesManager::instance();
        MainWindow fenetre;
        CreateNote fenetre2;
        QObject::connect(&app, SIGNAL(aboutToQuit()), &fenetre, SLOT(onClose()));
        fenetre.show();
        fenetre2.show();
    } catch (NoteException e) { cout << e.getInfo(); }
      catch (QSqlError e) { cout << e.driverText().toStdString(); }
    return app.exec();
}
