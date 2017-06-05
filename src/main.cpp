#include "dbmanager.h"
#include "exception.h"
#include "note/notesmanager.h"
#include "../ui/mainwindow.h"

#include <QApplication>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    try{


        DbManager& dbM = DbManager::instance();

            QSqlTableModel *model = new QSqlTableModel(0, dbM.db);
                model->setTable("Article");
                model->setEditStrategy(QSqlTableModel::OnManualSubmit);
                model->select();
                model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));

                QTableView *view = new QTableView;
                view->setModel(model);
                view->hideColumn(0); // don't show the ID
                view->show();

        /*DbManager& db = DbManager::instance();
        NotesManager& nm = NotesManager::instance();


        for (NMIterator it = nm.begin(); it != nm.end(); it++)
            std::cout<<(*it)->currentVersion()->getId().toStdString()<<" v"<<(*it)->currentVersion()->getVersion()
                    <<" - "<<(*it)->currentVersion()->getTitre().toStdString()<<std::endl;
*/

    }
    catch(Exception e) { std::cout<<"Erreur standard: "<<e.getInfo().toStdString()<<std::endl; }
    catch(QSqlError e) { std::cout<<"Erreur SQL: "<<e.driverText().toStdString()<<" - "<<e.databaseText().toStdString()<<std::endl; }
    catch (...) { std::cout<<"ERREUR"<<std::endl; }

    MainWindow window;
    window.show();

    QObject::connect(&app, SIGNAL(aboutToQuit()), &window, SLOT(onClose()));

    return app.exec();
}
