#ifndef Noeud_hpp
#define Noeud_hpp

#include <stdio.h>
#include <vector>
#include <unordered_set>

class Noeud {
private:
    int valeur;
    std::unordered_set<Noeud> noeuds;
public:
    Noeud();
    Noeud(int n);
    bool operator ==(const Noeud & obj) const{
        if (valeur == obj.valeur)
            return true;
        else
            return false;
    }
    int getValeur() const
    {
        return valeur;
    }
    ~Noeud();
protected:

};


#endif
