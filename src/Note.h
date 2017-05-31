#ifndef Note_h
#define Note_h

#include <iostream>
#include <Qt>
#include <QString>
#include <QWidget>
#include <QDateTime>
#include <QSqlQuery>
#include <QFormLayout>
#include "Date.h"

using namespace std;
using namespace TEMPS;

enum Statut {enAttente, enCours, termine};

///Décrit une Note (interface, classe abstraite)
class Note {
protected:
    const QString id;
    unsigned int version;
    QString titre;
    const QDateTime dateCreation;
    QDateTime dateLastModification;

    virtual QFormLayout* getLayout() = 0;
    Note(const QString i, unsigned int vers = 0, QString t = NULL,
         QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        id(i), version(vers), titre(t), dateCreation(creat), dateLastModification(modif) {}
    virtual QSqlQuery prepareQuery() = 0;
public:
    static const QString dateFormat;

    void setTitre(QString t) { titre = t; }
    void setVersion(unsigned int i) { version = i; }

    const QString& getId() const { return id; }
    QString getTitre() const { return titre; }
    unsigned int getVersion() const { return version; }
    const QDateTime& getDateCreat() const { return dateCreation; }
    QDateTime getDateLastModif() const { return dateLastModification; }
    QWidget* getNoteView();
    QSqlQuery getQuery();
};

///Décrit un Article
class Article: public Note {
private:
    QString texte;
    QFormLayout* getLayout();
    QSqlQuery prepareQuery();
public:
    Article(const QString id, unsigned int version = 0, QString t = NULL, QString te = NULL,
            QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Note(id, version, t, creat, modif), texte(te) {}
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
    QSqlQuery prepareQuery();
public:
    Tache(const QString id, unsigned int version = 0, QString t = NULL, QString act = NULL, int pr = 0, Date de = Date(), Statut s = enAttente,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Note(id, version, t, creat, modif), action(act), priorite(pr), dateEcheance(de), statut(s) {}
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
    Media(const QString id, unsigned int version = 0, QString t = NULL, QString desc = NULL, QString file = NULL,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Note(id, version, t, creat, modif), description(desc), filePath(file) {}
    QFormLayout* getLayout();
    QSqlQuery prepareQuery();
public:
    void setDescription(QString d) { description = d; }
    void setFilePath(QString f) { filePath = f; }
    QString getDescription() const { return description; }
    QString getFilePath() const { return filePath; }
    virtual QString typeToString() const = 0;
};

///Décrit une image
class Image: public Media {
public:
    Image(const QString id, unsigned int version = 0, QString t = NULL, QString desc = NULL, QString file = NULL,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Media(id, version, t, desc, file, creat, modif) {}
    QString typeToString() const { return "image"; }
};

///Décrit un fichier audio
class Audio: public Media {
public:
    Audio(const QString id, unsigned int version = 0, QString t = NULL, QString desc = NULL, QString file = NULL,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Media(id, version, t, desc, file, creat, modif) {}
    QString typeToString() const { return "audio"; }
};

///Décrit un fichier vidéo
class Video: public Media {
public:
    Video(const QString id, unsigned int version = 0, QString t = NULL, QString desc = NULL, QString file = NULL,
          QDateTime creat = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime()):
        Media(id, version, t, desc, file, creat, modif) {}
    QString typeToString() const { return "video"; }
};

#endif /* Note_h */
