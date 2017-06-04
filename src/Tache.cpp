#include "Tache.h"

#include <QComboBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QSqlRecord>

QFormLayout* Tache::getLayout() {
    //Sélection du statut
    QComboBox* statutBox = new QComboBox;
    statutBox->addItem("En attente");
    statutBox->addItem("En cours");
    statutBox->addItem("Terminé");
    if (statut == enAttente) statutBox->setCurrentIndex(0);     //En attente
    else if (statut == enCours) statutBox->setCurrentIndex(1);  //En cours
    else statutBox->setCurrentIndex(2);                         //Terminé

    //Action
    QLineEdit* actionEdit = new QLineEdit(action);
    actionEdit->setFixedWidth(300);

    //Date d'échéance
    QDateTimeEdit* echeanceEdit = new QDateTimeEdit(dateEcheance);
    echeanceEdit->setFixedWidth(300);

    //Layout et retour
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

    QString s;
    if (statut == enAttente) s = "enAttente";
    else if (statut == enCours) s = "enCours";
    else s = "termine";
    query.bindValue(":statut", s);

    return query;
}

bool Tache::load(NotesManager& nm)
{
    QSqlQuery query("SELECT * FROM Tache ORDER BY id, version ASC");

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

    QString statutStr, id, currentId = 0;
    unsigned int sizeCount = 0;
    Version* v = new Version;
    Statut statut;
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

        statutStr = query.value(index[8]).toString();
        if (statutStr == "enAttente") statut = enAttente;
        else if(statutStr == "enCours") statut = enCours;
        else statut = termine;

        n = new Tache(
            id,  //ID
            query.value(index[1]).toInt(),     //Version
            query.value(index[2]).toString(),  //Titre
            query.value(index[5]).toString(),  //Action
            query.value(index[6]).toInt(),     //Priorité
            QDateTime::fromString(query.value(index[7]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date d'échéance
            statut, //Statut
            QDateTime::fromString(query.value(index[3]).toString(), "dd/MM/yyyy hh:mm:ss"),    //Date de création
            QDateTime::fromString(query.value(index[4]).toString(), "dd/MM/yyyy hh:mm:ss")     //Date de modification
       );

        cout<<"Chargement de "<<id.toStdString()<<" v"<<query.value(index[1]).toInt()<<endl;
        v->addNote(n);
    }
    if (sizeCount != 0) nm.addNote(v);

    query.finish();

    return true;
}
