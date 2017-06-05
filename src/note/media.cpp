#include "media.h"
#include "../exception.h"

#include <QLineEdit>
#include <QSqlError>
#include <QSqlRecord>

QFormLayout* Media::getLayout() {
    //Description
    QLineEdit* descEdit = new QLineEdit(description);
    descEdit->setFixedWidth(300);

    //Fichier
    QLineEdit* fileEdit = new QLineEdit(filepath);
    fileEdit->setFixedWidth(300);

    //Layout
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Description", descEdit);
    layout->addRow("Fichier", fileEdit);

    return layout;
}

QSqlQuery Media::prepareQuery() {
    QSqlQuery query;

    query.prepare("INSERT INTO Media VALUES (:id, :version, :type, :titre, :dateCreation, :dateModification, :description, :filepath)");
    query.bindValue(":type", getTypeStr());
    query.bindValue(":description", description);
    query.bindValue(":filepath", filepath);

    return query;
}

void Media::load(NotesManager &nm, Type type) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Media WHERE type = ':type' ORDER BY id, version ASC");
    query.bindValue(":type", TypeStr[type]);
    bool success = query.exec();
    if(!success) throw query.lastError();

    int* index = new int;
    index[0] = query.record().indexOf("id");
    index[1] = query.record().indexOf("version");
    index[2] = query.record().indexOf("titre");
    index[3] = query.record().indexOf("dateCreation");
    index[4] = query.record().indexOf("dateModification");
    index[5] = query.record().indexOf("description");
    index[6] = query.record().indexOf("filePath");

    if (query.first()) {
        QString id;
        QString currentId = query.value(index[0]).toString();
        VersionIndex* vindex = new VersionIndex;
        Note* n;

        do {
            id = query.value(index[0]).toString();

            switch(type) {
            case IMAGE:
                n = new Image(
                    id,  //ID
                    query.value(index[1]).toInt(),     //Version
                    query.value(index[2]).toString(),  //Titre
                    QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                    QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de modification
                    query.value(index[5]).toString(),  //Description
                    query.value(index[6]).toString()  //Filepath
                );
                break;
            case AUDIO:
                n = new Audio(
                    id,  //ID
                    query.value(index[1]).toInt(),     //Version
                    query.value(index[2]).toString(),  //Titre
                    QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                    QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de modification
                    query.value(index[5]).toString(),  //Description
                    query.value(index[6]).toString()  //Filepath
                );
                break;
            case VIDEO:
                n = new Video(
                    id,  //ID
                    query.value(index[1]).toInt(),     //Version
                    query.value(index[2]).toString(),  //Titre
                    QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                    QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de modification
                    query.value(index[5]).toString(),  //Description
                    query.value(index[6]).toString()  //Filepath
                );
                break;
            default:
                throw Exception("Erreur de chargement des objets Médias depuis la base de données.");
            }

            if (id != currentId) {
                currentId = id;
                nm.addNote(vindex);
                vindex = new VersionIndex;
            }

            vindex->addVersion(n);
        } while (query.next());
    }

    query.finish();
}
