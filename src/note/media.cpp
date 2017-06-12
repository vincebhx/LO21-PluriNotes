#include "media.h"
#include "../exception.h"

#include <QLineEdit>
#include <QSqlError>
#include <QSqlRecord>

#include <iostream>

const QString Image::idStem  = "IMG_";
unsigned int Image::idIncrement = 0;

const QString Audio::idStem  = "AUD_";
unsigned int Audio::idIncrement = 0;

const QString Video::idStem  = "VID_";
unsigned int Video::idIncrement = 0;

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

    query.prepare("INSERT INTO Media VALUES (:etat, :id, :version, :type, :titre, :dateCreation, :dateModification, :description, :filepath)");
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
    modelMedia->sort(1, Qt::AscendingOrder);    //ORDER BY version ASC
    modelMedia->sort(0, Qt::AscendingOrder);    //ORDER BY id ASC
    return modelMedia;
}

QTableView* Media::getTableView(QSqlTableModel *table) {
    QTableView *viewMedia = new QTableView;
    viewMedia->setModel(table);
    viewMedia->hideColumn(0); // don't show the ID
    return viewMedia;
}
