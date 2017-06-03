#include "Memento.h"


void MementoArticle::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("Memento");
        //(*stream).writeTextElement("DateModif",this->getDateModif());
    (*stream).writeTextElement("titre",this->getTitle());
    (*stream).writeTextElement("texte",this->getTexte());
    (*stream).writeEndElement();

}

void MementoMultimedia::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("Memento");
    //(*stream).writeTextElement("DateModif",this->getDateModif());
    (*stream).writeTextElement("titre",this->getTitle());
    (*stream).writeTextElement("description",this->getDescription());

    (*stream).writeEndElement();

}

void MementoTache::saveXML(QXmlStreamWriter *stream){
    (*stream).writeStartElement("Memento");
    //(*stream).writeTextElement("DateModif",this->getDateModif());
    (*stream).writeTextElement("titre",this->getTitle());
    (*stream).writeTextElement("description",this->getAction());

    (*stream).writeEndElement();

}
