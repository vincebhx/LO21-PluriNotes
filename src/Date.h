#ifndef Date_h
#define Date_h

#include <iostream>
#include <QString>
#include <QDateTime>

using namespace std;

namespace TEMPS {
    
    class TimeException{
    private:
        QString info;
    public:
        TimeException(const QString& s): info("Erreur : " + s) {}
        const QString& getInfo() const { return info; }
    };
    
    class Date {
    private:
        unsigned short int jour;
        unsigned short int mois;
        unsigned int annee;
        unsigned short int heure;
        unsigned short int minute;
        unsigned short int seconde;
        
    public:
        Date(unsigned int short j = 1, unsigned int short m = 1, unsigned int a=  0,
             unsigned short int h = 0, unsigned short int min = 0, unsigned short int s = 0)
        : jour(1), mois(1), annee(0), heure(0), minute(0), seconde(0) { setDate(j, m, a, h, min, s); }

        unsigned short int getSec() const { return seconde; }
        unsigned short int getMin() const { return minute; }
        unsigned short int getHeure() const { return heure; }
        unsigned short int getJour() const { return jour; }
        unsigned short int getMois() const { return mois; }
        unsigned int getAnnee() const { return annee; }
        
        void setDate(unsigned short int j,
                     unsigned short int m,
                     unsigned int a,
                     unsigned short int h,
                     unsigned short int min,
                     unsigned short int s);
        
        void afficher(std::ostream& f=std::cout) const;
        string toString() const;
        QDateTime toQDateTime();
    };
    
    ostream& operator<<(ostream& f, const Date& d);
}

#endif /* Date_h */
