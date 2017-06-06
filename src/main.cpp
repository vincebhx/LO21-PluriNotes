#include "dbmanager.h"
#include "exception.h"
#include "note/notesmanager.h"
#include "../gui/mainwindow.h"

#include <QApplication>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <iostream>
#include <QString>
#include <QModelIndex>
#include <QDataStream>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    try{


        DbManager& dbM = DbManager::instance();
        NotesManager& nm = NotesManager::instance();
        //nm.load();
        int  i;
        QString id;               ///Identifiant de la note
        unsigned int version;           ///Numéro de version
        QString titre;                  ///Titre de la note
        QDateTime dateCreation;   ///Date de création
        QDateTime dateModification;
        QString texte;
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

            for (i= 0; i < modelArticle->rowCount(); i++) {
                id = viewArticle->model()->data(viewArticle->model()->index(i,0)).toString();
                version = viewArticle->model()->data(viewArticle->model()->index(i,1)).toInt();
                titre = viewArticle->model()->data(viewArticle->model()->index(i,2)).toString();
                dateCreation = viewArticle->model()->data(viewArticle->model()->index(i,3)).toDateTime();
                dateModification = viewArticle->model()->data(viewArticle->model()->index(i,4)).toDateTime();
                texte = viewArticle->model()->data(viewArticle->model()->index(i,5)).toString();
                //Article(id, version, titre, dateCreation, dateModification, texte);

            }



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
