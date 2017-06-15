#ifndef VERSIONINDEX_H
#define VERSIONINDEX_H

#include "note.h"

typedef std::vector<Note*>::iterator VersionIterator;

class VersionIndex
{
private:
    /**
     * @brief versions contient les pointeurs sur Note* corespondant aux différentes versions d'un même document.
     */
    std::vector<Note*> versions;
    unsigned short etat;
public:
    VersionIndex() {}
    /**
     * @brief VersionIndex est le constructeur de classe.
     * @param n
     */
    VersionIndex(Note* n);

    /**
     * @brief getEtat récupère l'état du document dans le NotesManager (Active, Archivée, Supprimée)
     * @return Retour sous forme d'unsigned short.
     */
    unsigned short& getEtat() { return etat; }
    /**
     * @brief setEtat donne un nouvel état à VersionIndex.
     * @param i : nouvel état à assigner.
     */
    void setEtat(unsigned short i) { etat = i; }

    /**
     * @brief firstVersion renvoie la première version d'un document.
     * @return La première version créée d'un document.
     */
    Note* firstVersion() { return versions.front(); }
    /**
     * @brief currentVersion renvoie la version actuelle d'un document.
     * @return Retour sous forme de Note*
     */
    Note* currentVersion() { return versions.back(); }
    /**
     * @brief at Permet de retourner la version se trouvant à la position donnée en paramètre dans le vecteur de VersionIndex.
     * @param version : Position de la Note à renvoyer.
     * @return Retour sous forme de Note*
     */
    Note* at(unsigned int version) { return versions.at(version); }

    VersionIterator begin() { return versions.begin(); }
    VersionIterator end() { return versions.end(); }
    /**
     * @brief nbOfVersions: nombre de versions d'une note
     * @return Retour sous forme d'unsigned int.
     */
    unsigned int nbOfVersions() { return versions.size(); }
    /**
     * @brief addVersion : permet de rajouter une version
     * @param n : Note correspondant à la nouvelle version.
     */
    void addVersion(Note* n);
};

#endif // VERSIONINDEX_H
