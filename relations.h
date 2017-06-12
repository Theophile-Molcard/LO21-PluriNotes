#ifndef RELATIONS_H
#define RELATIONS_H

#include <QString>
#include <QXmlStreamWriter>
/*!
* \file relations.h
* \brief Définition des classes utiles aux relations
* \author Théophile Maxime Théo
* \version 0.99
*/


/*! \class RelException
 * \brief Classe pour gérer les execptions propres aux relations
 */
class RelException{
public:
    /*!
     * \brief Contructeur de RelException
     * \param message information concernant l'exception
     */
    RelException(const QString& message):info(message){}
    /*!
     * \brief Getter de l'information d'une RelException
     * \return information de la RelException
     */
    QString getInfo() const { return info; }
private:
    QString info; /*!< information de la RelException */
};


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
                throw RelException(QString("Erreur, arrive au bout."));
            --last;
            return *(++current);
        }
        /*!
         * \brief Surcharge de l'operateur ++ (postfixé)
         * \return un pointeur sur le couple suivant
         */
        Couple* operator ++(int){
            if(last == 0)
                throw RelException(QString("Erreur, arrive au bout."));
            Couple* save = *current;
            ++current;
            --last;
            return save;
        }
        bool isdone(){return last == 0;}
    private:
        Couple** current;
        unsigned int last;
        friend class Relation;
        Iterator(Couple** _tab, unsigned int _nb_max): current(_tab), last(_nb_max) {}
    };

    Iterator getIterator() {
        return Iterator(tabCouples, nbCouples);
    }

    void saveXML(QXmlStreamWriter* stream);

private:
    QString titre;
    QString description;
    Couple** tabCouples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
    bool orientee;

};

class RelationManager{
public:

    void addRelation(Relation* rel);
    void deleteRelation(QString _titre);
    Relation& getRelation(QString _titre);
    void createReference();
    bool updateReference(const QString& idNote, const QString& texte); // renvoie true si tout va bien, false si Note(s) dans la ref n'existe pas.
    bool existeRelation(QString _titre);

    static RelationManager& donneInstance(){
        if (!instance)
            instance = new RelationManager();
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
        Relation* operator *(){return *current;}
        Relation* operator ++(){
            if(last == 0)
                throw RelException(QString("Erreur, arrive au bout."));
            --last;
            return *(++current);
        }
        Relation* operator ++(int){
            if(last == 0)
                throw RelException(QString("Erreur, arrive au bout."));
            Relation* save = *current;
            ++current;
            --last;
            return save;
        }
        bool isdone(){return last == 0;}
    private:
        Relation** current;
        unsigned int last;
        friend class RelationManager;
        Iterator(Relation** _tab, unsigned int _nb_max): current(_tab), last(_nb_max) {}
    };

    Iterator getIterator() {
        return Iterator(tabRelations, nbRelations);
    }

    void saveEveryRelationsXML(QXmlStreamWriter* stream);
    void LoadRelationXML(QXmlStreamReader* stream);
private:
    Relation** tabRelations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;

    static RelationManager* instance;

    RelationManager();
    ~RelationManager();

    RelationManager(const RelationManager&){}
    void operator=(const RelationManager&){}

};

#endif // RELATIONS_H
