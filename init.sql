-- Commande : .read init.sql --

DROP TABLE RelationNote;
DROP TABLE Relation;
DROP TABLE Media;
DROP TABLE Tache;
DROP TABLE Article;

CREATE TABLE Article(
  id TEXT NOT NULL,
  version INT NOT NULL,
  titre TEXT,
  dateCreation TEXT,
  dateModification TEXT,
  texte TEXT,
  PRIMARY KEY (id, version)
);

CREATE TABLE Tache(
  id TEXT NOT NULL,
  version INT NOT NULL,
  titre TEXT,
  dateCreation TEXT,
  dateModification TEXT,
  action TEXT,
  priorite INT,
  statut VARCHAR(9),
  PRIMARY KEY (id, version),
  CHECK (statut IN ("enAttente", "enCours", "termine"))
);

CREATE TABLE Media(
  id TEXT NOT NULL,
  version INT NOT NULL,
  type TEXT,
  titre TEXT,
  dateCreation TEXT,
  dateModification TEXT,
  description TEXT,
  filePath TEXT,
  PRIMARY KEY (id, version),
  CHECK(type IN ("image", "audio", "video"))
);

CREATE TABLE Relation(
  titre TEXT NOT NULL,
  description TEXT,
  oriente INT,
  CHECK (oriente IN (0, 1))
);

CREATE TABLE RelationNote(
  relation TEXT NOT NULL,
  note1 TEXT NOT NULL,
  note2 TEXT NOT NULL,
  PRIMARY KEY (relation, note1, note2)
);

INSERT INTO Tache VALUES ("tache1", 1, "toto", "aujourdhui", "aujourdhui", "coder en c++", 42, "enCours");
