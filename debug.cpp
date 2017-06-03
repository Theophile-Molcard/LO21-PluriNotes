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

    notes.addNote(&copain);
    NotesManager::Iterator it = notes.getIterator();
    qDebug() << (*it)->getId();

    qDebug() << notes.getNote("super").getDateModif();
    notes.SaveEverything();
}

void DebugTest::Debug_theophile(){

    A a(1);
    B b(10,20);
    A* pointeur_a = &b;

    B* pointeur_b = dynamic_cast<B*>(pointeur_a);

}

