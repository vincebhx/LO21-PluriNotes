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
        cout<<"3 "<<endl;
        MainWindow window(nm);

        //C'est là qu'il crashe

        cout<<"4 "<<endl;
        QObject::connect(&app, SIGNAL(aboutToQuit()), &window, SLOT(onClose()));
        cout<<"5 "<<endl;
        window.show();
        cout<<"6 "<<endl;
    } catch (NoteException e) { cout << e.getInfo()<<endl; }
      catch (QSqlError e) { cout << e.driverText().toStdString()<<endl; }

    cout<<"Imma cut a bitch"<<endl;
    return app.exec();
}
