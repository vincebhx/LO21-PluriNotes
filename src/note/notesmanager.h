#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "versionindex.h"
#include "./src/relation/relationsmanager.h"

typedef std::vector<VersionIndex*>::iterator NMIterator;
typedef enum { ACTIVES = 0, ARCHIVES = 1, CORBEILLE = 2 } Etat;
static const QString stateString[3] = {"actives", "archives", "corbeille"};

class NotesManager
{
private:
    /**
     * @brief Ensemble des notes actives.
     */
    std::vector<VersionIndex*> actives;
    /**
     * @brief Ensemble des notes archivées.
     */
    std::vector<VersionIndex*> archives;
    /**
     * @brief Ensemble des notes dans la corbeille
     */
    std::vector<VersionIndex*> corbeille;

    /**
     * @brief Instance unique du NotesManager (Singleton)
     */
    static NotesManager* _instance;
    /**
     * @brief Constructeur privé (appelé dans instance() si besoin)
     */
    NotesManager();
    ///Destructeur
    ~NotesManager();

    /**
     * @brief toEtat : convertit un entier en variable de type Etat.
     * @param i : entier à convertir.
     * @return Retourne la conversion en Etat (0 = ACTIVES, 1 = ARCHIVES, 2 = CORBEILLE)
     */
    static Etat toEtat(int i) { return static_cast<Etat>(i); }

public:
    /**
     * @brief instance : accesseur à l'instance unique de NotesManager (Singleton).
     * @return Retourne une référence vers l'instance unique de NotesManager.
     */
    static NotesManager& instance();
    /**
     * @brief free : Fonction à appeler en fin de programme pour libérer la mémoire.
     *
     * Appelle le destructeur de NotesManager.
     */
    void free();

    /**
     * @brief indexId
     */
    std::vector<QString> indexId; // TOUS LES ID DE TOUTES LES NOTES

    /**
     * @brief findVersionIndex
     * @param id
     * @return
     */
    VersionIndex* findVersionIndex(QString id);

    /**
     * @brief findNote
     * @param id
     * @return
     */
    Note* findNote(QString id);

    /**
     * @brief getIndexId
     * @param id
     * @return
     */
    int getIndexId(QString id);

    /**
     * @brief getSizeIndexId
     * @return
     */
    int getSizeIndexId() { return indexId.size(); }

    /**
     * @brief currentVersion : trouve la dernière version du dernier VersionIndex de l'état choisi en paramètre.
     * @param e : état choisi par l'utilisateur.
     * @return Retourne un pointeur vers la dernière note de l'état choisi.
     */
    Note* currentVersion(Etat e) {
        switch(e) {
        case ACTIVES: return actives.back()->currentVersion();
        case ARCHIVES: return archives.back()->currentVersion();
        case CORBEILLE: return corbeille.back()->currentVersion();
        }
    }
    /**
     * @brief currentNote : trouve le dernier VersionIndex de l'état choisi en paramètre.
     * @param e : état choisi par l'utilisateur.
     * @return Retourne un pointeur vers la dernière note de l'état choisi.
     */
    VersionIndex* currentNote(Etat e) {
        switch(e) {
        case ACTIVES: return actives.back();
        case ARCHIVES: return archives.back();
        case CORBEILLE: return corbeille.back();
        }
    }

    /**
     * @brief begin : surcharge de la méthode begin() de chaque état.
     * @param e : état choisi par l'utilisateur.
     * @return Retourne un itérateur pointant sur le premier élément de l'état choisi.
     */
    NMIterator begin(Etat e) {
        switch(e) {
        case ACTIVES: return actives.begin();
        case ARCHIVES: return archives.begin();
        case CORBEILLE: return corbeille.begin();
        }
    }
    /**
     * @brief end : surcharge de la méthode end() de chaque état.
     * @param e : état choisi par l'utilisateur.
     * @return Retourne un itérateur pointant sur une case fictive après le dernier élément de l'état choisi.
     */
    NMIterator end(Etat e) {
        switch(e) {
        case ACTIVES: return actives.end();
        case ARCHIVES: return archives.end();
        case CORBEILLE: return corbeille.end();
        }
    }

    /**
     * @brief nbNotes : surcharge de la méthode size() de chaque état.
     * @param e : état choisi par l'utilisateur.
     * @return Retourne le nombre d'éléments VersionIndex de l'état choisi.
     */
    unsigned int nbNotes(Etat e) {
        switch(e) {
        case ACTIVES: return actives.size();
        case ARCHIVES: return archives.size();
        case CORBEILLE: return corbeille.size();
        }
    }

    /**
     * @brief load : Charge les données des notes présentes dans la BDD.
     *
     * Récupère l'ensemble des notes dans la base de données, et les place à leurs emplacements respectif dans le NotesManager.
     */
    void load();

    /**
     * @brief addNote : ajoute un nouvel élément v dans l'état e.
     * @param e : état choisi par l'utilisateur.
     * @param v : Index de versions à ajouter dans le NotesManager.
     */
    void addNote(Etat e, VersionIndex* v);

    /**
     * @brief changeState : déplace l'index de versions vIndex de son état courant vers l'état targetState et met à jour la BDD en conséquence.
     * @param targetState : état cible choisi par l'utilisateur.
     * @param vIndex : index de versions à déplacer.
     */
    void changeState(Etat targetState, VersionIndex* vIndex);

    /**
     * @brief deleteNote : si v est dans la corbeille, le supprime totalement du NotesManager et de la BDD.
     * @param v : index de versions à supprimer.
     */
    void deleteNote(VersionIndex* v);

    /**
     * @brief getNote : Permet de trouver l'index de versions actif situé à la position i.
     * @param i : position de l'index de versions.
     * @return Retourne un pointeur vers le VersionIndex à la position i.
     */
    VersionIndex* getNote(int i) { return actives[i]; }

    /**
     * @brief getAscendants
     * @param note
     * @param relation
     * @return
     */
    std::vector<QString> getAscendants(Note* note, Relation* relation);

    /**
     * @brief getDescendants
     * @param note
     * @param relation
     * @return
     */
    std::vector<QString> getDescendants(Note* note, Relation* relation);

    /**
     * @brief getTasks
     * @return
     */
    std::vector<VersionIndex*> getTasks();
};

#endif // NOTESMANAGER_H
