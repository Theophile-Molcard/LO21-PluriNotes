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

bool RelationManager::existeRelation(QString _titre){
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabRelations[i]->getTitre()==_titre) return true;
    }
    return false;
}

void RelationManager::deleteRelation(QString _titre){
    if(_titre == "Reference") throw("erreur, on ne peut supprimer la relation Reference.");
    unsigned int i;
    for(i=0; i<nbRelations && tabRelations[i]->getTitre() != _titre; i++){}
    if(nbRelations != 0 && i <nbRelations)
    {
        if(tabRelations[i]->getTitre() == _titre)
        {
            delete tabRelations[i];
            tabRelations[i] = tabRelations[--nbRelations];
        }
    }
}

void RelationManager::saveEveryRelationsXML(QXmlStreamWriter *stream){
    stream->writeStartElement("Relations");
    for(unsigned int i=0; i<nbRelations; i++){
        this->tabRelations[i]->saveXML(stream);
    }
    stream->writeEndElement();
}

void RelationManager::createReference(){
    qDebug() << "aaaaaaaaaaaaaaaaaaaa";
    for(unsigned int i=0; i <nbRelations; i++){
        qDebug() << getRelation("Reference").getTitre();
        qDebug() << tabRelations[i]->getTitre();
        if(tabRelations[i]->getTitre() == "Reference")
            throw NotesException("erreur, Reference existe déjà");
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
    Relation* rel = new Relation("Reference", "relations fortes");
    tabRelations[nbRelations++] = rel;
}

bool RelationManager::updateReference(const QString &idNote, const QString &texte){
    NotesManager& NM = NotesManager::donneInstance();
    if(NM.existeNote(idNote))
    {
        bool suite = true;
        QRegExp regex("\\\\ref[{]([\\w]+)[}]");
        QStringList list;
        int pos = 0;
        while( (pos = regex.indexIn(texte, pos)) != -1){
            if(NM.existeNote(regex.cap(1)) && regex.cap(1) != idNote)
            {
                qDebug() << "lololo";
                qDebug() << regex.cap(1);
                list << regex.cap(1);
            }
            else
            {
                suite = false;
            }
            pos += regex.matchedLength();
        }
        if(suite)
        {
            Relation& reference = getRelation("Reference");
            Relation::Iterator it2 = reference.getIterator();
            while (!it2.isdone()) {
                qDebug() << "oo";
                qDebug() << (*it2)->getx();
                if((*it2)->getx() == idNote)
                {
                    reference.deleteCouple((*it2)->getx(), (*it2)->gety());
                }
                it2++;
            }

            QStringList::iterator it = list.begin();
            while (it != list.end()) {
                qDebug() << (*it);
                reference.addCouple(idNote, (*it));
                ++it;
            }
            return true;
        }
        else
        {
           return false;
        }
    }
    else
    {
        return false;
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
    if(!notes.existeNote(_x) || !notes.existeNote(_y)){
        throw NotesException("erreur, un des id n'existe pas");
    }
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
    for(i=0; i<nbCouples && ((tabCouples[i]->getx() != _x) || (tabCouples[i]->gety() != _y)); i++){}
    if(nbCouples != 0 && i < nbCouples)
    {
        qDebug() <<tabCouples[i]->getx();
        qDebug() << tabCouples[i]->gety();
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
Couple& Relation::getCouple(QString _x, QString _y){
    for(unsigned int i=0; i<nbCouples; i++){
        if (tabCouples[i]->getx()==_x && tabCouples[i]->gety() == _y) return *tabCouples[i];
    }
    throw NotesException(QString("Erreur, le couple n'existe pas."));
}

bool Relation::existeCouple(QString _x, QString _y){
    for(unsigned int i=0; i <nbCouples; i++){
        if(tabCouples[i]->getx() == _x && tabCouples[i]->gety() == _y) return true;
    }
    return false;
}

void Relation::saveXML(QXmlStreamWriter *stream){
    stream->writeStartElement("relation");
    stream->writeTextElement("titre", this->getTitre());
    stream->writeTextElement("description", this->getDescription());
    stream->writeTextElement("orientee", QString::number(this->orientee));
    stream->writeStartElement("Couples");

    if(!orientee)
    {
        bool existe = false;
        QVector<QString> listeX;
        QVector<QString> listeY;
        for(unsigned int i = 0; i<nbCouples; i++)
        {
            existe = false;
            for (int j = 0; j < listeX.size(); j++) {
                if(tabCouples[i]->getx() == listeY.at(j) && tabCouples[i]->gety() == listeX.at(j))
                {
                    existe = true;
                }
            }
            if(!existe)
            {
                this->tabCouples[i]->saveXML(stream);
                listeX << tabCouples[i]->getx();
                listeY << tabCouples[i]->gety();
            }
        }

    }
    else
    {
        for(unsigned int i=0; i<nbCouples; i++)
        {
            this->tabCouples[i]->saveXML(stream);
        }
    }

    stream->writeEndElement();
}

void Couple::saveXML(QXmlStreamWriter *stream){
     stream->writeStartElement("couple");
     stream->writeTextElement("x", this->getx());
     stream->writeTextElement("y", this->gety());
     stream->writeTextElement("label", this->getLabel());
     (*stream).writeEndElement();
}

void RelationManager::LoadRelationXML(QXmlStreamReader *stream){
    unsigned int j = 0;
    qDebug()<<"new relation\n";
    QString titre;
    QString description;
    bool orientee;
    QString x;
    QString y;
    QString label;

    //QXmlStreamAttributes attributes = stream.attributes();
    stream->readNext();
    while(!(stream->tokenType() == QXmlStreamReader::EndElement && ( stream->name() == "relation" || stream->name() == "Relations" || stream->name() == "PluriNotes" &&  stream->name() != "Couples"))){
        qDebug()<<stream->name();
        if(stream->tokenType() == QXmlStreamReader::StartElement) {
            if(stream->name() == "titre"){
                stream->readNext();
                titre=stream->text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }
            if(stream->name() == "description"){
                stream->readNext();
                description=stream->text().toString();
                qDebug()<<"desc="<<description<<"\n";
            }
            if(stream->name() == "orientee"){
                stream->readNext();
                orientee=stream->text().toInt();
                qDebug()<<"orientee="<<QString::number(orientee)<<"\n";
                if(titre =="Reference")
                {
                    this->createReference();
                    qDebug() << "llll";
                }
                else{
                    Relation* rel = new Relation(titre,description, orientee);
                    addRelation(rel);
                }
                j++;
            }
            if(stream->name() == "couple"){
                 while(stream->tokenType() != QXmlStreamReader::EndElement || (stream->name() != "couple" && stream->name() != "relation" && stream->name() != "Relations" && stream->name() != "PluriNotes" && stream->name() != "Couples")){
                     qDebug() <<"Couple";
                     qDebug() << stream->name();
                     if(stream->tokenType() == QXmlStreamReader::StartElement) {
                         qDebug() << "coucou";
                         if(stream->name() == "x" )
                         {
                             stream->readNext();
                             x=stream->text().toString();
                             qDebug()<<"x="<<x<<"\n";
                         }
                         if(stream->name() == "y" )
                         {
                             stream->readNext();
                             y=stream->text().toString();
                             qDebug()<<"y="<<y<<"\n";
                         }
                         if(stream->name() == "label" )
                         {
                             stream->readNext();
                             label=stream->text().toString();
                             qDebug()<<"label="<<label<<"\n";
                         }

                     }
                        stream->readNext();
                 }
                  qDebug() << x;
                  qDebug() << y;
                  qDebug() << label;
                tabRelations[j-1]->addCouple(x,y,label);
            }
        }
        stream->readNext();
    }
}




