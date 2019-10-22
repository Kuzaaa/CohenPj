#include <iostream>

#include "Graph.hpp"

using namespace std;

int main(){
	Graph graphe(5);
	srand(time(NULL));
	graphe.generation_aleatoire1();
	graphe.affiche();
	return 0;
}
