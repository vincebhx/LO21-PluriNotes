#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include "Note.h"

class DbManager
{
private:
    QSqlDatabase db;
    static DbManager* _instance;
    DbManager(const QString& path);
    ~DbManager();
public:
    static DbManager& instance();
    bool addNote(Note& n);
    void free();
};

#endif // DBMANAGER_H
