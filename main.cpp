#include <iostream>

#include "Graph.hpp"

using namespace std;

int main(){
	Graph graphe(6);
	srand(time(NULL));
	graphe.generation_aleatoire2();
	graphe.affiche();
	graphe.degeneracy();
	graphe.bron_kerbosch_degeneracy();

	return 0;
}
