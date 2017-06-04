#ifndef NOTES_H
#define NOTES_H

#include <QXmlStreamWriter>
#include <QDateTime>
#include "Memento.h"
#include <QMetaEnum>

using namespace std;





/// ----- Notes ----- ///


class Note{
public:
    QString getId() const {return identificateur;}
    QString getTitre() const {return titre;}
    QDateTime getDateCrea() const {return date_creation;}
    QDateTime getDateModif() const {return date_modif;}
    Gardien* getGardien() const {return gardien_note;}

    void setTitre(QString _titre){titre = _titre;}

    virtual ~Note(){}
    Note(QString id, QString _titre) : identificateur(id), titre(_titre){
        date_creation = QDateTime::currentDateTime();
        date_modif = QDateTime::currentDateTime();
        gardien_note = new Gardien;
    }
    Note(QString id, QString _titre, QDateTime _dateCrea, QDateTime _dateModif) : identificateur(id), titre(_titre), date_creation(_dateCrea), date_modif(_dateModif){
        gardien_note = new Gardien;
    }

    QString dateTimeToString(QDateTime date);

private:
    QString identificateur;
    QString titre;
    QDateTime date_creation;
    QDateTime date_modif;

    Gardien* gardien_note;

    friend class NotesManager;

    // fonctions appellées par NM

    virtual void saveXML(QXmlStreamWriter* stream) = 0;// enregistre avec tous les paramètres
    //Pour l'instant en virtuel, pour pouvoir enregistrer les paramètres des fils selon le type de note
    // passage par parametre de QXmlStreamWriter pour test si on peut ecrire sur un fichier avec plusieurs fonctions

    virtual Memento* createMemento() const = 0 ; // enregistre un memento
    virtual void restateMemento( Memento* mem ) = 0 ; // restaure un memento



};

class Article : public Note {
public:
    QString getTexte() const {return texte;}
    void setTexte(QString _texte){texte = _texte;}
    Article(QString id, QString _titre, QString _texte): Note(id,_titre), texte(_texte){}
    Article(QString id, QString _titre, QString _texte, QDateTime _dateCrea, QDateTime _dateModif): Note(id,_titre,_dateCrea,_dateModif), texte(_texte){}

    ~Article(){}

private:
    QString texte;

    Memento* createMemento() const; // enregistre un memento
    void restateMemento(Memento* mem);

    void saveXML(QXmlStreamWriter* stream);


};

class Tache : public Note {
public:
    Tache(QString id, QString _titre, QString _action, QDateTime date, unsigned int _priorite = 0, TypeStatut _statut = cours) : Note(id,_titre), action(_action), date_echeance(date), priorite(_priorite), statut(_statut){} //cas avec tous les attributs

    Tache(QString id, QString _titre, QString _action, unsigned int _priorite = 0, TypeStatut _statut = cours) : Note(id,_titre), action(_action), date_echeance(), priorite(_priorite), statut(_statut){}//cas sans date
    //on peut vérifier si une date est nulle avec isValid() ou isNull(), la priorité par défaut = 0 ?
    //voir si les valeurs par défaut sont plutot gérer par l'interface
    Tache(QString id, QString _titre, QString _action, QDateTime date, QDateTime _dateCrea, QDateTime _dateModif, unsigned int _priorite = 0, TypeStatut _statut = cours): Note(id,_titre,_dateCrea,_dateModif), action(_action), date_echeance(date), priorite(_priorite), statut(_statut){}

    ~Tache(){}

    QString getAction(){return action;}
    unsigned int getPriorite(){return priorite;}
    QDateTime getDateEcheance(){return date_echeance;}
    TypeStatut getStatut(){return statut;}
    void setAction(QString _action){action = _action;}
    void setPriority(unsigned int _priorite){priorite = _priorite;}
    void setDateEcheance(QDateTime dateEcheance){date_echeance = dateEcheance;}
    void setStatut(TypeStatut _statut){statut = _statut;}
    QString statutToString();
private:
    QString action;
    unsigned int priorite; // optionnel
    QDateTime date_echeance; //optionnel
    TypeStatut statut;

    Memento* createMemento() const; // enregistre un memento
    void restateMemento(Memento* mem);

    void saveXML(QXmlStreamWriter* stream);

    };

class Multimedia : public Note {
public:
    QString getDescription() const {return description;}
    Multimedia(QString id, QString _titre, QString desc, QString _fichier, TypeMultimedia _type): Note(id,_titre), description(desc), fichier(_fichier), type(_type){}
    Multimedia(QString id, QString _titre, QString desc, QString _fichier, TypeMultimedia _type, QDateTime _dateCrea, QDateTime _dateModif): Note(id,_titre,_dateCrea,_dateModif), description(desc), fichier(_fichier), type(_type){}

    ~Multimedia(){}

    QString getDescription(){return description;}
    QString getFicher(){return fichier;}
    TypeMultimedia getType(){return type;}

    void setDescription(QString desc){description = desc;}
    void setFichier(QString file){fichier = file;}

    QString typeToString();
private:
    QString description;
    QString fichier; // adresse du fichier
    TypeMultimedia type; //type du fichier
    Memento* createMemento() const; // enregistre un memento
    void restateMemento(Memento* mem);

    void saveXML(QXmlStreamWriter* stream);

    };




/// ----- Notes Manager ----- ///


class NotesManager{
public:
    void addNote(Note* n);

    static NotesManager& donneInstance(){
        if (!instance)
            instance = new NotesManager();
        return *instance;
    }

    static void supprimeInstance(){
        if (instance){
            delete instance;
            instance = nullptr;
        }
    }

    class Iterator {
    public:
        Note* operator *(){
            return *current;
        }
        Note* operator ++(){
            if(last == 0)
                throw NotesException(QString("Erreur, arrive au bout."));
            --last;
            return *(++current);
        }
        Note* operator ++(int){
            if(last == 0)
                throw NotesException(QString("Erreur, arrive au bout."));
            Note* save = *current;
            ++current;
            --last;
            return save;
        }
        bool isdone(){return last == 0;}

    private:
        Note** current;
        unsigned int last;
        friend class NotesManager;
        Iterator(Note** _tab, unsigned int _nb_max)
            : current(_tab), last(_nb_max) {}
    };

    Iterator getIterator() {
        return Iterator(tabNotes, nbNotes);
    }

    Note& getNote(const QString& id);
    void createNote(const string& id, const string& titre); // crée une note vide avec id / titre / date
    void saveNote(const string& id); // enregistre une note avec tout ce qu'il faut / ça fait un memento

    void SaveEverythingXML(); // Ecris Tout dans un fichier xml
    void LoadFileXML();

    void saveVersion(Note* _note) const;
    void restateVersion(Note* _note, unsigned int version);

private:
    Note** tabNotes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;

    static NotesManager* instance;
    NotesManager();
    ~NotesManager();

    //on interdit le constructeur de recopie et l'affectation.
    NotesManager(const NotesManager&){}
    void operator =(const NotesManager&){}



};


#endif // NOTES_H
