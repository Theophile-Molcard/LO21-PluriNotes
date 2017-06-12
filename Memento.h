#ifndef MEMENTO_H
#define MEMENTO_H

#include<QList>
#include<iterator>
#include<QDateTime>
#include <QXmlStreamWriter>
/*!
* \file Memento.h
* \brief Définition des classes utiles aux Mementos
* Permet de sauvegarder les versions d'une note
* \author Théophile Maxime Théo
* \version 0.99
*/
using namespace std;
/*! \enum TypeMultimedia
 * \brief Type énuméré pour décrire le type d'un fichier multimedia
 *
 * Valeurs possibles : video, audio ou image
 */
enum TypeMultimedia{video, audio, image};
/*! \enum TypeStatut
 * \brief Type énuméré pour décrire le statut d'une tache
 *
 * Valeur possibles : attente, cours, termine
 */
enum TypeStatut{attente, cours, termine};
/*! \enum TypeEtatNote
 * \brief Type énuméré pour décrire l'état d'une note
 *
 * Valeurs possible active (par défaut), archive, corbeille
 */
enum TypeEtatNote{active,archive,corbeille};


// ------ Note Exception ------ //

/*! \class NotesException
 * \brief Classe pour gérer les execptions propres aux notes
 */
class NotesException{
public:
    /*!
     * \brief Contructeur de NotesException
     * \param message information concernant l'exception
     */
    NotesException(const QString& message):info(message){}
    /*!
     * \brief Getter de l'information d'une NotesException
     * \return information de la NotesException
     */
    QString getInfo() const { return info; }
private:
    QString info; /*!< information de la NotesException */
};

/*! \class Memento
* \brief Classe Mère des Memento
*
* Classe mère abstraite des memento, permet de sauvegarder une note
*
*/
class Memento{
public:
    /*!
     * \brief Getter Titre du memento
     * \return le titre du memento, de type QString
     */
    QString getTitre() const { return titre; }

    /*!
     * \brief Gette date de modification du memento
     * \return la date de modification du memento, de type QDateTime
     */
    const QDateTime& getDateModif() const { return date_modif; }
    /*!
     * \brief Constructeur de Memento à 1 paramètre
     * \param _titre titre du memento
     */
    Memento(QString _titre) // il faut voir pour la version
        : titre(_titre)
    {
        date_modif=QDateTime::currentDateTime();
    }
    /*!
     * \brief Constructeur de Memento à 2 paramètres
     * \param _titre titre du memento
     * \param _dateModif date de modification du memento
     */
    Memento(QString _titre, QDateTime _dateModif): titre(_titre), date_modif(_dateModif){}

    /*!
     * \brief Destructeur de Memento
     */
    virtual ~Memento() {}
    /*!
     * \brief Sauvegarde le memento en XML
     *
     *  Méthode virtuelle pure à redifinir dans chaque classe fille de memento
     *
     * \param stream passage par paramètre du QXmlStreamWriter
     */
    virtual void saveXML(QXmlStreamWriter* stream) = 0;

    /*!
     * \brief Donne la date sous forme
     * \param date date de type QDateTime à transformer
     * \return date sous forme de QString
     */
    QString dateToString(QDateTime date){
        return date.toString("dd-MM-yyyy hh:mm:ss");
    }

private:
    QString titre; /*!< titre du memento */
    QDateTime date_modif;/*!< date de modification du mement */

};
/*! \class Memento Article
 * \brief Classe fille de memento pour les articles
 */
class MementoArticle : public Memento{
public:
    /*!
     * \brief Constructeur de MementoArticle à 2 paramètres
     * \param _titre titre du memento
     * \param _texte texte du memento
     */
    MementoArticle(QString _titre, QString _texte)
        : Memento(_titre)
    {
        texte = _texte;
    }
    /*!
     * \brief Constructeur de MementoArticle à 3 paramètres
     * \param _titre titre du memento
     * \param _texte texte du memento
     * \param _dateModif date de modification du memento
     */
    MementoArticle(QString _titre, QString _texte, QDateTime _dateModif): Memento(_titre,_dateModif), texte(_texte){}

    /*!
     * \brief Getter texte de MementoAticle
     * \return texte du memento article
     */
    QString getTexte() const {return texte;}
    virtual void saveXML(QXmlStreamWriter* stream);

private:
    QString texte; /*!< texte du memento */
};


/*! \class MementoTache
 * \brief Classe fille de Memento pour les tâches
 */
class MementoTache : public Memento{
public:
    /*!
     * \brief Constructeur de MementoTache à 5 paramètres
     * \param _titre titre de MementoTache
     * \param _action action de MementoTache
     * \param _date_echeance date d'échéance de MementoTache
     * \param _priorite priorité de MementoTache
     * \param _statut statut de MementoTache
     */
    MementoTache(QString _titre, QString _action, QDateTime _date_echeance, unsigned int _priorite = 0,TypeStatut _statut = cours )
        : Memento(_titre), action(_action), priorite(_priorite), date_echeance(_date_echeance), statut(_statut){}

    /*!
     * \brief Constructeur de MementoTache à 4 paramètres
     * \param _titre titre de MementoTache
     * \param _action action de MementoTache
     * \param _priorite priorité de MementoTache
     * \param _statut statut de MementoTache
     */
    MementoTache(QString _titre, QString _action, unsigned int _priorite = 0, TypeStatut _statut = cours )
        : Memento(_titre), action(_action), priorite(_priorite), statut(_statut)
    {
        QDateTime a;
        a.addDays(0);
        date_echeance = a; // à revoir...
    }
    /*!
     * \brief Constructeur de MementoTache à 5 paramètres
     * \param _titre titre de MementoTache
     * \param _action action de MementoTache
     * \param _dateModif date de modification de MementoTache
     * \param _date_echeance date d'échéange de MementoTache
     * \param _priorite priorité de MementoTache
     * \param _statut statut de MementoTache
     */
    MementoTache(QString _titre, QString _action, QDateTime _dateModif, QDateTime _date_echeance, TypeStatut _statut = cours, unsigned int _priorite = 0 ): Memento(_titre,_dateModif), action(_action), priorite(_priorite), statut(_statut), date_echeance(_date_echeance){}

    /*!
     * \brief Getterde l'action de MementoTache
     * \return l'action du MementoTache
     */
    QString getAction() const {return action;}
    /*!
     * \brief Getter de la priorité de MementoTache
     * \return la priorité du MementoTache
     */
    unsigned int getPriorite() const {return priorite;}
    /*!
     * \brief Getter de la date d'échéance de MementoTache
     * \return la date d'échance du MementoTache
     */
    QDateTime getEcheance() const {return date_echeance;}
    /*!
     * \brief Getter du statut de MementoTache
     * \return le statut de MementoTache
     */
    TypeStatut getStatut() const {return statut;}
    /*!
     * \brief Renvoie sous forme de string le statut
     * \return le statut sous forme de QString
     */
    QString statutToString();

    /*!
     * \brief Sauvegarde du MementoTache en XML
     * \param stream passage par parametre de QXmlStreamWriter
     */
    virtual void saveXML(QXmlStreamWriter* stream);
private:
    QString action; /*!< action du MementoTache */
    unsigned int priorite; /*!< priorité du MementoTache, optionnel */
    QDateTime date_echeance; /*!< date d'échéance du MementoTache, optionnel */
    TypeStatut statut; /*!< statut du MementoTache*/

};


/*! \class MementoMultimedia
 * \brief Classe fille de Memento pour les notes multimedia
 */
class MementoMultimedia : public Memento{
public:
    /*!
     * \brief Constructeur de MementoMultimedia à 4 paramètres
     * \param _titre titre du MementoMultimedia
     * \param _description description du MementoMultimedia
     * \param _fichier emplacement du fichier du MementoMultimedia
     * \param _type type de fichier du MementoMultimedia
     */
    MementoMultimedia(QString _titre, QString _description, QString _fichier, TypeMultimedia _type)
        : Memento(_titre), description(_description), fichier(_fichier), type(_type){}
    /*!
     * \brief Constructeur de MementoMultimedia à 4 paramètres
     * \param _titre titre du MementoMultimedia
     * \param _description description du MementoMultimedia
     * \param _fichier emplacement du fichier du MementoMultimedia
     * \param _type type de fichier du MementoMultimedia
     * \param _dateModif date de modification du MementoMultimedia
     */
    MementoMultimedia(QString _titre, QString _description, QString _fichier, TypeMultimedia _type, QDateTime _dateModif)
        : Memento(_titre, _dateModif), description(_description), fichier(_fichier), type(_type){}
    /*!
     * \brief Getter de la description du MementoMultimedia
     * \return la description du MementoMultimedia
     */
    QString getDescription() const {return description;}
    /*!
     * \brief Getter de l'emplacement du fichier du MementoMultimedia
     * \return l'emplacement du fichier sous forme de QString
     */
    QString getFichier() const {return fichier;}
    /*!
     * \brief Getter du type de fichier du MementoMultimedia
     * \return le type de fichier du MementoMultimedia
     */
    TypeMultimedia getType() const {return type;}
    /*!
     * \brief Renvoie le type de fichier sous forme de string
     * \return le type de fichier, sous forme de QString
     */
    QString typeToString();

    /*!
     * \brief Sauvegarde du MementoMultimedia en XML
     * \param stream passage par parametre de QXmlStreamWriter
     */
    virtual void saveXML(QXmlStreamWriter* stream);
private:
    QString description; /*!< description du MementoMultimedia */
    QString fichier; /*!< adresse du fichier */
    TypeMultimedia type; /*!< type du fichier */
};



// classes filles de memento

/*! \class Gardien
 * \brief Classe du Gardien de memento
 *
 * classe gérant le gardien d'un memento, permet de gérer et restaurer les différentes versions d'une note
 */
class Gardien{
public:
    /*!
     * \brief Constructeur vide du Gardien
     */
    Gardien(){
    }
    /*!
     * \brief Constructeur de Gardien qui ajoute un memento à la création
     * \param mem pointeur sur le Memento à ajouter au tableau de mementos
     */
    Gardien(Memento* mem){
        tab_memento.append(mem);
    }
    /*!
    * \brief Destructeur du Gardien
    */
    ~Gardien();
    /*!
     * \brief Ajoute un memento au tableau
     * \param mem pointeur sur le memento à ajouter
     */
    void addMemento(Memento* mem){
        tab_memento.append(mem);
    }

    /*!
     * \brief Getter sur un memento du tableau
     *
     * Identifie le mémento grâce à la date de modification
     * \param dateModif date de modification du memento à chercher
     * \return  référence sur le mémento trouvé
     */
    Memento& getMemento(QDateTime dateModif);

    /*!
     * \brief Donne la taille du tableau de Mementos
     * \return taille du tableau de mementos
     */
    unsigned int sizeMemento(){
        return tab_memento.size();
    }

    /*!
     * \brief test si tableau vide
     * \return true si le tableau est vide, false sinon
     */
    bool empty(){
        return tab_memento.empty();
    }
    /*! \class Iterator
     * \brief Classe Iterator pour parcourir le tableau de Mementos
     */
    class Iterator {
    public:
        /*!
         * \brief Surcharge de l'operateur *
         *
         * Permet d'utiliser le tableau de façon classique
         *
         * \return un pointeur sur le memento d'indice 'indice' du tableau
         */
        Memento* operator *(){return tab[indice];}
      /*  Memento* operator ++(){
            if(isdone())
                throw "il faut faire une classe d'exceptions";
            return tab[++indice];
        }*/
        /*!
         * \brief Surcharge de l'operateur ++ (postfixé)
         *
         * permet d'augmenter l'indice du tableau de 1 et renvoyer le memento correspondant
         *
         * \return un pointeur sur le memento au nouvel indice courant
         */
        Memento* operator ++(int){
            if(!isdone())
                return tab[indice++];
            else
                throw NotesException(QString("Erreur, arrive au bout."));
        }
        /*!
         * \brief test si on est au bout du tableau
         * \return true si on est à la fin du tableau, false sinon
         */
        bool isdone(){return indice == tab.size();}
    private:
        QList<Memento*> tab; /*!< tableau de pointeur de  mementos, sous forme de Qlist*/
        unsigned int indice; /*!< indice courant */
        friend class Gardien;
        /*!
         * \brief Constructeur de Iterator
         * \param _tab tableau des pointeurs de mementos à parcourir
         */
        Iterator(QList<Memento*> _tab): tab(_tab), indice(0) {}
    };

    /*!
     * \brief Getter de Iterator
     * Instancie un nouvel iterator
     * \return un iterator
     */
    Iterator getIterator() {
        return Iterator(tab_memento);
    }

private:
    QList<Memento*> tab_memento; /*!< tableau de pointeur de mementos, utilisant une QList*/

};


#endif // MEMENTO_H
