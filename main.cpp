#include <iostream>

#include "Graph.hpp"

using namespace std;

int main(){
	Graph graphe(6);
	srand(time(NULL));
	graphe.generation_aleatoire1();
	graphe.affiche();
	graphe.degeneracy();

	return 0;
}
