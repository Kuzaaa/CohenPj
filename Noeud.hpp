#ifndef Noeud_hpp
#define Noeud_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

class Noeud;
class Noeud {
private:
    int valeur;
    std::unordered_map<int,Noeud> fils;
public:
    Noeud();
    Noeud(int n);
    ~Noeud();
protected:

};


#endif
