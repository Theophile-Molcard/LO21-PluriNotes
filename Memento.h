#ifndef MEMENTO_H
#define MEMENTO_H

#include<QList>
#include<iterator>
#include<QDateTime>
#include <QXmlStreamWriter>

using namespace std;
enum TypeMultimedia{video, audio, image};
enum TypeStatut{attente, cours, termine};
enum TypeEtatNote{active,archive,corbeille};


/// ------ Note Exception ------ ///


class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


class Memento{
public:
    QString getTitre() const { return titre; }


    const QDateTime& getDateModif() const { return date_modif; }
    Memento(QString _titre) // il faut voir pour la version
        : titre(_titre)
    {
        date_modif=QDateTime::currentDateTime();
    }
    Memento(QString _titre, QDateTime _dateModif): titre(_titre), date_modif(_dateModif){}

    virtual ~Memento() {}
    virtual void saveXML(QXmlStreamWriter* stream) = 0;

    QString dateToString(QDateTime date){
        return date.toString("dd-MM-yyyy hh:mm:ss");
    }

private:
    QString titre;
    QDateTime date_modif;

};

class MementoArticle : public Memento{
public:
    MementoArticle(QString _titre, QString _texte)
        : Memento(_titre)
    {
        texte = _texte;
    }
    MementoArticle(QString _titre, QString _texte, QDateTime _dateModif): Memento(_titre,_dateModif), texte(_texte){}

    QString getTexte() const {return texte;}
    virtual void saveXML(QXmlStreamWriter* stream);

private:
    QString texte;
};



class MementoTache : public Memento{
public:
    MementoTache(QString _titre, QString _action, QDateTime _date_echeance, unsigned int _priorite = 0,TypeStatut _statut = cours )
        : Memento(_titre), action(_action), priorite(_priorite), date_echeance(_date_echeance), statut(_statut){}

    MementoTache(QString _titre, QString _action, unsigned int _priorite = 0, TypeStatut _statut = cours )
        : Memento(_titre), action(_action), priorite(_priorite), statut(_statut)
    {
        QDateTime a;
        a.addDays(0);
        date_echeance = a; // à revoir...
    }
    MementoTache(QString _titre, QString _action, QDateTime _dateModif, QDateTime _date_echeance, TypeStatut _statut = cours, unsigned int _priorite = 0 ): Memento(_titre,_dateModif), action(_action), priorite(_priorite), statut(_statut), date_echeance(_date_echeance){}

    QString getAction() const {return action;}
    unsigned int getPriorite() const {return priorite;}
    QDateTime getEcheance() const {return date_echeance;}
    unsigned int getStatut() const {return statut;}
    QString statutToString();

    virtual void saveXML(QXmlStreamWriter* stream);
private:
    QString action;
    unsigned int priorite; // optionnel
    QDateTime date_echeance; //optionnel
    TypeStatut statut;

};



class MementoMultimedia : public Memento{
public:
    MementoMultimedia(QString _titre, QString _description, QString _fichier, TypeMultimedia _type)
        : Memento(_titre), description(_description), fichier(_fichier), type(_type){}
    MementoMultimedia(QString _titre, QString _description, QString _fichier, TypeMultimedia _type, QDateTime _dateModif)
        : Memento(_titre, _dateModif), description(_description), fichier(_fichier), type(_type){}
    QString getDescription() const {return description;}
    QString getFichier() const {return fichier;}
    TypeMultimedia getType() const {return type;}
    QString typeToString();

    virtual void saveXML(QXmlStreamWriter* stream);
private:
    QString description;
    QString fichier; // adresse du fichier
    TypeMultimedia type; //type du fichier
};



// classes filles de memento


class Gardien{
public:

    Gardien(){
    }

    Gardien(Memento* mem){
        tab_memento.append(mem);
    }

    void addMemento(Memento* mem){
        tab_memento.append(mem);
    }

    unsigned int sizeMemento(){
        return tab_memento.size();
    }

    bool empty(){
        return tab_memento.empty();
    }

    class Iterator {
    public:
        Memento* operator *(){return tab[indice];}
        Memento* operator ++(){
            if(isdone())
                throw "il faut faire une classe d'exceptions";
            return tab[++indice];
        }
        Memento* operator ++(int){
            if(isdone())
            return tab[indice++];
        }
        bool isdone(){return indice == tab.size();}
    private:
        QList<Memento*> tab;
        unsigned int indice;
        friend class Gardien;
        Iterator(QList<Memento*> _tab): tab(_tab), indice(0) {}
    };

    Iterator getIterator() {
        return Iterator(tab_memento);
    }

private:
    QList<Memento*> tab_memento;

};


#endif // MEMENTO_H
