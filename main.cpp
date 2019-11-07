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
	graphe.BronKerbosch(P, R, X);

	cout << "List clique maximale : " << endl;
	for(auto clique : graphe.clique_maximal){
		cout << "[ ";
		for(auto sommet : clique){
			cout << sommet << ", ";
		}
		cout << "]" << endl;
	}

	graphe.degeneracy();
	//graphe.bron_kerbosch_degeneracy();

	return 0;
}
