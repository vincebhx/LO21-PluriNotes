#include "media.h"

#include <QLineEdit>

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

void Media::load(Type type) {

}
