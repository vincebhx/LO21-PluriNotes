#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DbManager
{
private:
    QSqlDatabase db;
public:
    DbManager(const QString& path);
};

#endif // DBMANAGER_H
