#include "media.h"
#include "../exception.h"

#include <QLineEdit>
#include <QSqlError>
#include <QSqlRecord>

#include <iostream>

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

QSqlTableModel* Media::getTableModel(QSqlDatabase db) {
    QSqlTableModel* modelMedia = new QSqlTableModel(0, db);
    modelMedia->setTable("Media");
    modelMedia->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelMedia->select();
    modelMedia->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modelMedia->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
    return modelMedia;
}

QTableView* Media::getTableView(QSqlTableModel *table) {
    QTableView *viewMedia = new QTableView;
    viewMedia->setModel(table);
    viewMedia->hideColumn(0); // don't show the ID
    return viewMedia;
}

void Image::load(NotesManager &nm) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Media WHERE type = 'image' ORDER BY id, version ASC");
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

            n = new Image(
                id,  //ID
                query.value(index[1]).toInt(),     //Version
                query.value(index[2]).toString(),  //Titre
                QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de modification
                query.value(index[5]).toString(),  //Description
                query.value(index[6]).toString()  //Filepath
            );

            if (id != currentId) {
                currentId = id;
                nm.addNote(vindex);
                vindex = new VersionIndex;
            }

            std::cout<<"AddVersion "<<n->getId().toStdString()<<" v"<<n->getVersion()<<std::endl;
            vindex->addVersion(n);
        } while (query.next());
    }

    query.finish();
}

void Audio::load(NotesManager &nm) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Media WHERE type = 'audio' ORDER BY id, version ASC");
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

            n = new Audio(
                id,  //ID
                query.value(index[1]).toInt(),     //Version
                query.value(index[2]).toString(),  //Titre
                QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de modification
                query.value(index[5]).toString(),  //Description
                query.value(index[6]).toString()  //Filepath
            );

            if (id != currentId) {
                currentId = id;
                nm.addNote(vindex);
                vindex = new VersionIndex;
            }

            std::cout<<"AddVersion "<<n->getId().toStdString()<<" v"<<n->getVersion()<<std::endl;
            vindex->addVersion(n);
        } while (query.next());
    }

    query.finish();
}

void Video::load(NotesManager &nm) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Media WHERE type = 'video' ORDER BY id, version ASC");
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

            n = new Video(
                id,  //ID
                query.value(index[1]).toInt(),     //Version
                query.value(index[2]).toString(),  //Titre
                QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de modification
                query.value(index[5]).toString(),  //Description
                query.value(index[6]).toString()  //Filepath
            );

            if (id != currentId) {
                currentId = id;
                nm.addNote(vindex);
                vindex = new VersionIndex;
            }

            std::cout<<"AddVersion "<<n->getId().toStdString()<<" v"<<n->getVersion()<<std::endl;
            vindex->addVersion(n);
        } while (query.next());
    }

    query.finish();
}
