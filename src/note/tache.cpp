#include "../exception.h"
#include "tache.h"

#include <QComboBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QSqlError>
#include <QSqlRecord>

QFormLayout* Tache::getLayout() {
    //Sélection du statut
    QComboBox* statutBox = new QComboBox;
    statutBox->addItem("En attente");
    statutBox->addItem("En cours");
    statutBox->addItem("Terminé");

    switch (statut) {
    case EN_ATTENTE:
        statutBox->setCurrentIndex(EN_ATTENTE);
        break;
    case EN_COURS:
        statutBox->setCurrentIndex(EN_COURS);
        break;
    case TERMINE:
        statutBox->setCurrentIndex(TERMINE);
        break;
    default:
        throw Exception("Statut invalide lors de la création du layout de la tâche " + this->getId() + " v" + this->getVersion());
    }

    //Action
    QLineEdit* actionEdit = new QLineEdit(action);
    actionEdit->setFixedWidth(300);

    //Date d'échéance
    QDateTimeEdit* echeanceEdit = new QDateTimeEdit(dateEcheance);
    echeanceEdit->setFixedWidth(300);

    //Layout
    QFormLayout* layout = new QFormLayout;
    layout->addRow("Action", actionEdit);
    layout->addRow("Date d'échéance", echeanceEdit);
    layout->addRow("Statut", statutBox);

    return layout;
}

QSqlQuery Tache::prepareQuery() {
    QSqlQuery query;

    query.prepare("INSERT INTO Tache VALUES (:id, :version, :titre, :dateCreation, :dateModification, :action, :priorite, :statut)");
    query.bindValue(":action", action);
    query.bindValue(":priorite", priorite);
    query.bindValue(":statut", StatutStr[statut]);

    return query;
}

void Tache::load(NotesManager &nm) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Tache ORDER BY id, version ASC");
    bool success = query.exec();
    if(!success) throw query.lastError();

    int* index = new int;
    index[0] = query.record().indexOf("id");
    index[1] = query.record().indexOf("version");
    index[2] = query.record().indexOf("titre");
    index[3] = query.record().indexOf("dateCreation");
    index[4] = query.record().indexOf("dateModification");
    index[5] = query.record().indexOf("action");
    index[6] = query.record().indexOf("priorite");
    index[7] = query.record().indexOf("dateEcheance");
    index[8] = query.record().indexOf("statut");

    if (query.first()) {
        QString id;
        QString currentId = query.value(index[0]).toString();
        VersionIndex* vindex = new VersionIndex;
        Note* n;
        QString sStr;
        Statut st;

        do {
            id = query.value(index[0]).toString();

            sStr = query.value(index[8]).toString();
            if (sStr == StatutStr[EN_COURS]) st = EN_COURS;
            else if (sStr == StatutStr[TERMINE]) st = TERMINE;
            else st = EN_ATTENTE;

            n = new Tache(
                id,  //ID
                query.value(index[1]).toInt(),     //Version
                query.value(index[2]).toString(),  //Titre
                QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
                QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de modification
                query.value(index[5]).toString(),  //Action
                query.value(index[6]).toInt(),     //Priorité
                QDateTime::fromString(query.value(index[7]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date d'échéance
                st //Statut
            );

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
