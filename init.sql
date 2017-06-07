PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
DROP TABLE RelationNote;
DROP TABLE Relation;
DROP TABLE Media;
DROP TABLE Tache;
DROP TABLE Article;

CREATE TABLE Article(
  etat INT NOT NULL DEFAULT 0,
  id TEXT NOT NULL,
  version INT NOT NULL,
  titre TEXT,
  dateCreation TEXT,
  dateModification TEXT,
  texte TEXT,
  PRIMARY KEY (id, version),
  CHECK(etat IN (0, 1, 2))
);
INSERT INTO Article VALUES(0, 'article1',1,'c++','26/05/2017 11:00:00','26/05/2017 10:00:00','coder en c++ v1');
INSERT INTO Article VALUES(0, 'article1',2,'c++','26/05/2017 12:00:00','26/05/2017 10:00:00','coder en c++ v2');
INSERT INTO Article VALUES(0, 'article1',3,'c++','26/05/2017 13:00:00','26/05/2017 10:00:00','coder en c++ v3');
INSERT INTO Article VALUES(0, 'article1',4,'c++','26/05/2017 14:00:00','26/05/2017 10:00:00','coder en c++ v4');
INSERT INTO Article VALUES(0, 'article2',1,'js','28/05/2017 11:00:00','26/05/2017 10:00:00','coder en js v1');
INSERT INTO Article VALUES(0, 'article2',2,'js','28/05/2017 12:00:00','26/05/2017 10:00:00','coder en js v2');
CREATE TABLE Tache(
  etat INT NOT NULL,
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
  CHECK(etat IN (0, 1, 2)),
  CHECK (statut IN ("enAttente", "enCours", "termine"))
);
INSERT INTO Tache VALUES(0,'tache1',1,'toto','26/05/2017 10:00:00','27/05/2017 10:00:00','coder en c++',42,'28/05/2017 10:00:00','enAttente');
INSERT INTO Tache VALUES(0,'tache1',3,'toto','26/05/2017 10:00:00','27/05/2017 10:00:00','coder en c++',42,'28/05/2017 10:00:00','enCours');
INSERT INTO Tache VALUES(0,'tache1',2,'toto','26/05/2017 10:00:00','27/05/2017 10:00:00','coder en c++',42,'28/05/2017 10:00:00','enCours');
INSERT INTO Tache VALUES(0,'tache1',4,'toto','26/05/2017 10:00:00','27/05/2017 10:00:00','coder en c++',42,'28/05/2017 10:00:00','enCours');
INSERT INTO Tache VALUES(0,'tache2',1,'toto','26/05/2017 10:00:00','27/05/2017 10:00:00','coder en js',42,'28/05/2017 10:00:00','enCours');
INSERT INTO Tache VALUES(0,'tache2',2,'toto','26/05/2017 10:00:00','27/05/2017 10:00:00','coder en js',42,'28/05/2017 10:00:00','termine');
CREATE TABLE Media(
  etat INT NOT NULL,
  id TEXT NOT NULL,
  version INT NOT NULL,
  type TEXT,
  titre TEXT,
  dateCreation TEXT,
  dateModification TEXT,
  description TEXT,
  filePath TEXT,
  PRIMARY KEY (id, version),
  CHECK(etat IN (0, 1, 2)),
  CHECK(type IN ("image", "audio", "video"))
);
INSERT INTO Media VALUES(0, 'audio1',1,'audio','Stardust - Music Sounds Better With You','28/05/2017 10:00:00','29/05/2017 10:00:00','Le premier hit de l''année 1997 !','/Users/vbaheux/Documents/stardust.mp3');
INSERT INTO Media VALUES(0, 'audio1',2,'audio','Stardust - Music Sounds Better With You','28/05/2017 10:00:00','29/05/2017 10:00:00','Le deuxième hit de l''année 1997 ! (finalement Mariah Carey était devant)','/Users/vbaheux/Documents/stardust.mp3');
INSERT INTO Media VALUES(0, 'image1',1,'image','Patate','28/05/2017 10:00:00','29/05/2017 10:00:00','Une photo de patate en qualité 4K.','/Users/vbaheux/Documents/patate.jpeg');
INSERT INTO Media VALUES(0, 'image1',2,'image','Patate','28/05/2017 10:00:00','29/05/2017 11:00:00','Une photo de patate en qualité 4K version 2 tavu.','/Users/vbaheux/Documents/patate.jpeg');
INSERT INTO Media VALUES(0, 'video1',1,'video','Lolcat','28/05/2017 10:00:00','29/05/2017 10:00:00','Internet was made for cats.','/Users/vbaheux/Documents/lolcat.avi');
INSERT INTO Media VALUES(0, 'video1',2,'video','Lolcat','28/05/2017 10:00:00','29/05/2017 11:00:00','Internet was made for cats, right ?','/Users/vbaheux/Documents/lolcat.avi');
CREATE TABLE Relation(
  titre TEXT PRIMARY KEY,
  description TEXT,
  oriente INT NOT NULL,
  CHECK (oriente IN (0, 1))
);
INSERT INTO Relation VALUES('mon apprentissage du c++','pour m aider a apprendre le c++',1);
INSERT INTO Relation VALUES('mon contenu internet de qualite','garder les contenus cool que je trouve',0);
CREATE TABLE RelationNote(
  relation TEXT,
  note1 TEXT NOT NULL,
  note2 TEXT NOT NULL,
  label TEXT,
  PRIMARY KEY (relation, note1, note2)
);
INSERT INTO RelationNote VALUES('mon apprentissage du c++','article1','tache1', 'digerer toutes ces infos');
INSERT INTO RelationNote VALUES('mon contenu internet de qualite','image1','video1', 'categorie extra drole');
COMMIT;
