#ifndef Noeud_hpp
#define Noeud_hpp

#include <stdio.h>
#include <vector>

class Noeud {
private:
    int valeur;
    std::vector<Noeud> noeuds;
public:
    Noeud();
    Noeud(int n);

    ~Noeud();
protected:

};


#endif
