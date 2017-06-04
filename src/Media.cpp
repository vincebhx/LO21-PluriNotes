#include "Media.h"
#include <QLineEdit>

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
