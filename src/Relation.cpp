#include "Relation.h"
#include "Note.h"
#include "Couple.h"
#include <iostream>

using namespace std;

void Relation::addCouple(Couple& c){
    if (nbCouples == nbMaxCouples){
        nbMaxCouples += 5;
        Couple** newCouples = new Couple* [nbMaxCouples];
        for (unsigned int i = 0; i < nbCouples; i++){
            newCouples[i] = couples[i];
        }
        Couple** oldCouples = couples;

        couples = newCouples;

        if (oldCouples){
            delete[] oldCouples;
        }
    }
    couples[nbCouples++] = &c;
}
