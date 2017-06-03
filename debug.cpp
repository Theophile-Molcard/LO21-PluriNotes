#include <QtDebug>
#include "debug.h"
#include "Notes.h"

//Fichier debug pour le mode console





//Exemple d'utilisation

void DebugTest::Debug()
{
    NotesManager& notes = NotesManager::donneInstance();

    Article copain("super","c'est la base", "La destruction de la planète est en marche");
    qDebug() << copain.getTexte();
    qDebug() << copain.getDateCrea();
    qDebug() << "Oui ca marche !!";



    QDate date(2017,6,3);
    QTime heure(10,00);
    Tache copainT("encore", "Ta poule", "manger", QDateTime(date,heure), 2, attente);

    Multimedia copainM("Ainsi", "va la vie", "Chaque jour passe" , "C:/dossierX", video);
    notes.addNote(&copain);
    notes.addNote(&copainT);
    notes.addNote(&copainM);

    notes.saveVersion(&copainT);
    copainT.setAction("VOLER VERS L'INFINI ET L'AU DELA");
    copainT.setPriority(5);
    copainT.setTitre("n'oublie pas les pommes");
    copainT.setStatut(termine);

    notes.saveVersion(&copain);

    copain.setTitre("NOOOOOOO!");

    notes.saveVersion(&copain);

    copain.setTitre("OUIIIII!");


    NotesManager::Iterator it = notes.getIterator();
    qDebug() << (*it)->getId();

    qDebug() << notes.getNote("super").getDateModif();
    notes.SaveEverythingXML();
}

void DebugTest::Debug_theophile(){

    A a(1);
    B b(10,20);
    A* pointeur_a = &b;

    B* pointeur_b = dynamic_cast<B*>(pointeur_a);

}

