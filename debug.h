#ifndef DEBUG_H
#define DEBUG_H

//Fichier debug pour le mode console



//Exemple d'utilisation
namespace DebugTest {

void Debug();
void Debug_theophile();
    class A{
    public:
        int a;
        A(int _a): a(_a){}

        virtual int getA() {return a;}
    };
    class B: public A{
    public:
        int b;
        B(int _a, int _b): A(_a), b(_b){}

        int getB() {return b;}
        int getA(){return b;}
    };
}





#endif // DEBUG_H
