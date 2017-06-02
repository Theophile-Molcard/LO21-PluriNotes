#include <QtDebug>
#include "debug.h"
#include "Notes.h"

//Fichier debug pour le mode console





//Exemple d'utilisation

void DebugTest::Debug()
{
    Article copain("super","c'est la base", "La destruction de la planète est en marche");
    qDebug() << copain.getTexte();
    qDebug() << copain.getDateCrea();
    qDebug() << "Oui ca marche !!";

}


