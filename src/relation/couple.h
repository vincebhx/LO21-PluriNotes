#ifndef COUPLE_H
#define COUPLE_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QTableView>
#include <QString>
#include "../note/note.h"

class Relation;

class Couple {
private:
    QString id1;
    QString id2;
    QString label;
public:
    // -- CONSTRUCTEURS -- //
    Couple(const QString& n1, const QString& n2, const QString& l): id1(n1), id2(n2), label(l){}
    Couple(const QString& n1, const QString& n2): id1(n1), id2(n2){
        QString labelVide("");
        setLabel(labelVide);
    }
    ~Couple();

    // -- SETTERS, GETTERS -- //
    /**
     * @brief getLabel retourne le label du couple appelant.
     * @return Le label est sous forme de QString.
     */
    QString getLabel(){ return label; }
    /**
     * @brief setLabel permet de modifier le label du couple appelant.
     * @param l : QString qui sera le nouveau label du couple.
     */
    void setLabel(QString& l) { label = l; }
    /**
     * @brief getNote1 permet de récupérer l'ID de la note1 du couple.
     * @return L'ID retourné est sous forme de QString&.
     */
    QString& getNote1() { return id1; }
    /**
     * @brief getNote2 permet de récupérer l'ID de la note2 du couple.
     * @return L'ID retourné est sous forme de QString&.
     */
    QString& getNote2() { return id2; }
    /**
     * @brief getNotes permet de récupérer les ID des notes du couple.
     * @return Les notes sont sous forme de vecteur de QString.
     */
    std::vector<QString> getNotes();

    // -- RECUPERATION DES DONNEES DANS LA BDD -- //
    /**
     * @brief getTableModel permet d'interroger la base de données.
     * @param db il s'agit de la base de données à interroger.
     * @return Renvoie un objet QSqlTableModel avec tous les résultats apportés par la base de données.
     */
    static QSqlTableModel* getTableModel(QSqlDatabase db);
    /**
     * @brief getCoupleView permet de mettre en forme des résultats.
     * @param table : pointeur sur l'objet contenant les résultats.
     * @return Renvoie un objet QTableView donnant la mise en forme des résultats.
     */
    static QTableView* getCoupleView(QSqlTableModel *table);

    /**
     * @brief getInsertQuery permet de récupérer une requête d'insertion de couple.
     * @param r : pointeur de la relation dans laquelle sera insérée le couple.
     * @return Retourne la requête sous forme de QSqlQuery.
     */
    QSqlQuery getInsertQuery(Relation* r);
    /**
     * @brief geDeleteQuery permet de récupérer une requête de suppression de couple dans la base de données.
     * @param r : pointeur de la relation de laquelle sera supprimé le couple.
     * @return Retourne la requête sous forme de QSqlQuery.
     */
    QSqlQuery getDeleteQuery(Relation* r);
};

#endif // COUPLE_H
