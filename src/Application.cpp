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
        std::cout << "fin note manager construct" << std::endl;
        MainWindow* fenetre = new MainWindow();
        CreateNote* fenetre2 = new CreateNote();
        QObject::connect(&app, SIGNAL(aboutToQuit()), fenetre, SLOT(onClose()));
        std::cout << "avant fenetre.show()" << std::endl;
        fenetre->show();
        fenetre2->show();
    } catch (NoteException e) { cout << e.getInfo(); }
      catch (QSqlError e) { cout << e.driverText().toStdString(); }
    return app.exec();
}
