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

    QDate date(2017,6,3);
    QTime heure(10,00);
    Tache* copainT = new Tache("encore", "Ta poule", "manger", QDateTime(date,heure), 2, attente);

    Multimedia* copainM = new Multimedia("Ainsi", "va la vie", "Chaque jour passe" , "C:/dossierX", video);
    notes.addNote(copain);
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


    NotesManager::Iterator it = notes.getIterator();
    qDebug() << (*it)->getId();

    qDebug() << notes.getNote("super").getDateModif();
    notes.SaveEverythingXML();
}

void DebugTest::DebugRelation(){

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
    rela->deleteCouple("encore", "Ainsi");

    Relation* relaNonOriente = new Relation("Exact", "Faux", false);
    relaNonOriente->addCouple("encore", "Ainsi");
    Relation::Iterator it2 = relaNonOriente->getIterator();
    while(!it2.isdone())
    {
        qDebug() << (*it2)->getx();
        qDebug() << (*it2)->gety();
        it2++;
    }
    qDebug() << "delete";
    relaNonOriente->deleteCouple("encore", "Ainsi");
    Relation::Iterator it3 = relaNonOriente->getIterator();
    while(!it3.isdone())
    {
        qDebug() << (*it3)->getx();
        qDebug() << (*it3)->gety();
        it3++;
    }

    RelationManager& Rels = RelationManager::donneInstance();

    Rels.addRelation(rela);
    qDebug() << Rels.getRelation("Copain").getTitre();


}

void DebugTest::Debug_theophile(){

    NotesManager& notes = NotesManager::donneInstance();
    //notes.LoadFileXML();
    Article *copain = new Article("super","c'est la base", "La destruction de la planète est en marche");

    QDate date(2017,6,3);
    QTime heure(10,00);
    Tache *copainT= new Tache("encore", "Ta poule", "manger", QDateTime(date,heure), 2, attente);

    Multimedia *copainM= new Multimedia("Ainsi", "va la vie", "Chaque jour passe" , "C:/dossierX", video);
    notes.addNote(copain);
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

