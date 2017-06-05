#include <QtDebug>
#include "debug.h"
#include "Notes.h"
#include "relations.h"
//Fichier debug pour le mode console





//Exemple d'utilisation

void DebugTest::Debug()
{

    NotesManager& notes = NotesManager::donneInstance();
    //notes.LoadFileXML();
    Article* copain = new Article("super","c'est la base", "La destruction de la planète est en marche");
    qDebug() << copain->getTexte();
    qDebug() << copain->getDateCrea();
    qDebug() << "Oui ca marche !!";

    QDate date1(2016,6,3);
    QDate date2(2019,12,3);
    QDate date3(2018,6,3);
    QTime heure(10,00);
    Tache* copainT1 = new Tache("encore", "Ta poule1", "manger", QDateTime(date1,heure), 2, attente);
    Tache* copainT2 = new Tache("a", "Ta poule2", "manger", QDateTime(date2,heure), 1, termine);
    Tache* copainT3 = new Tache("e", "Ta poule3", "manger", QDateTime(date3,heure), 1, attente);

    Article* copain2 = new Article("je", "suis", "voué à être supprimé");


    Multimedia* copainM = new Multimedia("Ainsi", "va la vie", "Chaque jour passe" , "C:/dossierX", video);
    notes.addNote(copain);
    notes.addNote(copainT1);
    notes.addNote(copainT2);
    notes.addNote(copainT3);
    notes.addNote(copainM);
    notes.addNote(copain2);

    RelationManager& Rels= RelationManager::donneInstance();
    Rels.createReference();
    Rels.getRelation("Reference").addCouple("encore", "super");
    Relation* rel = new Relation("cool", "a la vie comme a la mort");
    rel->addCouple("je", "encore");
    Rels.addRelation(rel);

    notes.saveVersion(copain);

    copain->setTitre("NOOOOOOO!");

    notes.saveVersion(copain);

    copain->setTitre("OUIIIII!");

    notes.deleteNote("super");
    qDebug() << "suppr 1";
    qDebug() << notes.getNote("super").etatToString();
    qDebug() << "suppr 2";
    notes.deleteNote("je");
    qDebug() << notes.getNote("je").etatToString();

    notes.viderCorbeille();

    NotesManager::Iterator it = notes.getIterator();
    while (!it.isdone()) {
        qDebug() << (*it)->getId();
        it++;
    }

    qDebug() << notes.getNote("super").getDateModif();

}

void DebugTest::DebugRelation(){

    NotesManager& notes = NotesManager::donneInstance();
    Relation* rela = new Relation("Copain", "on s'amuse");
    rela->addCouple("encore","Ainsi");
    rela->addCouple("super", "encore");
    Relation::Iterator it = rela->getIterator();
    qDebug() << rela->getDescription();
    while(!it.isdone())
    {
        qDebug() << (*it)->getx();
        qDebug() << (*it)->gety();
        it++;
    }
    //rela->deleteCouple("encore", "Ainsi");

    Relation* relaNonOriente = new Relation("Exact", "Faux", false);
    relaNonOriente->addCouple("encore", "Ainsi");
    relaNonOriente->addCouple("super", "encore");
    Relation::Iterator it2 = relaNonOriente->getIterator();
    while(!it2.isdone())
    {
        qDebug() << (*it2)->getx();
        qDebug() << (*it2)->gety();
        it2++;
    }
    qDebug() << "delete";
   // relaNonOriente->deleteCouple("encore", "Ainsi");
    Relation::Iterator it3 = relaNonOriente->getIterator();
    while(!it3.isdone())
    {
        qDebug() << (*it3)->getx();
        qDebug() << (*it3)->gety();
        it3++;
    }

    RelationManager& Rels = RelationManager::donneInstance();

    Rels.addRelation(rela);
    Rels.addRelation(relaNonOriente);
    qDebug() << Rels.getRelation("Copain").getTitre();

    notes.SaveEverythingXML();
   /* RelationManager& Rels = RelationManager::donneInstance();
    RelationManager::Iterator it5 = Rels.getIterator();
    while (!it5.isdone()) {
        Relation::Iterator itr = (*it5)->getIterator();
        qDebug() << (*it5)->getTitre();
        while (!itr.isdone()) {
            qDebug() << (*itr)->getx();
            qDebug() << (*itr)->gety();
            itr++;
        }
        it5++;
    }*/


}

void DebugTest::Debug_theophile(){

    NotesManager& notes = NotesManager::donneInstance();
    //notes.LoadFileXML();
    Article *copain = new Article("super","c'est la base", "La destruction de la planète est en marche");

    Article *copainA2 = new Article("a1","check", "La destruction de la planète est en marche");

    Article *copainA3 = new Article("a2","Elizabetheeee !!! ", "La destruction de la planète est en marche");

    QDate date(2017,6,3);
    QTime heure(10,00);


    Tache *copainT= new Tache("encore", "Ta poule", "manger", QDateTime(date,heure), 2, attente);

    Multimedia *copainM= new Multimedia("Ainsi", "va la vie", "Chaque jour passe" , "C:/dossierX", video);
    notes.addNote(copain);
    notes.addNote(copainA2);
    notes.addNote(copainA3);

    notes.addNote(copainT);
    notes.addNote(copainM);

    notes.saveVersion(copainT);
    copainT->setAction("VOLER VERS L'INFINI ET L'AU DELA");
    copainT->setPriority(5);
    copainT->setTitre("n'oublie pas les pommes");
    copainT->setStatut(termine);

    notes.saveVersion(copain);

    copain->setTitre("NOOOOOOO!");

    notes.saveVersion(copain);

    copain->setTitre("OUIIIII!");


}

