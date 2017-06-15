#include <qxml.h>
#include <QFile>
#include "Notes.h"
#include "relations.h"
#include <QDebug>


NotesManager* NotesManager::instance = nullptr;

NotesManager::NotesManager(): tabNotes(nullptr), nbNotes(0), nbMaxNotes(0){}

NotesManager::~NotesManager(){
    SaveEverythingXML();
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

void NotesManager::deleteNote(const QString &id){
    unsigned int i;
    for(i=0; i<nbNotes && tabNotes[i]->getId() != id; i++){}
    if(nbNotes != 0 && i<nbNotes)
    {
        if(tabNotes[i]->getId() == id)
        {
            RelationManager& Rels = RelationManager::donneInstance();
            Relation& rel = Rels.getRelation("Reference");
            Relation::Iterator it = rel.getIterator();
            bool reference = false;
            while(!it.isdone())
            {
                if((*it)->gety() == id)
                    reference = true;
                it++;
            }

            if(reference)
            {
                tabNotes[i]->etat = archive;
            }
            else
            {
                tabNotes[i]->etat = corbeille;
            }
        }
    }
}

void NotesManager::deleteArchive(){
    for(unsigned int i = 0; i < nbNotes; i++)
    {
        if(tabNotes[i]->etat == archive)
        {
            deleteNote(tabNotes[i]->getId());
        }
    }
}

void NotesManager::viderCorbeille(){
    for(unsigned int i = 0; i<nbNotes; i++)
    {
        if(tabNotes[i]->etat == corbeille)
        {

            RelationManager& Rels = RelationManager::donneInstance();
            RelationManager::Iterator it = Rels.getIterator();
            while (!it.isdone()) {
                if((*it)->getTitre() != "Reference")
                {
                    Relation::Iterator itr = (*it)->getIterator();
                    while (!itr.isdone()) {
                        if((*itr)->getx() == tabNotes[i]->getId() || (*itr)->gety() == tabNotes[i]->getId())
                        {
                            (*it)->deleteCouple((*itr)->getx(),(*itr)->gety());
                        }
                        itr++;
                    }
                }
                it++;
            }
            delete tabNotes[i]->getGardien();
            delete tabNotes[i];
            tabNotes[i] = tabNotes[--nbNotes];
            i--;
        }
    }
}

void NotesManager::restaurerCorbeille(){
    for(unsigned int i = 0; i < nbNotes; i++)
    {
        if(tabNotes[i]->etat == corbeille)
        {
            tabNotes[i]->etat = active;
        }
    }
}

bool NotesManager::testCorbeille(){
    for(unsigned int i = 0; i < nbNotes; i++)
    {
        if(tabNotes[i]->etat == corbeille)
        {
            return true;
        }
    }
    return false;
}

void NotesManager::restaurerArchiveNote(const QString &id){
    unsigned int i;
    for(i = 0; i < nbNotes && tabNotes[i]->getId() != id ; i++){}
    if(nbNotes !=0 && i < nbNotes){
        if(tabNotes[i]->getId() == id)
        {
            tabNotes[i]->etat = active;
        }
    }
}

Note& NotesManager::getNote(const QString& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (tabNotes[i]->getId()==id) return *tabNotes[i];
    }
    throw NotesException(QString("Erreur, la note n'existe pas."));
}

bool NotesManager::existeNote(const QString &id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (tabNotes[i]->getId()==id) return true;
    }
    return false;
}

void NotesManager::LoadFileXML(){
    QFile fichier("PluriNotes.xml");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
    }else{
    QXmlStreamReader stream(&fichier);
    int i = -1;
    QXmlStreamReader::TokenType token;
    while(!stream.atEnd() && !stream.hasError()) {
        if(stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia"  && stream.name() != "relation") token = stream.readNext();
        if(token == QXmlStreamReader::StartDocument) continue; //continue permet d'aller directement à la fin de la boucle
        if(token == QXmlStreamReader::StartElement) {
            if(stream.name() == "PluriNotes") continue;
            if(stream.name() == "Notes") continue;
            if(stream.name() == "Relations") continue;
            if(stream.name() == "article") {
                QString id;
                QString titre;
                QString texte;
                QDateTime dateCrea;
                QDateTime dateModif;
                TypeEtatNote etat;
                //QXmlStreamAttributes attributes = stream.attributes();
                stream.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia" && stream.name() != "Notes"){
                    if(stream.tokenType() == QXmlStreamReader::StartElement) {
                        if(stream.name() == "Current")
                        {
                            while((stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia"))
                            {
                                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                    if(stream.name() == "id") {
                                        stream.readNext();
                                        id=stream.text().toString();
                                    }
                                    if(stream.name() == "titre") {
                                        stream.readNext();
                                        titre=stream.text().toString();
                                    }
                                    if(stream.name() == "texte") {
                                        stream.readNext();
                                        texte=stream.text().toString();
                                    }
                                    if(stream.name() == "dateCrea")
                                    {
                                        stream.readNext();
                                        dateCrea = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "dateModif")
                                    {
                                        stream.readNext();
                                        dateModif = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "etat") {
                                        stream.readNext();
                                        QString tempType =stream.text().toString();
                                        if(tempType == "archive")
                                            etat = archive;
                                        else
                                            etat = active;
                                    }


                                }
                                stream.readNext();
                            }
                            Article* article = new Article(id,titre,texte, dateCrea, dateModif,etat);
                            addNote(article);
                            i++;
                        }
                        if(stream.name() == "Memento")
                        {
                            while(stream.tokenType() != QXmlStreamReader::EndElement || (stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia")){
                                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                    if(stream.name() == "titre") {
                                        stream.readNext();
                                        titre=stream.text().toString();
                                    }
                                    if(stream.name() == "texte") {
                                        stream.readNext();
                                        texte=stream.text().toString();
                                    }
                                    if(stream.name() == "dateModif")
                                    {
                                        stream.readNext();
                                        dateModif = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }


                                }
                                stream.readNext();
                            }
                            Gardien* mementos = this->tabNotes[i]->getGardien();
                            Memento* memento = new MementoArticle(titre,texte,dateModif);
                            mementos->addMemento(memento);
                        }
                    }
                    stream.readNext();
                }
            }
            if(stream.name() == "tache") {
                QString id;
                QString titre;
                QDateTime dateCrea;
                QDateTime dateModif;
                QString action;
                QDateTime dateEcheance;
                TypeStatut statut;
                unsigned int priorite;
                TypeEtatNote etat;
                //QXmlStreamAttributes attributes = stream.attributes();
                stream.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(stream.name() == "article" || stream.name() == "tache" || stream.name() == "multimedia" || stream.name() == "Notes")){
                    if(stream.tokenType() == QXmlStreamReader::StartElement) {
                        if(stream.name() == "Current")
                        {
                            while((stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia"))
                            {
                                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                    if(stream.name() == "id") {
                                        stream.readNext();
                                        id=stream.text().toString();
                                    }
                                    if(stream.name() == "titre") {
                                        stream.readNext();
                                        titre=stream.text().toString();
                                    }
                                    if(stream.name() == "action") {
                                        stream.readNext();
                                        action=stream.text().toString();
                                    }
                                    if(stream.name() == "dateCrea")
                                    {
                                        stream.readNext();
                                        dateCrea = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "dateModif")
                                    {
                                        stream.readNext();
                                        dateModif = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "dateEcheance")
                                    {
                                       stream.readNext();
                                       dateEcheance = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "statut") {
                                        stream.readNext();
                                        QString tempType =stream.text().toString();
                                        if(tempType == "attente")
                                            statut = attente;
                                        else if(tempType == "cours")
                                            statut = cours;
                                        else if(tempType == "termine")
                                            statut = termine;
                                    }
                                    if(stream.name() == "priorite"){
                                        stream.readNext();
                                        priorite = stream.text().toInt();
                                    }
                                    if(stream.name() == "etat") {
                                        stream.readNext();
                                        QString tempType =stream.text().toString();
                                        if(tempType == "archive")
                                            etat = archive;
                                        else
                                            etat = active;
                                    }
                                }
                                stream.readNext();
                            }
                            Tache* tache = new Tache(id,titre,action,dateEcheance,dateCrea,dateModif,priorite,statut,etat);
                            addNote(tache);
                            i++;
                        }
                        if(stream.name() == "Memento")
                        {
                            while(stream.tokenType() != QXmlStreamReader::EndElement || (stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia")){
                                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                    if(stream.name() == "titre") {
                                        stream.readNext();
                                        titre=stream.text().toString();
                                    }
                                    if(stream.name() == "action") {
                                        stream.readNext();
                                        action=stream.text().toString();
                                    }
                                    if(stream.name() == "dateModif")
                                    {
                                        stream.readNext();
                                        dateModif = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "dateEcheance")
                                    {
                                       stream.readNext();
                                       dateEcheance = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "statut") {
                                        stream.readNext();
                                        QString tempType =stream.text().toString();
                                        if(tempType == "attente")
                                            statut = attente;
                                        else if(tempType == "cours")
                                            statut = cours;
                                        else if(tempType == "termine")
                                            statut = termine;
                                    }
                                    if(stream.name() == "priorite"){
                                        stream.readNext();
                                        priorite = stream.text().toInt();
                                    }

                                }
                                stream.readNext();
                            }
                            Gardien* mementos = this->tabNotes[i]->getGardien();
                            Memento* memento = new MementoTache(titre,action,dateModif,dateEcheance,statut,priorite);
                            mementos->addMemento(memento);
                        }
                    }
                    stream.readNext();
                }
            }
            if(stream.name() == "multimedia") {
                QString id;
                QString titre;
                QDateTime dateCrea;
                QDateTime dateModif;
                QString description;
                QString fichier;
                TypeMultimedia type;
                TypeEtatNote etat;

                //QXmlStreamAttributes attributes = stream.attributes();
                stream.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(stream.name() == "article" || stream.name() == "tache" || stream.name() == "multimedia" || stream.name() == "Notes")){
                    if(stream.tokenType() == QXmlStreamReader::StartElement) {
                        if(stream.name() == "Current")
                        {
                            while((stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia"))
                            {
                                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                    if(stream.name() == "id") {
                                        stream.readNext();
                                        id=stream.text().toString();
                                    }
                                    if(stream.name() == "titre") {
                                        stream.readNext();
                                        titre=stream.text().toString();
                                    }
                                    if(stream.name() == "description") {
                                        stream.readNext();
                                        description=stream.text().toString();
                                    }
                                    if(stream.name() == "dateCrea")
                                    {
                                        stream.readNext();
                                        dateCrea = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "dateModif")
                                    {
                                        stream.readNext();
                                        dateModif = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "type") {
                                        stream.readNext();
                                        QString tempType =stream.text().toString();
                                        if(tempType == "video")
                                            type = video;
                                        else if(tempType == "audio")
                                            type = audio;
                                        else if(tempType == "image")
                                            type = image;
                                    }
                                    if(stream.name() == "fichier"){
                                        stream.readNext();
                                        fichier = stream.text().toString();
                                    }
                                    if(stream.name() == "etat") {
                                        stream.readNext();
                                        QString tempType =stream.text().toString();
                                        if(tempType == "archive")
                                            etat = archive;
                                        else
                                            etat = active;
                                    }
                                }
                                stream.readNext();
                            }
                            Multimedia* multimedia = new Multimedia(id,titre,description,fichier,type,dateCrea,dateModif,etat);
                            addNote(multimedia);
                            i++;
                        }
                        if(stream.name() == "Memento")
                        {
                            while(stream.tokenType() != QXmlStreamReader::EndElement || (stream.name() != "Memento" && stream.name() != "article" && stream.name() != "tache" && stream.name() != "multimedia")){
                                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                                    if(stream.name() == "titre") {
                                        stream.readNext();
                                        titre=stream.text().toString();
                                    }
                                    if(stream.name() == "description") {
                                        stream.readNext();
                                        description=stream.text().toString();
                                    }
                                    if(stream.name() == "dateModif")
                                    {
                                        stream.readNext();
                                        dateModif = QDateTime::fromString(stream.text().toString(),"dd-MM-yyyy hh:mm:ss");
                                    }
                                    if(stream.name() == "type") {
                                        stream.readNext();
                                        QString tempType =stream.text().toString();
                                        if(tempType == "video")
                                            type = video;
                                        else if(tempType == "audio")
                                            type = audio;
                                        else if(tempType == "image")
                                            type = image;
                                    }
                                    if(stream.name() == "fichier"){
                                        stream.readNext();
                                        fichier = stream.text().toString();
                                    }
                                }
                                stream.readNext();
                            }
                            Gardien* mementos = this->tabNotes[i]->getGardien();
                            Memento* memento = new MementoMultimedia(titre,description,fichier,type,dateModif);
                            mementos->addMemento(memento);
                        }
                    }
                    stream.readNext();
                }
            }
            if(stream.name() == "relation"){
                RelationManager& Rels = RelationManager::donneInstance();
                Rels.LoadRelationXML(&stream);
             }
        }
    }
    // Error handling.
    if(stream.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    stream.clear();
    }
}

void NotesManager::SaveEverythingXML(){
    QFile fichier("PluriNotes.xml");
    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde articles : ouverture fichier xml"));
    QXmlStreamWriter stream(&fichier);
       stream.setAutoFormatting(true);
       stream.writeStartDocument();
       stream.writeStartElement("PluriNotes");
       stream.writeStartElement("Notes");
       for(unsigned int i=0; i<nbNotes; i++){
           if(tabNotes[i]->etat != corbeille)
           {
                this->tabNotes[i]->saveXML(&stream);
           }
       }
       stream.writeEndElement();
       RelationManager& Rels = RelationManager::donneInstance();
       Rels.saveEveryRelationsXML(&stream);
       stream.writeEndElement();
       stream.writeEndDocument();
       fichier.close();
}



void Article::saveXML(QXmlStreamWriter* stream){
    (*stream).writeStartElement("article");
    (*stream).writeStartElement("Current");
    (*stream).writeTextElement("id",this->getId()); //On utilisera un design pattern pour pas répeter l'ecriture de l'indentifiant dans les autres saves.
    (*stream).writeTextElement("titre",this->getTitre());
    (*stream).writeTextElement("dateCrea",this->dateTimeToString(this->getDateCrea()));
    (*stream).writeTextElement("dateModif",this->dateTimeToString(this->getDateModif()));
    (*stream).writeTextElement("texte",this->getTexte());
    stream->writeTextElement("etat", this->etatToString());
    (*stream).writeEndElement();
    Gardien* MementoS = this->getGardien();
    if(!MementoS->empty())
    {
        Gardien::Iterator it = MementoS->getIterator();

        while(!it.isdone())
        {
            (*it)->saveXML(stream);
            it++;
        }
    }
    (*stream).writeEndElement();
}

void Tache::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("tache");
    (*stream).writeStartElement("Current");
    (*stream).writeTextElement("id",this->getId()); //On utilisera un design pattern pour pas répeter l'ecriture de l'indentifiant dans les autres saves.
    (*stream).writeTextElement("titre",this->getTitre());
    (*stream).writeTextElement("dateCrea",this->dateTimeToString(this->getDateCrea()));
    (*stream).writeTextElement("dateModif",this->dateTimeToString(this->getDateModif()));
    (*stream).writeTextElement("action",this->getAction());
    (*stream).writeTextElement("dateEcheance",this->dateTimeToString(this->getDateEcheance()));
    (*stream).writeTextElement("statut",this->statutToString());
    (*stream).writeTextElement("priorite",QString::number(this->getPriorite()));
    stream->writeTextElement("etat", this->etatToString());
    (*stream).writeEndElement();
    Gardien* MementoS = this->getGardien();
    if(!MementoS->empty())
    {
        Gardien::Iterator it = MementoS->getIterator();

        while(!it.isdone())
        {
            (*it)->saveXML(stream);
            it++;
        }
    }
    (*stream).writeEndElement();
}


void Multimedia::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("multimedia");
    (*stream).writeStartElement("Current");
    (*stream).writeTextElement("id",this->getId());
    (*stream).writeTextElement("titre",this->getTitre());
    (*stream).writeTextElement("dateCrea",this->dateTimeToString(this->getDateCrea()));
    (*stream).writeTextElement("dateModif",this->dateTimeToString(this->getDateModif()));
    (*stream).writeTextElement("description", this->getDescription());
    (*stream).writeTextElement("fichier", this->getFicher());
    (*stream).writeTextElement("type", this->typeToString());
    stream->writeTextElement("etat", this->etatToString());
    (*stream).writeEndElement();
    Gardien* MementoS = this->getGardien();
    if(!MementoS->empty())
    {
        Gardien::Iterator it = MementoS->getIterator();

        while(!it.isdone())
        {
            (*it)->saveXML(stream);
            it++;
        }
    }
    (*stream).writeEndElement();
}


QString Note::dateTimeToString(QDateTime date) const{
    return date.toString("dd-MM-yyyy hh:mm:ss");
}

QString Note::etatToString() const{
    switch(etat){
        case 0:
            return "active";
        break;
        case 1:
            return "archive";
        break;
        case 2:
            return "corbeille";
        break;
        default:
            return "";

    }
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

/// Memento

// create
Memento* Article::createMemento() const{
    return new MementoArticle(getTitre(),texte,getDateModif());
}

Memento* Multimedia::createMemento() const{
    return new MementoMultimedia(getTitre(),description,fichier,type,getDateModif());
}

Memento* Tache::createMemento() const{
    return new MementoTache(getTitre(),action,getDateModif(),date_echeance,statut,priorite);
}

// restate
void Article::restateMemento(Memento *mem){
    MementoArticle* mem_art = dynamic_cast<MementoArticle*>(mem);
    setTitre(mem_art->getTitre());
    texte = mem_art->getTexte();
    RelationManager& RM = RelationManager::donneInstance();
    RM.updateReference(getId(), getTitre()+getTexte());
}

void Multimedia::restateMemento(Memento *mem){
    MementoMultimedia* mem_mult = dynamic_cast<MementoMultimedia*>(mem);
    setTitre( mem_mult->getTitre() );
    description = mem_mult->getDescription();
    type = mem_mult->getType();
    fichier = mem_mult->getFichier();
    RelationManager& RM = RelationManager::donneInstance();
    RM.updateReference(getId(), getTitre()+getDescription());
}

void Tache::restateMemento(Memento *mem){
    MementoTache* mem_tache = dynamic_cast<MementoTache*>(mem);
    setTitre( mem_tache->getTitre() );
    action = mem_tache->getAction();
    date_echeance = mem_tache->getEcheance();
    priorite = mem_tache->getPriorite();
    statut = mem_tache->getStatut();
    RelationManager& RM = RelationManager::donneInstance();
    RM.updateReference(getId(), getAction()+getTitre());
}


// NM - save un memento

void NotesManager::saveVersion(Note* _note) const{
    _note->gardien_note->addMemento(_note->createMemento());
}

void NotesManager::restateVersion(Note* _note, QDateTime version){
    Memento& version_note = _note->gardien_note->getMemento(version);
    _note->restateMemento(&version_note);
}

