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
    void printAll();//appel initial de print avec root en param
    void print(Noeud n);//permet de visualiser un noeud, appel récursifs sur ses fils
    void ajout_noeud(Noeud noeud);//on pleure
protected:

};


#endif
