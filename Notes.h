#ifndef NOTES_H
#define NOTES_H

#include <QXmlStreamWriter>
#include <QDateTime>
#include "Memento.h"
#include <QMetaEnum>

/*!
* \file Notes.h
* \brief Définition des classes utiles aux notes
* \author Théophile Maxime Théo
* \version 0.99
*/

using namespace std;

/*! \class Note
* \brief Classe abstraite mère des notes
*
*  C'est la classe abstraite dont les différents types de notes héritent
*/

class Note{
public:
    /*!
    * \brief Getter identificateur
    * \return l'id d'une note sous forme de QString
    */
    QString getId() const {return identificateur;}
    /*!
    *  \brief Getter Titre
    * \return le titre d'une note sous forme de QString
    */
    QString getTitre() const {return titre;}
    /*!
    * \brief Getter Date de création
    * \return la date de création de la note sous forme de QDateTime
    */
    QDateTime getDateCrea() const {return date_creation;}
    /*!
    *  \brief Getter Date de modification
    * \return la date de modification de la note
    */
    QDateTime getDateModif() const {return date_modif;}
    /*!
    *  \brief Getter pointeur sur Gardien
    * \return un pointeur sur le gardien de la note
    */
    Gardien* getGardien() const {return gardien_note;}
    /*!
    *  \brief Setter pour le titre de la note
    * \param _titre le nouveau titre de la note de type QString
    */
    void setTitre(QString _titre){titre = _titre;}
    /*!
    *  \brief Setter pour la date de modification de la note. La date de modification devient celle du PC.
    */
    void newDateModif()
    {
        date_modif = QDateTime::currentDateTime();
    }
    /*!
    *  \brief Destructeur virtuel de Note
    */
    virtual ~Note(){}
    /*!
     * \brief Constructeur de Note à 2 paramètres
     *
     * Utile pour la première création d'une note
     *
     * \param id id de la note à créer de type QString
     * \param _titre titre de la note à créer de type QString
     */
    Note(QString _id, QString _titre) : identificateur(_id), titre(_titre), etat(active){
        date_creation = QDateTime::currentDateTime();
        date_modif = QDateTime::currentDateTime();
        gardien_note = new Gardien;
    }
    /*!
     * \brief Constructeur de Note à 5 paramètres
     *
     * Utile quand on charge une note depuis un fichier XML
     *
     * \param id identificateur de la note, de type QString
     * \param _titre titre de la note, de type QString
     * \param _dateCrea date de création, de type QDateTime
     * \param _dateModif date de modification de type QDateTime
     * \param _etat état, de type énuméré TypeEtatNote
     */
    Note(QString id, QString _titre, QDateTime _dateCrea, QDateTime _dateModif, TypeEtatNote _etat = active) : identificateur(id), titre(_titre), date_creation(_dateCrea), date_modif(_dateModif), etat(_etat){
        gardien_note = new Gardien;
    }
    /*!
     * \brief renvoie un QString avec la date de création de la note
     * \param date date à convertir en QString
     * \return date sous forme de QString
     */
    QString dateTimeToString(QDateTime date) const; //pourrait être static ?
    /*!
     * \brief renvoie un QString correspondant à l'état
     * \return etat sous forme de QString
     */
    QString etatToString() const;

private:
    QString identificateur; /*!< id de la note */
    QString titre; /*!< titre de la note */
    QDateTime date_creation;  /*!< date de creation de la note */
    QDateTime date_modif;  /*!< date de modification de la note */
    TypeEtatNote etat;  /*!< etat de la note  */
    Gardien* gardien_note; /*!< Pointeur sur le gardien de la note*/

    friend class NotesManager;

    // fonctions appellées par NM
    /*!
     * \brief Sauvegarde Note en XML
     *
     * Méthode virtuelle pure, redéfinie par les classes filles pour sauvegarder correctement la note en XML
     *
     * \param stream passage par parametre de QXmlStreamWriter
     */
    virtual void saveXML(QXmlStreamWriter* stream) = 0;// enregistre avec tous les paramètres
    //Pour l'instant en virtuel, pour pouvoir enregistrer les paramètres des fils selon le type de note
    // passage par parametre de QXmlStreamWriter pour test si on peut ecrire sur un fichier avec plusieurs fonctions
    /*!
     * \brief Enregistrement memento
     *
     * Méthode virtuelle pure, redéfinie par les classes filles pour enregistrer correctement le memento
     *
     * \return un pointeur sur le memento enregistré
     */
    virtual Memento* createMemento() const = 0 ; // enregistre un memento
    /*!
     * \brief Restauration memento
     * \param pointeur sur le memento à restaurer
     */
    virtual void restateMemento( Memento* mem ) = 0 ; // restaure un memento



};
/*! \class Article
 * \brief Classe Article
 *
 * Classe Article fille de Note
 */
class Article : public Note {
public:
    /*!
     * \brief Getter Texte
     * \return le texte de l'article, de type QString
     */
    QString getTexte() const {return texte;}
    /*!
     * \brief Setter Texte
     * \param _texte le texte à mettre dans l'article, de type QString
     */
    void setTexte(QString _texte){texte = _texte;}
    /*!
     * \brief Constructeur d'Article à 3 paramètres
     *
     * utile quand on crée pour la première fois un article
     *
     * \param id id de l'article à construire, de type QString
     * \param _titre titre de l'article à construire, de type QString
     * \param _texte texte de l'article à construire, de type QString
     */
    Article(QString id, QString _titre, QString _texte): Note(id,_titre), texte(_texte){}
    /*!
     * \brief Constructeur d'Article à 6 paramètres
     *
     * utile quand on charge un article depuis l'XML
     *
     * \param id id de l'article à construire, de type QString
     * \param _titre titre de l'article à construire, de type QString
     * \param _texte texte de l'article à construire, de type QString
     * \param _dateCrea date de création de l'article, de type QDateTime
     * \param _dateModif date de modification de l'article, de type QDateTime
     * \param _etat etat de l'article, de type TypeEtatNote
     */
    Article(QString id, QString _titre, QString _texte, QDateTime _dateCrea, QDateTime _dateModif, TypeEtatNote _etat = active): Note(id,_titre,_dateCrea,_dateModif, _etat), texte(_texte){}

    /*!
    * \brief Destructeur de la classe article
    */
    ~Article(){}

private:
    QString texte; /*!< texte de l'article */

    /*!
     * \brief Enregistrement d'un memento
     * \return pointeur sur le memento enregistré
     */
    Memento* createMemento() const; // enregistre un memento
    /*!
     * \brief Restauration d'un memento
     * \param pointeur sur le memento à restaurer
     */
    void restateMemento(Memento* mem);
    /*!
     * \brief sauvegarde d'Article en XML
     * \param stream Passage par paramètre QXmlStreamWriter
     */
    void saveXML(QXmlStreamWriter* stream);


};
/*! \class Tache
 * \brief Classe Tache
 *
 * classe Tache, fille de Note
 *
 */
class Tache : public Note {
public:
    /*!
     * \brief Constructeur de Tache à 6 paramètres
     *
     * utile quand on crée une tache pour la première fois en lui donnant une date d'échéance
     *
     * \param id id de la tache, de type QString
     * \param _titre titre de la tache, de type QString
     * \param _action action à effectuer de la tache, de type QString
     * \param date date d'échéance de la tache, de type QDateTime
     * \param _priorite prioriété de la tache, de type unsigned int
     * \param _statut statut de la tache de type énuméré TypeStatut
     */
    Tache(QString id, QString _titre, QString _action, QDateTime date, unsigned int _priorite = 0, TypeStatut _statut = attente) : Note(id,_titre), action(_action), date_echeance(date), priorite(_priorite), statut(_statut){} //cas avec tous les attributs
    /*!
     * \brief Constructeur de Tache à 5 paramètres
     *
     * utile qu'on on crée une tache pour la première fois sans lui donner de date d'échéance
     *
     * \param id id de la tache, de type QString
     * \param _titre titre de la tache, de type QString
     * \param _action action à effectuer de la tache, de type QString
     * \param _priorite prioriété de la tache, de type unsigned int
     * \param _statut statut de la tache de type énuméré TypeStatut
     */
    Tache(QString id, QString _titre, QString _action, unsigned int _priorite = 0, TypeStatut _statut = attente) : Note(id,_titre), action(_action), date_echeance(), priorite(_priorite), statut(_statut){}//cas sans date
    //on peut vérifier si une date est nulle avec isValid() ou isNull(), la priorité par défaut = 0 ?
    //voir si les valeurs par défaut sont plutot gérer par l'interface
    /*!
     * \brief Constructeur de Tache à 9 paramètres
     *
     * utile pour charger une tache depuis un fichier XML
     *
     * \param id id de la tache, de type QString
     * \param _titre titre de la tache, de type QString
     * \param _action action à effectuer de la tache, de type QString
     * \param date date d'échéance de la tache, de type QDateTime
     * \param _dateCrea date de création de la tache, de type QDateTime
     * \param _dateModif date de modification de la tache, de type QDateTime
     * \param _priorite prioriété de la tache, de type unsigned int
     * \param _statut statut de la tache de type énuméré TypeStatut
     * \param _etat état de la tachen de type énuméré TypeEtatNote
     */
    Tache(QString id, QString _titre, QString _action, QDateTime date, QDateTime _dateCrea, QDateTime _dateModif, unsigned int _priorite = 0, TypeStatut _statut = attente, TypeEtatNote _etat = active): Note(id,_titre,_dateCrea,_dateModif, _etat), action(_action), date_echeance(date), priorite(_priorite), statut(_statut){}
    /*!
    * \brief Destructeur de Tache
    */
    ~Tache(){}
    /*!
     * \brief Getter de action
     * \return action sous forme de QString
     */
    QString getAction(){return action;}
    /*!
     * \brief Getter de priorité
     * \return priorité sous forme d'entier non signé
     */
    unsigned int getPriorite(){return priorite;}
    /*!
     * \brief Getter de la date d'échance
     * \return date d'échéance sous frome de QDateTime
     */
    QDateTime getDateEcheance(){return date_echeance;}
    /*!
     * \brief Getter Statut
     * \return statut, de type énuméré TypeStatut
     */
    TypeStatut getStatut(){return statut;}
    /*!
     * \brief Setter d'action
     * \param _action action de type QString
     */
    void setAction(QString _action){action = _action;}
    /*!
     * \brief Setter de priorité
     * \param _priorite priorité de type unsigned int
     */
    void setPriority(unsigned int _priorite){priorite = _priorite;}
    /*!
     * \brief Setter de date d'échéance
     * \param dateEcheance date d'échance de la tache sous forme de QDateTime
     */
    void setDateEcheance(QDateTime dateEcheance){date_echeance = dateEcheance;}
    /*!
     * \brief Setter de statut
     * \param _statut statut sous forme de TypeStatut
     */
    void setStatut(TypeStatut _statut){statut = _statut;}
    /*!
     * \brief Retourne le statut d'une tache sous forme de QString
     * \return statut en QString
     */
    QString statutToString();
private:
    QString action; /*!< action de la tache */
    unsigned int priorite; /*!< priorité de la tache, optionnel */
    QDateTime date_echeance; /*!< date d'échéance de la tache, optionnel */
    TypeStatut statut; /*!< statut de la tache */
    /*!
     * \brief Enregistrement d'un mémento
     * \return pointeur sur le mémento enregistré
     */
    Memento* createMemento() const; // enregistre un memento
    /*!
     * \brief Restauration d'un mémento
     * \param mem pointeur sur le mémento à restaurer
     */
    void restateMemento(Memento* mem);
    /*!
     * \brief Sauvegarde XML de la tache
     * \param stream Passage par paramètre de QXmlStreamWriter
     */
    void saveXML(QXmlStreamWriter* stream);

    };
/*! \class Multimedia
 * \brief Classe Multimedia
 *
 * classe multimedia, fille de Note
 *
 */
class Multimedia : public Note {
public:
    /*!
     * \brief Getter de la description
     * \return description sous forme de QString
     */
    QString getDescription() const {return description;}
    /*!
     * \brief Constructeur de Multimedia à 5 paramètres
     *
     * utile pour la première création d'une Note multimedia
     *
     * \param id id du multimedia, de type QString
     * \param _titre titre du multimedia, de type QString
     * \param desc description du multimedia, de type QString
     * \param _fichier emplacement du fichier du multimedia, de type QString
     * \param _type type du fichier, de type énuméré TypeMultimedia
     */
    Multimedia(QString id, QString _titre, QString desc, QString _fichier, TypeMultimedia _type): Note(id,_titre), description(desc), fichier(_fichier), type(_type){}
    /*!
     * \brief Constructeur de Multimedia à 8 paramètres
     *
     * utile pour créer un multimedia à partir d'un XML
     *
     * \param id id du multimedia, de type QString
     * \param _titre titre du multimedia, de type QString
     * \param desc description du multimedia, de type QString
     * \param _fichier emplacement du fichier du multimedia, de type QString
     * \param _type type du multimedia, de type énuméré TypeMultimedia
     * \param _dateCrea date de création, de type QDateTime
     * \param _dateModif date de modification, de type QDateTime
     * \param _etat état du fichier, de type TypeEtatNote
     */
    Multimedia(QString id, QString _titre, QString desc, QString _fichier, TypeMultimedia _type, QDateTime _dateCrea, QDateTime _dateModif,  TypeEtatNote _etat = active): Note(id,_titre,_dateCrea,_dateModif, _etat), description(desc), fichier(_fichier), type(_type){}
    /*!
    *\brief Destructeur de Multimedia
    */
    ~Multimedia(){}
    /*!
     * \brief Getter de l'emplacement du fichier
     * \return emplacement du fichier, sous forme de QString
     */
    QString getFicher() const {return fichier;}
    /*!
     * \brief Getter du Type de fichier
     * \return le type de fichier
     */
    TypeMultimedia getType() const {return type;}

    /*!
     * \brief Setter de la Description
     * \param desc description de type QString
     */
    void setDescription(QString desc){description = desc;}
    /*!
     * \brief Setter de l'emplacement du fichier
     * \param file emplacement du fichier sous forme de QString
     */
    void setFichier(QString file){fichier = file;}
    /*!
     * \brief Setter du type de fichier
     * \param _type type énuméré de type TypeMultimedia
     */
    void setType(TypeMultimedia _type){type = _type;}


    /*!
     * \brief Retourne le type de fichier en QString
     * \return QString du type de fichier
     */
    QString typeToString();
private:
    QString description; /*!< description du multimedia */
    QString fichier; /*!< emplacement du fichier */
    TypeMultimedia type; /*!< type du fichier */
    /*!
     * \brief Enregistrement d'un mémento
     * \return pointeur sur le mémento enregistré
     */
    Memento* createMemento() const; // enregistre un memento
    /*!
     * \brief Restauration d'un mémento
     * \param mem pointeur sur le mémento à restaurer
     */
    void restateMemento(Memento* mem);

    /*!
     * \brief Sauvegarde XML de la tache
     * \param stream pointeur sur QXmlStreamWriter
     */
    void saveXML(QXmlStreamWriter* stream);

    };





// ----- Notes Manager ----- //

/*! \class NotesManager
 *
 * \brief Manager de la classe Note
 */
class NotesManager{
public:
    /*!
     * \brief Ajout de Note
     * \param n pointeur sur la note à ajouter
     */
    void addNote(Note* n);
    /*!
     * \brief Suppression de Note
     * \param id identificateur de la note à supprimer
     */
    void deleteNote(const QString& id);
    /*!
     * \brief test et supprime les notes archivées qui n'ont plus de références
     */
    void deleteArchive();
    /*!
     * \brief Vide la Corbeille
     */
    void viderCorbeille();
    /*!
     * \brief Restaure la Corbeille
     */
    void restaurerCorbeille();
    /*!
     * \brief Renvoie True si il existe au moins un element dans la corbeille.
     */
    bool testCorbeille();
    /*!
     * \brief restaure une note archivée
     * \param id id identificateur de la note à restaurer
     */
    void restaurerArchiveNote(const QString& id);
    /*!
     * \brief Teste l'existence d'une Note
     * \param id identificateur de la Note à chercher
     * \return True si la Note existe, False sinon
     */
    bool existeNote(const QString& id);

    /*!
     * \brief Méthode statique donnant l'instance de NoteManager
     *
     * Renvoie une référence sur NoteManager si déjà instancié, sinon en crée une nouvelle
     *
     * \return référence sur NoteManage
     */
    static NotesManager& donneInstance(){
        if (!instance)
            instance = new NotesManager();
        return *instance;
    }

    /*!
     * \brief Supprime l'instance de NoteManager
     *
     * Supprime l'instance de NoteManager si elle existe
     *
     */
    static void supprimeInstance(){
        if (instance){
            delete instance;
            instance = nullptr;
        }
    }

    /*! \class Iterator
     * \brief classe Itérator de NoteManager
     *
     * Permet de parcourir les notes
     *
     */
    class Iterator {
    public:
        /*!
         * \brief Surcharche de l'opérateur *
         * \return Pointeur sur la note courante
         */
        Note* operator *(){
            return *current;
        }
        /*!
         * \brief Surcharche de l'operateur ++ (préfixé)
         * \return pointeur sur la note suivante
         */
        Note* operator ++(){
            if(last == 0)
                throw NotesException(QString("Erreur, arrive au bout."));
            --last;
            return *(++current);
        }
        /*!
         * \brief Surcharche de l'operateur ++ (postfixé)
         * \return pointeur sur la note suivante
         */
        Note* operator ++(int){
            if(last == 0)
                throw NotesException(QString("Erreur, arrive au bout."));
            Note* save = *current;
            ++current;
            --last;
            return save;
        }
        /*!
         * \brief Teste si on est sur la dernière note
         * \return True s'il n'y a plus de note suivante, False sinon
         */
        bool isdone(){return last == 0;}

    private:
        Note** current; /*!< tableau de pointeur de note*/
        unsigned int last; /*!< position de la dernière note par rapport à la note courante*/
        friend class NotesManager;
        /*!
         * \brief Constructeur de la classe Iterator
         * \param _tab tableau de pointeur de Note
         * \param _nb_max nombre maximum de notes pour le tableau
         */
        Iterator(Note** _tab, unsigned int _nb_max)
            : current(_tab), last(_nb_max) {}
    };

    /*!
     * \brief instancie l'Iterator
     */
    Iterator getIterator() {
        return Iterator(tabNotes, nbNotes);
    }
    /*!
     * \brief Getter d'une note
     * \param id identificateur de la note à chercher
     * \return référence sur la note
     */
    Note& getNote(const QString& id);
    /*!
     * \brief Création d'une Note
     *
     * crée une note vide avec id / titre / date
     *
     * \param id id de la note à créer
     * \param titre titre de la note à créer
     */
    void createNote(const string& id, const string& titre); // crée une note vide avec id / titre / date
    /*!
     * \brief Sauvegarde d'une Note
     * \param id id de la note à sauvegarder
     */
    void saveNote(const string& id); // enregistre une note avec tout ce qu'il faut / ça fait un memento

    /*!
     * \brief Sauvegarde des Notes dans un XML
     *
     * Ecris Tout dans un fichier xml
     *
     */
    void SaveEverythingXML(); // Ecris Tout dans un fichier xml
    /*!
     * \brief Charge un fichier XML
     */
    void LoadFileXML();

    /*!
     * \brief Sauvegarde la version d'une note
     * \param _note pointeur sur la note
     */
    void saveVersion(Note* _note) const;
    /*!
     * \brief Restaure une note depuis sa version
     * \param _note pointeur sur la note
     * \param version version à restaurer
     */
    void restateVersion(Note* _note, QDateTime version);

private:
    Note** tabNotes; /*!< tableau de pointeur de notes */
    unsigned int nbNotes; /*!< nombre de notes dans le tableau */
    unsigned int nbMaxNotes; /*!< nombre maximum de notes dans le tableau*/

    static NotesManager* instance; /*!< pointeur sur l'instance de NotesManager*/

    /*!
     * \brief Constructeur de NotesManager
     */
    NotesManager();
    /*!
    * \brief Destructeur de NotesManager
    */
    ~NotesManager();

    /*!
     * \brief Constructeur de recopie de NotesManager vide
     *
     * on interdit le constructeur de recopie
     *
     */
    NotesManager(const NotesManager&){}
    /*!
     * \brief Surcharge vide de l'operateur =
     *
     * on interdit l'affectation.
     *
     */
    void operator =(const NotesManager&){}



};


#endif // NOTES_H
