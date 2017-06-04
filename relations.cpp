#include "relations.h"
#include "Notes.h"
#include <QDebug>

Relation::~Relation(){
    for(unsigned int i=0; i<nbCouples; i++) delete tabCouples[i];
    delete[] tabCouples;
}

void Relation::addCouple(QString _x, QString _y){
    for(unsigned int i=0; i <nbCouples; i++){
        if(tabCouples[i]->getx() == _x && tabCouples[i]->gety() == _y)
            throw NotesException("erreur, couple existe déjà");
    }
    //NotesManager& notes = NotesManager::donneInstance();
    //notes.getNote(_x); //à modifier, pour l'instant on compte sur le fait que getNote envoie une erreur si la note existe pas (très moche)
    //notes.getNote(_y);
    if(nbCouples == nbMaxCouples){
        Couple** newCouples = new Couple*[nbMaxCouples+5];
        for(unsigned int i=0; i<nbCouples; i++)
            newCouples[i] = tabCouples[i];
        Couple** oldCouples = tabCouples;
        tabCouples = newCouples;
        nbMaxCouples+=5;
        if(oldCouples) delete[] oldCouples;
    }
    Couple* couple = new Couple(_x,_y);
    tabCouples[nbCouples++] = couple;
    /*if(!orientee){
        addCouple(_y,_x);
    }*/
}

void Relation::deleteCouple(QString _x, QString _y){
    unsigned int i;
    for(i=0; i<nbCouples && (tabCouples[i]->getx() != _x) && (tabCouples[i]->gety() != _y); i++){}
    if(tabCouples[i]->getx() == _x && tabCouples[i]->gety() == _y)
    {
        delete tabCouples[i];
        tabCouples[i] = tabCouples[--nbCouples];
        /*if(!orientee)
        {
            deleteCouple(_y,_x);
        }*/
    }

}

