#include <iostream>
#include <QApplication>
#include "Date.h"
#include "Note.h"
#include "NotesManager.h"
#include "../gui/ApplicationGui.h"

using namespace std;

int main(int argc, char* argv[]) {
    //NotesManager* notesManager = NotesManager::instance();
    QApplication app(argc, argv);

    ApplicationGui fenetre;
    fenetre.show();

    return app.exec();
}
