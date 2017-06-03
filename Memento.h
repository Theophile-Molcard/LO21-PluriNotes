#ifndef MEMENTO_H
#define MEMENTO_H

#include<QStack>
#include<QDateTime>
#include <QXmlStreamWriter>

using namespace std;
enum TypeMultimedia;

class MementoException{ // je ne pouvais pas inclure notes ici car memento inclu dans notes
public:
    MementoException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


class Memento{
public:
    QString getTitle() const { return title; }

    const QDateTime& getDateModif() const { return date_modif; }
    Memento(QString _title) // il faut voir pour la version
        : title(_title)
    {
        date_modif=QDateTime::currentDateTime();
    }

    virtual ~Memento() {}
    virtual void saveXML(QXmlStreamWriter* stream) = 0;

private:
    QString title;
    QDateTime date_modif;

};

class MementoArticle : public Memento{
public:
    MementoArticle(QString _title, QString _texte)
        : Memento(_title)
    {
        texte = _texte;
    }

    QString getTexte() const {return texte;}
    virtual void saveXML(QXmlStreamWriter* stream);

private:
    QString texte;
};



class MementoTache : public Memento{
public:
    MementoTache(QString _title, QString _action, QDateTime _date_echeance, unsigned int _priorite = 0, unsigned int _statut = 1 )
        : Memento(_title), action(_action), priorite(_priorite), date_echeance(_date_echeance), statut(_statut){}

    MementoTache(QString _title, QString _action, unsigned int _priorite = 0, unsigned int _statut = 1 )
        : Memento(_title), action(_action), priorite(_priorite), statut(_statut)
    {
        QDateTime a;
        a.addDays(0);
        date_echeance = a; // à revoir...
    }

    QString getAction() const {return action;}
    unsigned int getPriorite() const {return priorite;}
    QDateTime getEcheance() const {return date_echeance;}
    unsigned int getStatut() const {return statut;}

    virtual void saveXML(QXmlStreamWriter* stream);
private:
    QString action;
    unsigned int priorite; // optionnel
    QDateTime date_echeance; //optionnel
    unsigned int statut;

};



class MementoMultimedia : public Memento{
public:
    MementoMultimedia(QString _title, QString _description, QString _fichier, unsigned int _type)
        : Memento(_title), description(_description), fichier(_fichier), type(_type){}

    QString getDescription() const {return description;}
    QString getFichier() const {return fichier;}
    unsigned int getType() const {return type;}

    virtual void saveXML(QXmlStreamWriter* stream);
private:
    QString description;
    QString fichier; // adresse du fichier
    unsigned int type; //type du fichier
};



// classes filles de memento


class Gardien{
public:

    Gardien(){
    }

    Gardien(Memento* mem){
        pileMemento.push(mem);
    }

    void addMemento(Memento* mem){
        pileMemento.push(mem);
    }

    Memento* getMemento(int version){ // voir comment gérer les versions...
        if(version > pileMemento.size()){
            MementoException error = MementoException("Dépassement de Pille");
            throw error;
        }
        else{
            for(int i = 0 ; i < version ; i++)
                pileMemento.pop();
        }

        return pileMemento.top();

    }

    Memento* popMemento(){
        return pileMemento.pop();
    }

    unsigned int sizeMemento(){
        return pileMemento.size();
    }

    bool empty(){
        return pileMemento.empty();
    }

private:
    QStack<Memento*> pileMemento;

};


#endif // MEMENTO_H
