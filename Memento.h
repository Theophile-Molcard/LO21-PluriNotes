#ifndef MEMENTO_H
#define MEMENTO_H

using namespace std;

class Memento {
public:
private:
    Note* note;
};

class Gardien {
public:
private:
    Memento* mementosListe;

};



#endif // MEMENTO_H
