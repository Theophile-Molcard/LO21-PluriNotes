#ifndef NOTES_H
#define NOTES_H

#include <QXmlStreamWriter>
#include <QDateTime>

using namespace std;

enum TypeMultimedia{video, audio, image};
enum TypeStatut{attente, cours, termine};


/// ------ Note Exception ------ ///


class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};




/// ----- Notes ----- ///


class Note{
public:
    QString getId() const {return identificateur;}
    QString getTitre() const {return titre;}
    QDateTime getDateCrea() const {return date_creation;}
    QDateTime getDateModif() const {return date_modif;}
    virtual ~Note(){}
    Note(QString id, QString _titre) : identificateur(id), titre(_titre){
        date_creation = QDateTime::currentDateTime();
        date_modif = QDateTime::currentDateTime();
    }
private:
    QString identificateur;
    QString titre;
    QDateTime date_creation;
    QDateTime date_modif;

    friend class NotesManager;

    // fonctions appellées par NM

    virtual void save(QXmlStreamWriter* stream); // enregistre avec tous les paramètres
    //Pour l'instant en virtuel, pour pouvoir enregistrer les paramètres des fils selon le type de note
    // passage par parametre de QXmlStreamWriter pour test si on peut ecrire sur un fichier avec plusieurs fonctions

    void createMemento(); // enregistre un memento
    void restoreMemento(); // restaure un memento
};

class Article : public Note {
public:
    QString getTexte() const {return texte;}
    Article(QString id, QString _titre, QString _texte): Note(id,_titre), texte(_texte){}
    ~Article(){}
private:
    QString texte;

    void save(QXmlStreamWriter* stream);

};

class Tache : public Note {
public:
    Tache(QString id, QString _titre, QString _action, QDateTime date, unsigned int _priorite, TypeStatut _statut) : Note(id,_titre), action(_action), date_echeance(date), priorite(_priorite), statut(_statut){}
    //A modifier: le constructeur dans le cas des attributs optionnels
    ~Tache(){}

    QString getAction(){return action;}
    unsigned int getPriorite(){return priorite;}
    QDateTime getDateEcheance(){return date_echeance;}
    TypeStatut getStatut(){return statut;}
private:
    QString action;
    unsigned int priorite; // optionnel
    QDateTime date_echeance; //optionnel
    TypeStatut statut;

    void save(QXmlStreamWriter* stream);
};

class Multimedia : public Note {
public:
    QString getDescription() const {return description;}
    Multimedia(QString id, QString _titre, QString desc, QString _fichier, TypeMultimedia _type): Note(id,_titre), description(desc), fichier(_fichier), type(_type){}
    ~Multimedia(){}

    QString getDescription(){return description;}
    QString getFicher(){return fichier;}
    TypeMultimedia getType(){return type;}
private:
    QString description;
    QString fichier; // adresse du fichier
    TypeMultimedia type; //type du fichier

    void save(QXmlStreamWriter* stream);
};




/// ----- Notes Manager ----- ///


class NotesManager{
public:
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
                throw "il faut faire une calsse d'exceptions";
            --last;
            return *(++current);
        }
        Note* operator ++(int){
            if(last == 0)
                throw "il faut faire une calsse d'exceptions";
            Note* save = *current;
            ++current;
            --last;
            return save;
        }

    private:
        Note** current;
        unsigned int last;
        friend class NotesManager;
        Iterator(Note** _tab, unsigned int _nb_max)
            : current(_tab), last(_nb_max) {}
    };

    Iterator getIterator() {
        return Iterator(tabNotes, nbMaxNotes);
    }

    void createNote(const string& id, const string& titre); // crée une note vide avec id / titre / date
    void saveNote(const string& id); // enregistre une note avec tout ce qu'il faut / ça fait un memento

    void SaveEverything(); // Ecris Tout dans un fichier xml
    //void LoadFile();

private:
    Note** tabNotes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;

    static NotesManager* instance;
    NotesManager();
    NotesManager(const NotesManager&);
    virtual ~NotesManager();
    void operator =(const NotesManager&);

};


#endif // NOTES_H
