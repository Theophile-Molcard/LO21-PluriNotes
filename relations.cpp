#include "relations.h"
#include "Notes.h"
#include <QDebug>

RelationManager* RelationManager::instance = nullptr;

RelationManager::RelationManager(): tabRelations(nullptr), nbRelations(0), nbMaxRelations(0){}

RelationManager::~RelationManager(){
    for(unsigned int i=0; i<nbRelations; i++) delete tabRelations[i];
    delete[] tabRelations;
}

void RelationManager::addRelation(Relation* rel){
    if(rel->getTitre() == "Reference") throw("erreur, on ne peut ajouter une relation Reference. ");
    for(unsigned int i=0; i <nbRelations; i++){
        if(tabRelations[i]->getTitre() == rel->getTitre())
            throw NotesException("erreur, relation existe déjà");
    }
    if(nbRelations == nbMaxRelations){
        Relation** newRelations = new Relation*[nbMaxRelations+5];
        for(unsigned int i=0; i<nbRelations; i++)
            newRelations[i] = tabRelations[i];
        Relation** oldRelations = tabRelations;
        tabRelations = newRelations;
        nbMaxRelations+=5;
        if(oldRelations) delete[] oldRelations;
    }
    tabRelations[nbRelations++] = rel;
}

Relation& RelationManager::getRelation(QString _titre){
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabRelations[i]->getTitre()==_titre) return *tabRelations[i];
    }
    throw NotesException(QString("Erreur, la relation n'existe pas."));
}

void RelationManager::deleteRelation(QString _titre){
    if(_titre == "Reference") throw("erreur, on ne peut supprimer la relation Reference.");
    unsigned int i;
    for(i=0; i<nbRelations && tabRelations[i]->getTitre() == _titre; i++){}
    if(nbRelations != 0)
    {
        if(tabRelations[i]->getTitre() == _titre)
        {
            delete tabRelations[i];
            tabRelations[i] = tabRelations[--nbRelations];
        }
    }
}

Relation::~Relation(){
    for(unsigned int i=0; i<nbCouples; i++) delete tabCouples[i];
    delete[] tabCouples;
}

void Relation::addCouple(QString _x, QString _y, QString _label){
    bool stop = false;
    for(unsigned int i=0; i <nbCouples; i++){
        if(tabCouples[i]->getx() == _x && tabCouples[i]->gety() == _y)
            throw NotesException("erreur, couple existe déjà");
        if(tabCouples[i]->getx() == _y && tabCouples[i]->gety() == _x)
            stop = true;
    }
    NotesManager& notes = NotesManager::donneInstance();
    notes.getNote(_x); //à modifier, pour l'instant on compte sur le fait que getNote envoie une erreur si la note existe pas (très moche)
    notes.getNote(_y);
    if(nbCouples == nbMaxCouples){
        Couple** newCouples = new Couple*[nbMaxCouples+5];
        for(unsigned int i=0; i<nbCouples; i++)
            newCouples[i] = tabCouples[i];
        Couple** oldCouples = tabCouples;
        tabCouples = newCouples;
        nbMaxCouples+=5;
        if(oldCouples) delete[] oldCouples;
    }
    Couple* couple = new Couple(_x,_y,_label);
    tabCouples[nbCouples++] = couple;
    if(!orientee && !stop){
        addCouple(_y,_x, _label);
    }
}

void Relation::deleteCouple(QString _x, QString _y){
    unsigned int i;
    for(i=0; i<nbCouples && (tabCouples[i]->getx() != _x) && (tabCouples[i]->gety() != _y); i++){}
    if(nbCouples != 0)
    {
        if(tabCouples[i]->getx() == _x && tabCouples[i]->gety() == _y)
        {
            delete tabCouples[i];
            tabCouples[i] = tabCouples[--nbCouples];
            if(!orientee)
            {
                deleteCouple(_y,_x);
            }
        }
    }
}

