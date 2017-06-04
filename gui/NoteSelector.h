#ifndef NOTESELECTOR_H
#define NOTESELECTOR_H
#include "../src/NotesManager.h"
#include <QAbstractTableModel>


class NoteSelector : public QAbstractTableModel
{

private :
    QStringList id;
    QStringList titre;
    QStringList version;
    QStringList creat;
    QStringList modif;

public:
    NoteSelector(NotesManager& nm, QObject* parent = 0);

   int rowCount(const QModelIndex &parent = QModelIndex()) const
    { return this->id.count(); }
   int columnCount(const QModelIndex &parent = QModelIndex()) const {
       return 5;
   }

   QVariant data (const QModelIndex &index, int role) const;
};


#endif // NOTESELECTOR_H
