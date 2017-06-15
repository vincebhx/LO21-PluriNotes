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
#include "../gui/ajouterrelation.h"
#include "../gui/corbeille.h"
#include "../gui/modifierrelation.h"

#include <QApplication>
#include <QSqlError>
#include <iostream>
#include <QString>
/*
#include <QModelIndex>
#include <QDataStream>
#include <QObject>
#include <typeinfo>*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    try{

        //Initialisation des instances des managers.

        DbManager::instance();
        NotesManager::instance();
        RelationsManager::instance();

    }
    catch(Exception e) { std::cout<<"Erreur standard: "<<e.getInfo().toStdString()<<std::endl; }
    catch(QSqlError e) { std::cout<<"Erreur SQL: "<<e.driverText().toStdString()<<" - "<<e.databaseText().toStdString()<<std::endl; }
    catch (...) { std::cout<<"ERREUR"<<std::endl; }

    MainWindow* window = new MainWindow;
    window->show();

    Dialog* createnote = new Dialog;
    Mediator* mediator = Mediator::instance();
    AjouterRelation* ajouterR = new AjouterRelation;
    Corbeille* corbeille = new Corbeille;
    ModifierRelation* modifierR = new ModifierRelation;

    mediator->addComponent(window);
    mediator->addComponent(createnote);
    mediator->addComponent(ajouterR);
    mediator->addComponent(corbeille);
    mediator->addComponent(modifierR);
    //mediator->disributeMessage(createnote, "hello");

    QObject::connect(&app, SIGNAL(aboutToQuit()), window, SLOT(onClose()));

    return app.exec();
}
