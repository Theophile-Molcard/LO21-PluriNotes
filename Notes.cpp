#include <qxml.h>
#include <QFile>
#include "Notes.h"

//NotesManager::NotesManager(): tabNotes(nullptr), nbNotes(0), nbMaxNotes(0){}

/*NotesManager::~NotesManager(){
    //à rajouter la sauvegarde des notes (automatique ?)
    for(unsigned int i=0; i<nbNotes; i++) delete tabNotes[i];
        delete[] tabNotes;
}*/

void NotesManager::SaveEverything(){
    QFile fichier("test_notes.xml");
    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde articles : ouverture fichier xml"));
    QXmlStreamWriter stream(&fichier);
       stream.setAutoFormatting(true);
       stream.writeStartDocument();
       stream.writeStartElement("Notes");
       for(unsigned int i=0; i<nbNotes; i++){
           this->tabNotes[i]->save(&stream); // Je tente un truc
       }
       stream.writeEndElement();
       stream.writeEndDocument();
       fichier.close();
}


void Article::save(QXmlStreamWriter* stream){
    (*stream).writeStartElement("article");
    (*stream).writeTextElement("id",this->getId()); //On utilisera un design pattern pour pas répeter l'ecriture de l'indentifiant dans les autres saves.
    (*stream).writeTextElement("titre",this->getTitre());
    (*stream).writeTextElement("texte",this->getTexte());
    (*stream).writeEndElement();
}

void Multimedia::save(QXmlStreamWriter *stream){
    (*stream).writeStartElement("multimedia");
    (*stream).writeTextElement("id",this->getId());
    (*stream).writeTextElement("titre",this->getTitre());
    (*stream).writeTextElement("description", this->getDescription());
    (*stream).writeEndElement();
}
