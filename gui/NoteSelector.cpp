#include "NoteSelector.h"

NoteSelector::NoteSelector(NotesManager& nm, QObject* parent)
{
    for(NMIterator it = nm.begin(); it != nm.end(); it++) {
        id << (*it)->currentNote()->getId();
        titre << (*it)->currentNote()->getTitre();
        version << QString::number((*it)->currentNote()->getVersion());
        creat << (*it)->currentNote()->getDateCreat().toString("dd/MM/yyyy hh::mm::ss");
        modif << (*it)->currentNote()->getDateLastModif().toString("dd/MM/yyyy hh::mm::ss");
    }
}

QVariant NoteSelector::data (const QModelIndex &index, int role) const {
    if (! index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
            return this->id.at(index.row());
        else if (index.column() == 1)
            return this->titre.at(index.row());
        else if (index.column() == 2)
            return this->version.at(index.row());
        else if (index.column() == 3)
            return this->creat.at(index.row());
        else if (index.column() == 4)
            return this->modif.at(index.row());
    }
    else
        return QVariant();
}
