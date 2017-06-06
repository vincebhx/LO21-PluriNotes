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

        QSqlTableModel *modelArticle = new QSqlTableModel(0, dbM.db);
            modelArticle->setTable("Article");
            modelArticle->setEditStrategy(QSqlTableModel::OnManualSubmit);
            modelArticle->select();
            modelArticle->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            modelArticle->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));

            QTableView *viewArticle = new QTableView;
            viewArticle->setModel(modelArticle);
            viewArticle->hideColumn(0); // don't show the ID
            viewArticle->show();

        QSqlTableModel *modelTache = new QSqlTableModel(0, dbM.db);
            modelTache->setTable("Tache");
            modelTache->setEditStrategy(QSqlTableModel::OnManualSubmit);
            modelTache->select();
            modelTache->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            modelTache->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));

            QTableView *viewTache = new QTableView;
            viewTache->setModel(modelTache);
            viewTache->hideColumn(0); // don't show the ID
            viewTache->show();

        QSqlTableModel *modelMedia = new QSqlTableModel(0, dbM.db);
                modelMedia->setTable("Media");
                modelMedia->setEditStrategy(QSqlTableModel::OnManualSubmit);
                modelMedia->select();
                modelMedia->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                modelMedia->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));

                QTableView *viewMedia = new QTableView;
                viewMedia->setModel(modelMedia);
                viewMedia->hideColumn(0); // don't show the ID
                viewMedia->show();

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
