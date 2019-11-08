#include <iostream>

#include "Graph.hpp"

using namespace std;

int main(){
	vector<int> P;
	vector<int> R;
	vector<int> X;

	Graph graphe(6);
	srand(time(NULL));
	graphe.generation_aleatoire1();

	for(int i=0; i<graphe.nb_sommet; i++){
		P.push_back(i);
	}
	graphe.affiche();

	cout << "Graphe2: avec sommet 3:" << endl;
	Graph graphe2(3,graphe);
	graphe2.affiche();

	//graphe.degeneracy();
	//graphe.liste_adj_degen();
	//graphe.bron_kerbosch_degeneracy();

	return 0;
}
