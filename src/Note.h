#ifndef Note_h
#define Note_h

#include <iostream>
#include <Qt>
#include <QString>
#include <QWidget>
#include <QDateTime>
#include <QFormLayout>
#include "Date.h"

using namespace std;
using namespace TEMPS;

enum Statut {enAttente, enCours, termine};

///Décrit une Note (interface, classe abstraite)
class Note {
protected:
    const QString id;
    QString titre;
    const QDateTime dateCreation;
    QDateTime dateLastModification;

    virtual QFormLayout* getLayout() = 0;
    Note(const QString i, QString t = NULL): id(i), titre(t), dateCreation(QDateTime::currentDateTime()) {
        dateLastModification = dateCreation;
    }
public:
    static const QString dateFormat;

    void setTitre(QString t) { titre = t; }

    const QString& getId() const { return id; }
    QString getTitre() const { return titre; }
    const QDateTime& getDateCreat() const { return dateCreation; }
    QDateTime getDateLastModif() const { return dateLastModification; }
    QWidget* getNoteView();
};

///Décrit un Article
class Article: public Note {
private:
    QString texte;
    QFormLayout* getLayout();
public:
    Article(const QString id, QString t = NULL, QString te = NULL): Note(id, t), texte(te) {}
    void setTexte(QString t) { texte = t; }
    QString getTexte() const { return texte; }
};

///Décrit une Tâche
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

///Décrit un Média
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

///Décrit une image
class Image: public Media {
public:
    Image(const QString id, QString t = NULL, QString desc = NULL, QString file = NULL): Media(id, t, desc, file) {}
};

///Décrit un fichier audio
class Audio: public Media {
public:
    Audio(const QString id, QString t = NULL, QString desc = NULL, QString file = NULL): Media(id, t, desc, file) {}
};

///Décrit un fichier vidéo
class Video: public Media {
public:
    Video(const QString id, QString t = NULL, QString desc = NULL, QString file = NULL): Media(id, t, desc, file) {}
};

#endif /* Note_h */
