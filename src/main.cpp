#include "../src/note/article.h"
#include "dbmanager.h"
#include "exception.h"
#include "note/notesmanager.h"
#include "../gui/mainwindow.h"
#include "../gui/dialog.h"
#include "../gui/mediator.h"
#include "../src/note/media.h"
#include "../src/note/tache.h"
#include "../src/note/note.h"
#include "../src/relation/relation.h"
#include "../src/relation/couple.h"
#include "../src/relation/relationsmanager.h"

#include <QApplication>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <iostream>
#include <QDebug>
#include <QString>
#include <QModelIndex>
#include <QDataStream>
#include <QObject>
#include <typeinfo>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    try{

        DbManager& dbM = DbManager::instance();
        NotesManager& nm = NotesManager::instance();
        RelationsManager& rm = RelationsManager::instance();
        nm.load();
        int  i;
        QString id;               ///Identifiant de la note
        unsigned int version;           ///Numéro de version
        QString titre;                  ///Titre de la note
        QDateTime dateCreation;   ///Date de création
        QDateTime dateModification;
        QString texte;

        QSqlTableModel* modelArticle = Article::getTableModel(dbM.db);
        QTableView* viewArticle = Article::getTableView(modelArticle);
        //viewArticle->show();

        for (i= 0; i < modelArticle->rowCount(); i++) {
            id = viewArticle->model()->data(viewArticle->model()->index(i,0)).toString();
            version = viewArticle->model()->data(viewArticle->model()->index(i,1)).toInt();
            titre = viewArticle->model()->data(viewArticle->model()->index(i,2)).toString();
            dateCreation = viewArticle->model()->data(viewArticle->model()->index(i,3)).toDateTime();
            dateModification = viewArticle->model()->data(viewArticle->model()->index(i,4)).toDateTime();
            texte = viewArticle->model()->data(viewArticle->model()->index(i,5)).toString();
            //Article(id, version, titre, dateCreation, dateModification, texte);

        }

        QSqlTableModel* modelTache = Tache::getTableModel(dbM.db);
        QTableView* viewTache = Tache::getTableView(modelTache);
        //viewTache->show();

        QSqlTableModel* modelMedia = Media::getTableModel(dbM.db);
        QTableView* viewMedia = Media::getTableView(modelMedia);
        //viewMedia->show();

        std::string id1;
        unsigned int ver1;
        for(NMIterator it = nm.begin(ACTIVES); it!= nm.end(ACTIVES); it++) {
            id1 = (*it)->currentVersion()->getId().toStdString();
            ver1 = (*it)->currentVersion()->getVersion();
            std::cout<<id1<<" v"<<ver1<<std::endl;
        }

    }
    catch(Exception e) { std::cout<<"Erreur standard: "<<e.getInfo().toStdString()<<std::endl; }
    catch(QSqlError e) { std::cout<<"Erreur SQL: "<<e.driverText().toStdString()<<" - "<<e.databaseText().toStdString()<<std::endl; }
    catch (...) { std::cout<<"ERREUR"<<std::endl; }
    MainWindow* window = new MainWindow;
    window->show();
    Dialog* createnote = new Dialog;
    Mediator* mediator = Mediator::instance();
    mediator->addComponent(window);
    mediator->addComponent(createnote);
    //mediator->disributeMessage(createnote, "hello");


    QObject::connect(&app, SIGNAL(aboutToQuit()), window, SLOT(onClose()));

    return app.exec();
}
