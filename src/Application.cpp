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

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    cout<<"1 ";
    try {
        DbManager& db = DbManager::instance();
        cout<<"2 ";
        NotesManager& nm = NotesManager::instance();
        cout<<"3 ";
        MainWindow window(nm);

        //C'est là qu'il crashe

        cout<<"4 ";
        QObject::connect(&app, SIGNAL(aboutToQuit()), &window, SLOT(onClose()));
        cout<<"5 ";
        window.show();
        cout<<"6 ";
    } catch (NoteException e) { cout << e.getInfo(); }
      catch (QSqlError e) { cout << e.driverText().toStdString(); }
    return app.exec();
}
