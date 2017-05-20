#include "Relation.h"
#include "Note.h"
#include <iostream>

using namespace std;

void Relation::addCouple(Note* note1, Note* note2){
    if (nbCouples == nbMaxCouples){
        nbMaxCouples += 5;
        Note** newNotesX = new Note* [nbMaxCouples];
        Note** newNotesY = new Note* [nbMaxCouples];
        for (unsigned int i = 0; i < nbCouples; i++){
            newNotesX[i] = notesX[i];
            newNotesY[i] = notesY[i];
        }
        Note** oldNotesX = notesX;
        Note** oldNotesY = notesY;

        notesX = newNotesX;
        notesY = newNotesY;

        if (oldNotesX && oldNotesY){
            delete[] oldNotesX;
            delete[] oldNotesY;
        }
    }
    nbCouples++;
    notesX[nbCouples] = note1;
    notesY[nbCouples] = note2;
};
