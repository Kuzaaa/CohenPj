#ifndef Arbre_hpp
#define Arbre_hpp

#include <stdio.h>
#include "Noeud.hpp"

class Arbre {
private:
    Noeud root;
public:
    Arbre(Noeud root);
    ~Arbre();
    void printAll();
    void print(Noeud n);
    void ajout_noeud(Noeud noeud);
protected:

};


#endif
