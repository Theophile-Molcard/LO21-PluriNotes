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

    notes.addNote(&copain);
    notes.addNote(&copainT);
    NotesManager::Iterator it = notes.getIterator();
    qDebug() << (*it)->getId();

    qDebug() << notes.getNote("super").getDateModif();
    notes.SaveEverythingXML();
}


