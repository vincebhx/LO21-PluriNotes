#include "dbmanager.h"
#include "note/notesmanager.h"
#include "../ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DbManager::instance();
    NotesManager::instance();

    MainWindow window;
    window.show();

    QObject::connect(&app, SIGNAL(aboutToQuit()), &window, SLOT(onClose()));

    return app.exec();
}
