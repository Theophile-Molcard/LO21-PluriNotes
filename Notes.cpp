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



/// Memento

// create
Memento* Article::createMemento() const{
    return new MementoArticle( Note::getTitre(), texte );
}

Memento* Multimedia::createMemento() const{
    return new MementoMultimedia( Note::getTitre(), description, fichier, 124578); // remplacer 124578 par indice du type
}

Memento* Tache::createMemento() const{
    return new MementoTache( Note::getTitre(), action, date_echeance, priorite, 124578); // remplacer 124578 par indice du type
}

// restate
void Article::restateMemento(Memento *mem){
    MementoArticle* mem_art = dynamic_cast<MementoArticle*>(mem);
    setTitre(mem_art->getTitle());
    texte = mem_art->getTexte();
}

void Multimedia::restateMemento(Memento *mem){
    MementoMultimedia* mem_mult = dynamic_cast<MementoMultimedia*>(mem);
    setTitre( mem_mult->getTitle() );
    description = mem_mult->getDescription();
    //type = mem_mult->getType(); getType renvoie un indice
    fichier = mem_mult->getFichier();

}

void Tache::restateMemento(Memento *mem){
    MementoTache* mem_tache = dynamic_cast<MementoTache*>(mem);
    setTitre( mem_tache->getTitle() );
    action = mem_tache->getAction();
    date_echeance = mem_tache->getEcheance();
    priorite = mem_tache->getPriorite();
    //statut = mem_tache->getStatut();
}


// NM - save un memento

void NotesManager::saveVersion(Note* _note) const{
    _note->gardien_note->addMemento(_note->createMemento());
}

void NotesManager::restateVersion(Note* _note, unsigned int version){
    Memento* version_note;
    version_note = _note->gardien_note->getMemento(version);
    _note->restateMemento(version_note);
}

