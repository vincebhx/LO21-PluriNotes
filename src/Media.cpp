#include "Media.h"
#include "NoteException.h"

#include <QLineEdit>
#include <QSqlRecord>

QFormLayout* Media::getLayout() {
    //Description
    QLineEdit* descEdit = new QLineEdit(description);
    descEdit->setFixedWidth(300);

    //Fichier
    QLineEdit* fileEdit = new QLineEdit(filePath);
    fileEdit->setFixedWidth(300);

    //Layout et retour
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Description", descEdit);
    layout->addRow("Fichier", fileEdit);
    return layout;
}

QSqlQuery Media::prepareQuery() {
    QSqlQuery query;
    query.prepare("INSERT INTO Media VALUES (:id, :version, :type, :titre, :dateCreation, :dateModification, :description, :filepath)");
    query.bindValue(":type", typeToString());
    query.bindValue(":description", description);
    query.bindValue(":filepath", filePath);
    return query;
}

bool Media::load(NotesManager& nm, QString type)
{
    QSqlQuery query("SELECT * FROM Media WHERE type = '" + type + "' ORDER BY id, version ASC");

    int* index = new int;
    index[0] = query.record().indexOf("id");
    index[1] = query.record().indexOf("version");
    index[2] = query.record().indexOf("titre");
    index[3] = query.record().indexOf("dateCreation");
    index[4] = query.record().indexOf("dateModification");
    index[5] = query.record().indexOf("description");
    index[6] = query.record().indexOf("filePath");

    QString id, currentId = 0;
    unsigned int sizeCount = 0;
    Version* v = new Version;
    Note* n;

    while (query.next())
    {
        sizeCount++;
        id = query.value(index[0]).toString();

        if(currentId != id) {
            cout<<"Nouvelle note :"<<endl;
            if (currentId != 0) {
                nm.addNote(v);
               v = new Version;
            }
            currentId = id;
        }

        if (type == "image")
            n = new Image(
                id,  //ID
                query.value(index[1]).toInt(),     //Version
                query.value(index[2]).toString(),  //Titre

                query.value(index[5]).toString(),  //Description
                query.value(index[6]).toString(),  //Filepath
                QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
            );
        else if (type == "audio")
            n = new Audio(
                id,  //ID
                query.value(index[1]).toInt(),     //Version
                query.value(index[2]).toString(),  //Titre

                query.value(index[5]).toString(),  //Description
                query.value(index[6]).toString(),  //Filepath
                QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
            );
        else if (type == "video")
            n = new Video(
                id,  //ID
                query.value(index[1]).toInt(),     //Version
                query.value(index[2]).toString(),  //Titre

                query.value(index[5]).toString(),  //Description
                query.value(index[6]).toString(),  //Filepath
                QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
            );
        else throw NoteException("Erreur de chargement des objets Médias depuis la base de données.");

        cout<<"Chargement de "<<id.toStdString()<<" v"<<query.value(index[1]).toInt()<<endl;
        v->addNote(n);
    }
    if (sizeCount != 0) nm.addNote(v);

    query.finish();

    return true;
}
