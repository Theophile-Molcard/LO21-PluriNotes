#ifndef RELATIONS_H
#define RELATIONS_H

#include <QString>
#include <QXmlStreamWriter>
#include "Memento.h"
/*!
* \file relations.h
* \brief Définition des classes utiles aux relations
* \author Théophile Maxime Théo
* \version 0.99
*/

/*! \class Couple
 * \brief Classe qui définit un couple
 *
 * Les couples sont définits uniquement sur des QString correspondantes aux id de notes
 *
 */
class Couple{
    friend class Relation;
public:
    /*!
     * \brief Getter de l'attribut x d'un couple
     * \return la chaine de caractères correspondante à x
     */
    QString getx(){return x;}
    /*!
     * \brief Getter de l'attribut y d'un couple
     * \return la chaine de caractères correspondante à y
     */
    QString gety(){return y;}
    /*!
     * \brief Getter du label d'un couple
     * \return la chaine de caractères correspondante au label
     */
    QString getLabel(){return label;}
    /*!
     * \brief Setter du label
     * \param _label la QString qui définit ce label
     */
    void setLabel(QString _label){label=_label;}
private:
    /*!
     * \brief Constructeur de Couple
     * \param _x l'id de la note x dans la relation (x;y)
     * \param _y l'id de la note y dans la relation (x;y)
     * \param _label le label pour le couple
     */
    Couple(QString _x, QString _y, QString _label): x(_x), y(_y), label(_label){}
    QString x; /*!< l'id de la note x dans la relation (x;y) */
    QString y; /*!< l'id de la note y dans la relation (x;y) */
    QString label; /*!< le label pour le couple */

    /*!
     * \brief Sauvegarde en XML du couple
     * \param stream pointeur sur le QXmlStreamWriter
     */
    void saveXML(QXmlStreamWriter* stream);
};

/*! \class Relation
 * \brief Classe qui définit les relations
 *
 * Définit les relations et le tableau de couples appartenant à la relation
 *
 */
class Relation{
public:
    /*!
     * \brief Constructeur de Relation
     * \param _titre titre de la relation
     * \param _desc description de la relation
     * \param _orientee booléen informant du statut orienté ou non de la note
     */
    Relation(QString _titre, QString _desc, bool _orientee = true): titre(_titre), description(_desc), tabCouples(nullptr), nbCouples(0), nbMaxCouples(0), orientee(_orientee){}
    /*!
     * \brief Destructeur de Relation
     */
    ~Relation();
    /*!
     * \brief Ajout de Couple à la relation
     * \param _x id de la note x du couple (x;y)
     * \param _y id de la note y du couple (x;y)
     * \param _label label du couple
     */
    void addCouple(QString _x, QString _y, QString _label = "default");
    /*!
     * \brief Suppression du couple dans la relation
     * \param _x id de la note x du couple (x;y)
     * \param _y id de la note y du couple (x;y)
     */
    void deleteCouple(QString _x, QString _y);
    /*!
     * \brief teste si le couple (x;y) existe dans la relation
     * \param _x id de la note x du couple (x;y)
     * \param _y id de la note y du couple (x;y)
     * \return true si le couple existe, false sinon
     */
    bool existeCouple(QString _x, QString _y);
    /*!
     * \brief Getter du couple (x;y)
     * \param _x id de la note x du couple (x;y)
     * \param _y id de la note y du couple (x;y)
     * \return une référence sur le couple (x;y)
     */
    Couple& getCouple(QString _x, QString _y);

    /*!
     * \brief Inverse le statut orienté du relation
     */
    void inverseOrientation();

    /*!
     * \brief Getter du titre d'une relation
     * \return titre sous forme de QString
     */
    QString getTitre(){return titre;}
    /*!
     * \brief Getter de la description d'une relation
     * \return Description sous forme de QString
     */
    QString getDescription(){return description;}
    /*!
     * \brief Getter de l'orientation d'une relation
     * \return true si la relation est orientée, false sinon
     */
    bool getOrientee(){return orientee;}

    /*!
     * \brief Setter du titre d'une relation
     * \param _titre titre à donner à la relation
     */
    void setTitre(QString _titre){if (titre != "Reference") titre=_titre;}
    /*!
     * \brief Setter de la description d'une relation
     * \param _desc description à donner à la relation
     */
    void setDescription(QString _desc){if (description != "Relation forte") description = _desc;}

    /*! \class Iterator
     * \brief Classe Iterator de Relation
     *
     * Permet de parcourir de tableau de couple d'une relation
     */
    class Iterator {
    public:
        /*!
         * \brief Surcharge de l'operateur *
         * \return un pointeur sur le couple courant du tableau
         */
        Couple* operator *(){return *current;}
        /*!
         * \brief Surcharge de l'operateur ++ (préfixé)
         * \return un pointeur sur le couple suivant
         */
        Couple* operator ++(){
            if(last == 0)
                throw NotesException(QString("Erreur, arrive au bout."));
            --last;
            return *(++current);
        }
        /*!
         * \brief Surcharge de l'operateur ++ (postfixé)
         * \return un pointeur sur le couple suivant
         */
        Couple* operator ++(int){
            if(last == 0)
                throw NotesException(QString("Erreur, arrive au bout."));
            Couple* save = *current;
            ++current;
            --last;
            return save;
        }
        /*!
         * \brief Permet de savoir si on est arrivé sur le dernier élément du tableau
         * \return true si il ne reste plus d'élément à parcourir
         */
        bool isdone(){return last == 0;}
    private:
        Couple** current; /*!< pointeur sur le couple courant */
        unsigned int last; /*!< nombre de couples restant à parcourir */
        friend class Relation;
        /*!
         * \brief Constructeur d'Iterator
         * \param _tab tableau de couple à parcourir
         * \param _nb_max nombre maximum de couple pouvant être mis dans le tableau
         */
        Iterator(Couple** _tab, unsigned int _nb_max): current(_tab), last(_nb_max) {}
    };

    /*!
     * \brief Getter de l'iterator
     * Instancie un itérateur
     * \return
     */
    Iterator getIterator() {
        return Iterator(tabCouples, nbCouples);
    }

    /*!
     * \brief Sauvegarde de la relation en XML
     * \param stream pointeur sur le QXmlStreamWriter
     */
    void saveXML(QXmlStreamWriter* stream);

private:
    QString titre; /*!< titre de la relation*/
    QString description; /*!< description de la relation*/
    Couple** tabCouples; /*!< tableau de pointeur sur des couples */
    unsigned int nbCouples; /*!< nombre de couples dans le tableau */
    unsigned int nbMaxCouples; /*!< nombre maxium de couples dans le tableau*/
    bool orientee; /*!< booléen concernant l'orientation de la relation */

    void operator=(const Relation&){}
    Relation(const Relation&){}

};

/*! \class RelationManager
 * \brief Le manager de relation
 */
class RelationManager{
public:
    /*!
     * \brief Ajoute une relation
     * \param rel pointeur sur la relation à ajouter
     */
    void addRelation(Relation* rel);
    /*!
     * \brief Supprime une relation
     * \param _titre titre de la relation à supprimer
     */
    void deleteRelation(QString _titre);
    /*!
     * \brief Getter de relation
     * \param _titre titre de la relation à trouver
     * \return référence sur la relation trouvée
     */
    Relation& getRelation(QString _titre);

    /*!
     * \brief Crée la relation Référence si elle n'existe pas
     */
    void createReference();
    /*!
     * \brief Met à jour la relation Référence par rapport au texte du note
     * \param idNote id de la note
     * \param texte texte de la note
     * \return true si tout va bien, false si Note(s) dans la ref n'existe pas.
     */
    bool updateReference(const QString& idNote, const QString& texte); // renvoie true si tout va bien, false si Note(s) dans la ref n'existe pas.
    /*!
     * \brief Permet de savoir si une relation existe
     * \param _titre titre de la relation à tester
     * \return true si la relation existe, false sinon
     */
    bool existeRelation(QString _titre);

    /*!
     * \brief Méthode static qui donne l'instance de RelationManager
     * Crée une nouvelle instance si elle n'existe pas
     * \return référence sur RelationManager
     */
    static RelationManager& donneInstance(){
        if (!instance)
            instance = new RelationManager();
        return *instance;
    }

    /*!
     * \brief Supprime l'instance de RelationManager si elle existe
     */
    static void supprimeInstance(){
        if (instance){
            delete instance;
            instance = nullptr;
        }
    }

    /*! \class Iterator
     * \brief Classe Iterator pour parcourir les relations de relationManager
     */
    class Iterator {
    public:
        /*!
         * \brief Surcharge de l'operateur *
         * \return un pointeur sur la relation courante
         */
        Relation* operator *(){return *current;}
        /*!
         * \brief Surcharge de l'operateur ++ (préfixé)
         * \return pointeur sur la relation suivante
         */
        Relation* operator ++(){
            if(last == 0)
                throw NotesException(QString("Erreur, arrive au bout."));
            --last;
            return *(++current);
        }
        /*!
         * \brief Surcharge de l'operateur ++ (postfixé)
         * \return pointeur sur la relation suivante
         */
        Relation* operator ++(int){
            if(last == 0)
                throw NotesException(QString("Erreur, arrive au bout."));
            Relation* save = *current;
            ++current;
            --last;
            return save;
        }
        /*!
         * \brief Permet de savoir si on se trouve à la fin du tableau
         * \return true s'il ne reste pas de relation suivante, false sinon
         */
        bool isdone(){return last == 0;}
    private:
        Relation** current; /*!< pointeur sur l'élément courant du tableau*/
        unsigned int last; /*!< nombre de relations restantes à parcourir */
        friend class RelationManager;
        /*!
         * \brief Constructeur d'Iterator
         * \param _tab tableau de pointeur de relations
         * \param _nb_max nombre maximum de relations dans le tableau
         */
        Iterator(Relation** _tab, unsigned int _nb_max): current(_tab), last(_nb_max) {}
    };
    /*!
     * \brief Getter d'Iterator
     * Instancie un iterator
     */
    Iterator getIterator() {
        return Iterator(tabRelations, nbRelations);
    }
    /*!
     * \brief Sauvegarde de toutes les relations en XML
     * \param stream pointeur sur QXmlStreamWriter
     */
    void saveEveryRelationsXML(QXmlStreamWriter* stream);
    /*!
     * \brief Chargement des relations à partir de l'XML
     * \param stream QXmlStreamWriter
     */
    void LoadRelationXML(QXmlStreamReader* stream);
private:
    Relation** tabRelations; /*!< tableau de pointeur sur des relations */
    unsigned int nbRelations; /*!< nombre de relations dans le tableau */
    unsigned int nbMaxRelations; /*!< nombre maximum de relation dans le tableau */

    static RelationManager* instance; /*!< attribut static, instance de relationManager*/

    /*!
     * \brief Constructeur de RelationManager
     */
    RelationManager();
    /*!
    * \brief Destructeur de RelationManager
    */
    ~RelationManager();

    /*!
     * \brief Constructeur de recopie de RelationManager
     *
     * vide pour empecher la recopie
     *
     */
    RelationManager(const RelationManager&){}
    /*!
     * \brief Surcharge de l'operateur =
     *
     * vide pour empecher la recopie
     */
    void operator=(const RelationManager&){}

};

#endif // RELATIONS_H
