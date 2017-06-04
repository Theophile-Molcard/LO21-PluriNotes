#ifndef RELATIONS_H
#define RELATIONS_H

#include <QString>

class Couple{
    friend class Relation;
public:
    QString getx(){return x;}
    QString gety(){return y;}
private:
    Couple(QString _x, QString _y): x(_x), y(_y){}
    QString x;
    QString y;
};


class Relation{
public:
    Relation(QString _titre, QString _desc, bool _orientee = true): titre(_titre), description(_desc), tabCouples(nullptr), nbCouples(0), nbMaxCouples(0), orientee(_orientee){}
    ~Relation();
    void addCouple(QString _x, QString _y);
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

private:
    QString titre;
    QString description;
    Couple** tabCouples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
    bool orientee;

};

#endif // RELATIONS_H
