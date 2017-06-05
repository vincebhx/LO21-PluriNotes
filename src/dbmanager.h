#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "note/note.h"

#include <QSqlDatabase>
#include <QString>

class DbManager
{
private:

    static DbManager* _instance;
    DbManager(const QString& path);
    ~DbManager();

public:
    QSqlDatabase db;
    static DbManager& instance();
    void free();
    bool addNote(Note& n);
};

#endif // DBMANAGER_H
