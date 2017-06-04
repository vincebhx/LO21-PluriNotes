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
        cout<<"2 "<<endl;
        NotesManager& nm = NotesManager::instance();
        cout<<"Note courante : "<<nm.currentNote()->getId().toStdString()<<" v"<<nm.currentNote()->getVersion()<<endl;
        cout<<"3 "<<endl;;
        MainWindow windaube(nm);
        cout<<"4 "<<endl;
        QObject::connect(&app, SIGNAL(aboutToQuit()), &windaube, SLOT(onClose()));
        cout<<"5 "<<endl;
        windaube.show();
        cout<<"6 "<<endl;
    } catch (NoteException e) { cout << e.getInfo(); }
      catch (QSqlError e) { cout << e.driverText().toStdString(); }
    return app.exec();
}
