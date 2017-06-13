#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "note/note.h"
#include "./src/relation/relation.h"

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

    bool saveNote(Note* n);
    bool saveRelation(Relation* r);
    bool saveCouple(Relation* r, Couple* c);

    bool changeNoteState(Note* n);

    bool deleteNote(Note* n);

    bool deleteRelation(Relation* r);
    bool deleteCouple(Couple* c, Relation* r);

    QString getLastQuery(const QSqlQuery& query);
};

#endif // DBMANAGER_H
