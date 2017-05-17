//
//  Notes.h
//  LO21-PluriNotes
//
//  Created by Vincent Baheux on 17/05/2017.
//  Copyright © 2017 Vincent Baheux. All rights reserved.
//

#ifndef Notes_h
#define Notes_h

#include <iostream>
#include "Temps.h"

using namespace std;
using namespace TEMPS;

namespace NOTES {
    
    class Note {
    protected:
        const string id;
        string titre;
        Date dateCreation;
        Date dateLastModification;
        Note(const string i, string t = NULL): id(i), titre(t) {}
    public:
        void setTitre(string t) { titre = t; }
        const string& getId() const { return id; }
        string getTitre() const { return titre; }
        Date getDateCreat() const { return dateCreation; }
        Date getDateLastModif() const { return dateLastModification; }
    };
    
    class Article: public Note {
    private:
        string texte;
    public:
        Article(const string id, string ti = NULL, string te = NULL): Note(id, ti), texte(te) {}
        void setTexte(string t) { texte = t; }
        string getTexte() const { return texte; }
    };

}

#endif /* Notes_h */
