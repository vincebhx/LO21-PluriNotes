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
    bool loadAll(); ///Charge la base de données dans le NotesManager.
    bool saveAll(); ///Sauvegarde le NotesManager dans la base de données.
};

#endif // DBMANAGER_H
