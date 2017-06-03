#include "Memento.h"


void MementoArticle::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("Memento");
    (*stream).writeTextElement("DateModif",this->dateToString(this->getDateModif()));
    (*stream).writeTextElement("titre",this->getTitle());
    (*stream).writeTextElement("texte",this->getTexte());
    (*stream).writeEndElement();

}

void MementoMultimedia::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("Memento");
    (*stream).writeTextElement("DateModif",this->dateToString(this->getDateModif()));
    (*stream).writeTextElement("titre",this->getTitle());
    (*stream).writeTextElement("description",this->getDescription());
    (*stream).writeTextElement("fichier",this->getFichier());
    (*stream).writeTextElement("type",this->typeToString());
    (*stream).writeEndElement();

}

void MementoTache::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("Memento");
    (*stream).writeTextElement("DateModif",this->dateToString(this->getDateModif()));
    (*stream).writeTextElement("titre",this->getTitle());
    (*stream).writeTextElement("action",this->getAction());
    (*stream).writeTextElement("dateEcheance",this->dateToString(this->getEcheance()));
    (*stream).writeTextElement("priorite",QString::number(this->getPriorite()));
    (*stream).writeTextElement("statut",this->statutToString());
    (*stream).writeEndElement();

}

QString MementoTache::statutToString(){
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

QString MementoMultimedia::typeToString(){
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
