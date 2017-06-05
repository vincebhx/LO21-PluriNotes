#include "relation.h"
#include "../note/note.h"
#include "couple.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <iostream>

using namespace std;

/*void Relation::loadRelations() {
    QSqlQuery query("SELECT * FROM Relation ORDER BY titre ASC");

    int titre = query.record().indexOf("titre");
    int description = query.record().indexOf("description");
    int oriente = query.record().indexOf("oriente");

    while (query.next())
    {
        cout<<"Chargement de la relation"<<query.value(titre).toString().toStdString()<<endl;

        Article* rel = new Relation(
            query.value(titre).toString(),
            query.value(description).toString(),
            query.value(oriente).toInt()
        );
####### AJOUTER RELATION DANS LE RELATION MANAGER #######
        rel->addNote(a);
    }
}

void Relation::addCouple(QPair c){
    if (nbCouples == nbMaxCouples){
        nbMaxCouples += 5;
        QPair* newCouples = new QPair [nbMaxCouples];
        for (unsigned int i = 0; i < nbCouples; i++){
            newCouples[i] = couples[i];
        }
        QPair* oldCouples = couples;

        couples = newCouples;

        if (oldCouples){
            delete[] oldCouples;
        }
    }
    couples[nbCouples++] = &c;
}
*/
