//
//  Temps.cpp
//  LO21-PluriNotes
//
//  Created by Vincent Baheux on 17/05/2017.
//  Copyright © 2017 Vincent Baheux. All rights reserved.
//

#include <iomanip>
#include "Temps.h"

using namespace std;

namespace TEMPS {
    void Date::setDate(unsigned short int j, unsigned short int m, unsigned int a,
                       unsigned short int h, unsigned short int min, unsigned short int s) {
        if (a <= 3000) annee = a; else throw TimeException("année invalide");
        if (1 <= m && m <= 12) mois = m; else throw TimeException("mois invalide");
        switch (m) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if (1 <= j && j <= 31) jour = j; else throw TimeException("jour invalide");
                break;
            case 4: case 6: case 9: case 11:
                if (1 <= j && j <= 30) jour = j; else throw TimeException("jour invalide");
                break;
            case 2:
                if (1 <= j && (j <= 28 || (j == 29 && ((a%4==0 && a%100!=0) || a%400 == 0)))) jour = j;
                else throw TimeException("jour invalide");
                break;
        }
        if (0 <= h && h <= 23) heure = h; else throw TimeException("heure invalide");
        if (0 <= min && min <= 59) minute = min; else throw TimeException("minute invalide");
        if (0 <= s && s <= 59) seconde = s; else throw TimeException("seconde invalide");
    }
    
    void Date::afficher(ostream& f) const {
        f<<setfill('0')<<setw(2)<<jour<<"/"<<setw(2)<<mois<<"/"<<annee<<" "
        <<setw(2)<<heure<<":"<<setw(2)<<minute<<":"<<setw(2)<<seconde<<setfill(' ');
    }
    
    ostream& operator<<(ostream& f, const Date& d){ d.afficher(f); return f; }
}
