#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include "Note.h"

class DbManager
{
private:
    QSqlDatabase db;
public:
    DbManager(const QString& path);
    bool addNote(Note& n);
};

#endif // DBMANAGER_H
