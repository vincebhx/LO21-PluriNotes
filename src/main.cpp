#include "dbmanager.h"
#include "note/notesmanager.h"
#include "../ui/mainwindow.h"

#include <QApplication>
#include <QSqlError>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    try{
        DbManager& db = DbManager::instance();
        NotesManager& nm = NotesManager::instance();

        for (NMIterator it = nm.begin(); it != nm.end(); it++)
            for(VersionIterator it2 = (*it)->begin(); it2 != (*it)->end(); it2++)
                std::cout<<(*it2)->getId().toStdString()<<" v"<<(*it2)->getVersion()<<" - "<<(*it2)->getTitre().toStdString()<<std::endl;

        MainWindow window;
        window.show();

        QObject::connect(&app, SIGNAL(aboutToQuit()), &window, SLOT(onClose()));
    }
    catch(QSqlError e) { std::cout<<"Erreur : "<<e.driverText().toStdString()<<" - "<<e.databaseText().toStdString()<<std::endl;
                         DbManager::instance().free(); }
    catch (...) { std::cout<<"ERREUR"<<std::endl;
                  DbManager::instance().free(); }

    return app.exec();
}
