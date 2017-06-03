#include <qxml.h>
#include <QFile>
#include "Notes.h"

NotesManager* NotesManager::instance = nullptr;

NotesManager::NotesManager(): tabNotes(nullptr), nbNotes(0), nbMaxNotes(0){}

NotesManager::~NotesManager(){
    //à rajouter la sauvegarde des notes (automatique ?)
    for(unsigned int i=0; i<nbNotes; i++) delete tabNotes[i];
        delete[] tabNotes;
}

void NotesManager::addNote(Note* n){
    for(unsigned int i=0; i<nbNotes; i++){
        if (tabNotes[i]->getId()==n->getId()) throw NotesException("erreur, creation d'une note avec un id deja existant");
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes = new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=tabNotes[i];
        Note** oldNotes=tabNotes;
        tabNotes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    tabNotes[nbNotes++]= n;
}

Note& NotesManager::getNote(const QString& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (tabNotes[i]->getId()==id) return *tabNotes[i];
    }
    throw NotesException(QString("Erreur, la note n'existe pas."));
}

void NotesManager::SaveEverythingXML(){
    QFile fichier("test_notes.xml");
    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde articles : ouverture fichier xml"));
    QXmlStreamWriter stream(&fichier);
       stream.setAutoFormatting(true);
       stream.writeStartDocument();
       stream.writeStartElement("Notes");
       for(unsigned int i=0; i<nbNotes; i++){
           this->tabNotes[i]->saveXML(&stream); // Je tente un truc
       }
       stream.writeEndElement();
       stream.writeEndDocument();
       fichier.close();
}


void Article::saveXML(QXmlStreamWriter* stream){
    (*stream).writeStartElement("article");
    (*stream).writeTextElement("id",this->getId()); //On utilisera un design pattern pour pas répeter l'ecriture de l'indentifiant dans les autres saves.
    (*stream).writeTextElement("titre",this->getTitre());
    (*stream).writeTextElement("texte",this->getTexte());
    (*stream).writeEndElement();
}

void Tache::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("tache");
    (*stream).writeTextElement("id",this->getId()); //On utilisera un design pattern pour pas répeter l'ecriture de l'indentifiant dans les autres saves.
    (*stream).writeTextElement("titre",this->getTitre());
    (*stream).writeTextElement("action",this->getAction());
    (*stream).writeTextElement("statut",this->statutToString());
    (*stream).writeTextElement("priorite",QString::number(this->getPriorite()));
    (*stream).writeEndElement();
}

QString Tache::statutToString(){
    switch(statut){
        case 0:
            return "attente";
        break;
        case 1:
            return "cours";
        break;
        case 2:
            return "termine";
        break;
        default:
            return "";

    }
}

QString Multimedia::typeToString(){
    switch(type){
        case 0:
            return "video";
        break;
        case 1:
            return "audio";
        break;
        case 2:
            return "image";
        break;
        default:
            return "";
   }

}

void Multimedia::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("multimedia");
    (*stream).writeTextElement("id",this->getId());
    (*stream).writeTextElement("titre",this->getTitre());
    (*stream).writeTextElement("description", this->getDescription());
    (*stream).writeEndElement();
}



/// Memento

Memento* Article::createMemento() const{
    return new MementoArticle( Note::getTitre(), texte );
}

Memento* Multimedia::createMemento() const{
    return new MementoMultimedia( Note::getTitre(), description, fichier, 124578); // remplacer 124578 par indice du type
}

Memento* Tache::createMemento() const{
    return new MementoTache( Note::getTitre(), action, date_echeance, priorite, 124578); // remplacer 124578 par indice du type
}

