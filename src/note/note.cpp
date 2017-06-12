#include "note.h"
#include "notesmanager.h"
#include "./src/relation/relationsmanager.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

const QString Note::dateDisplayFormat = "ddd dd MMMM yyyy à hh:mm:ss";
const QString Note::dateStorageFormat = "dd/MM/yyyy hh:mm:ss";

QWidget* Note::getNoteView() {
    QWidget* view = new QWidget;

    //Date de création
    QLabel* dateCreatEdit = new QLabel(dateCreation.toString(dateDisplayFormat));

    //Date de modification
    QLabel* dateModifEdit = new QLabel(dateModification.toString(dateDisplayFormat));

    //Titre
    QLineEdit* titreEdit = new QLineEdit(titre);
    titreEdit->setFixedWidth(300);

    //Layout
    QFormLayout* formLayout = getLayout();
    formLayout->insertRow(0, "Identificateur", new QLabel(id, view));
    formLayout->insertRow(1, "Version", new QLabel(QString::number(version), view));
    formLayout->insertRow(2, "Création", dateCreatEdit);
    formLayout->insertRow(3, "Dernière modification", dateModifEdit);
    formLayout->insertRow(4, "Titre", titreEdit);
    formLayout->setHorizontalSpacing(10);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addItem(formLayout);

    //Bouton
    QPushButton* saveButton = new QPushButton("Sauver", view);
    layout->addWidget(saveButton);
    //Le slot saveNote() n'est pas encore défini
    //QObject::connect(saveButton, SIGNAL(clicked()), view, SLOT(saveNote()));

    //Vue et retour
    view->setLayout(layout);
    return view;
}

QSqlQuery Note::getQuery() {
    QSqlQuery query = prepareQuery();
    query.bindValue(":etat", parent->getEtat());
    query.bindValue(":id", id);
    query.bindValue(":version", version);
    query.bindValue(":titre", titre);
    query.bindValue(":dateCreation", dateCreation.toString(dateStorageFormat));
    query.bindValue(":dateModification", dateModification.toString(dateStorageFormat));
    return query;
}

void Note::arborescences(std::vector< std::vector<int> > visite){
    // -- LA MATRICE VISITE EVITE LA REDONDANCE DES LIENS DANS LES ARBORESCENCES -- //
    NotesManager& nm = NotesManager::instance();

    // -- A-T-ON TOUT DEJA VISITE ? -- //
    bool empty = true;
    for (int i = 0; i < visite.size(); i++){
        for (int j = 0; j < visite.size(); j++){
            if (visite[i][j] != 0) empty = false;
        }
    }

    if (!empty){
        std::vector<int> descendants;
        std::vector<int> ascendants;
        int noteDeDepart = nm.getIndexId(this->getId());

        // -- MISE A JOUR DE VISITE : ETUDE DES ASCENDANTS/DESCENDANTS DIRECT -- //
        for (int i = 0; i < visite.size(); i++){
            if (visite[noteDeDepart][i] == 1){
                descendants.push_back(i);
                visite[noteDeDepart][i] = 0;
            }
            if (visite[i][noteDeDepart] == 1){
                ascendants.push_back(i);
                visite[i][noteDeDepart] = 0;
            }
        }

        for (unsigned int j = 0; j < descendants.size(); j++){
            QString IdNoteDescendante = nm.indexId[j];
            Note* NoteDescendante = nm.findNote(IdNoteDescendante);
            NoteDescendante->arborescences(visite);
            // -- ETUDE DES ARBORESCENCES PROPRES AUX DESCENDANTS -- //
        }

        for (unsigned int j = 0; j < descendants.size(); j++){
            QString IdNoteAscendante = nm.indexId[j];
            Note* NoteAscendante = nm.findNote(IdNoteAscendante);
            NoteAscendante->arborescences(visite);
            // -- ETUDE DES ARBORESCENCES PROPRES AUX ASCENDANTS -- //
        }
   } // -- FIN IF !EMPTY -- //
    // -- IF EMPTY : FIN DE LA RECUSION -- //
}

void Note::getArborescences(){
    NotesManager& nm = NotesManager::instance();
    int taille = nm.getSizeIndexId();
    RelationsManager& rm = RelationsManager::instance();
    std::vector< std::vector<int> > visite;

    for (RMIterator RMit = rm.begin(); RMit != rm.end(); RMit++){
        for (unsigned int i = 0; i < taille; i++){
            for (unsigned int j = 0; j < taille; j++){
                visite[i][j] = (*RMit)->matriceAdjacence[i][j];
            }
        }
        this->arborescences(visite);
    }
}

