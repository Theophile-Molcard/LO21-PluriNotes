#ifndef RELATIONS_H
#define RELATIONS_H

#include <QString>
#include <QXmlStreamWriter>

class Couple{
    friend class Relation;
public:
    QString getx(){return x;}
    QString gety(){return y;}
    QString getLabel(){return label;}
    void setLabel(QString _label){label=_label;}
private:
    Couple(QString _x, QString _y, QString _label): x(_x), y(_y), label(_label){}
    QString x;
    QString y;
    QString label;

    void saveXML(QXmlStreamWriter* stream);
};


class Relation{
public:
    Relation(QString _titre, QString _desc, bool _orientee = true): titre(_titre), description(_desc), tabCouples(nullptr), nbCouples(0), nbMaxCouples(0), orientee(_orientee){}
    ~Relation();
    void addCouple(QString _x, QString _y, QString _label = "default");
    void deleteCouple(QString _x, QString _y);

    QString getTitre(){return titre;}
    QString getDescription(){return description;}

    void setTitre(QString _titre){if (titre != "Reference") titre=_titre;}
    void setDescription(QString _desc){if (description != "Relation forte") description = _desc;}

    class Iterator {
    public:
        Couple* operator *(){return *current;}
        Couple* operator ++(){
            if(last == 0)
                throw "il faut faire une classe d'exceptions";
            --last;
            return *(++current);
        }
        Couple* operator ++(int){
            if(last == 0)
                throw "il faut faire une classe d'exceptions";
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
                throw "il faut faire une classe d'exceptions";
            --last;
            return *(++current);
        }
        Relation* operator ++(int){
            if(last == 0)
                throw "il faut faire une classe d'exceptions";
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
