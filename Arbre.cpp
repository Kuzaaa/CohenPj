#include "Arbre.hpp"
#include <iostream>
using namespace std;

Arbre::Arbre(Noeud n){
    root = n;
}

Arbre::~Arbre() {}

void Arbre::printAll(){
    print(root);
}

void Arbre::print(Noeud n){
}
