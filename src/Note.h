#ifndef Note_h
#define Note_h

#include <iostream>
#include <QString>
#include <QWidget>
#include <QFormLayout>
#include "Date.h"

using namespace std;
using namespace TEMPS;

enum Statut {enAttente, enCours, termine};

//Note est une classe abstraite, utilisée comme interface.
class Note {
protected:
    const QString id;
    QString titre;
    Date dateCreation;
    Date dateLastModification;
    Note(const QString i, QString t = NULL): id(i), titre(t) {}
    virtual QFormLayout* getLayout() = 0;
public:
    void setTitre(QString t) { titre = t; }
    const QString& getId() const { return id; }
    QString getTitre() const { return titre; }
    Date getDateCreat() const { return dateCreation; }
    Date getDateLastModif() const { return dateLastModification; }
    QWidget* getNoteView();
};

class Article: public Note {
private:
    QString texte;
    QFormLayout* getLayout();
public:
    Article(const QString id, QString t = NULL, QString te = NULL): Note(id, t), texte(te) {}
    void setTexte(QString t) { texte = t; }
    QString getTexte() const { return texte; }
};

class Tache: public Note {
private:
    QString action;
    int priorite;
    Date dateEcheance;
    Statut statut;
    QFormLayout* getLayout();
public:
    Tache(const QString id, QString t = NULL, QString act = NULL, int pr = 0, Date de = Date(), Statut s = enAttente):
        Note(id, t), action(act), priorite(pr), dateEcheance(de), statut(s) {}
    void setAction(QString a) { action = a; }
    void setPriorite(int p) { priorite = p; }
    void setDateEcheance(Date d) { dateEcheance = d; }
    void setStatut(Statut s) { statut = s; }
    QString getAction() const { return action; }
    int getPriorite() const { return priorite; }
    Date getDateEcheance() const { return dateEcheance; }
    Statut getStatut() const { return statut; }
};

class Media: public Note {
protected:
    QString description;
    QString filePath;
    Media(const QString id, QString t = NULL, QString desc = NULL, QString file = NULL): Note(id, t), description(desc), filePath(file) {}
    QFormLayout* getLayout();
public:
    void setDescription(QString d) { description = d; }
    void setFilePath(QString f) { filePath = f; }
    QString getDescription() const { return description; }
    QString getFilePath() const { return filePath; }
};

class Image: public Media {
public:
    Image(const QString id, QString t = NULL, QString desc = NULL, QString file = NULL): Media(id, t, desc, file) {}
};

class Audio: public Media {
public:
    Audio(const QString id, QString t = NULL, QString desc = NULL, QString file = NULL): Media(id, t, desc, file) {}
};

class Video: public Media {
public:
    Video(const QString id, QString t = NULL, QString desc = NULL, QString file = NULL): Media(id, t, desc, file) {}
};

#endif /* Note_h */
