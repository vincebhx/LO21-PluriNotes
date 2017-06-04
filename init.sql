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
  dateEcheance TEXT,
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

INSERT INTO Article VALUES ("article1", 1, "c++", "26/05/2017 11:00:00", "26/05/2017 10:00:00", "coder en c++ v1");
INSERT INTO Article VALUES ("article1", 2, "c++", "26/05/2017 12:00:00", "26/05/2017 10:00:00", "coder en c++ v2");
INSERT INTO Article VALUES ("article1", 3, "c++", "26/05/2017 13:00:00", "26/05/2017 10:00:00", "coder en c++ v3");
INSERT INTO Article VALUES ("article1", 4, "c++", "26/05/2017 14:00:00", "26/05/2017 10:00:00", "coder en c++ v4");

INSERT INTO Article VALUES ("article2", 1, "js", "28/05/2017 11:00:00", "26/05/2017 10:00:00", "coder en js v1");
INSERT INTO Article VALUES ("article2", 2, "js", "28/05/2017 12:00:00", "26/05/2017 10:00:00", "coder en js v2");

INSERT INTO Tache VALUES ("tache1", 1, "toto", "26/05/2017 10:00:00", "27/05/2017 10:00:00", "coder en c++", 42, "28/05/2017 10:00:00", "enCours");
INSERT INTO Tache VALUES ("tache1", 3, "toto", "26/05/2017 10:00:00", "27/05/2017 10:00:00", "coder en c++", 42, "28/05/2017 10:00:00", "enCours");
INSERT INTO Tache VALUES ("tache1", 2, "toto", "26/05/2017 10:00:00", "27/05/2017 10:00:00", "coder en c++", 42, "28/05/2017 10:00:00", "enCours");
INSERT INTO Tache VALUES ("tache1", 4, "toto", "26/05/2017 10:00:00", "27/05/2017 10:00:00", "coder en c++", 42, "28/05/2017 10:00:00", "enCours");

INSERT INTO Tache VALUES ("tache2", 1, "toto", "26/05/2017 10:00:00", "27/05/2017 10:00:00", "coder en js", 42, "28/05/2017 10:00:00", "enCours");
INSERT INTO Tache VALUES ("tache2", 2, "toto", "26/05/2017 10:00:00", "27/05/2017 10:00:00", "coder en js", 42, "28/05/2017 10:00:00", "enCours");

INSERT INTO Media VALUES ("audio1", 1, "audio", "Stardust - Music Sounds Better With You", "28/05/2017 10:00:00", "29/05/2017 10:00:00", "Le hit de l'année 1997 !", "/Users/vbaheux/Documents/stardust.mp3");


SELECT * FROM Tache ORDER BY id, version ASC;
