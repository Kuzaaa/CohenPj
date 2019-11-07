#include <iostream>

#include "Graph.hpp"

using namespace std;

int main(){
	vector<int> P;
	vector<int> R;
	vector<int> X;

	Graph graphe(5);
	srand(time(NULL));
	graphe.generation_aleatoire1();
<<<<<<< HEAD
=======

	for(int i=0; i<=graphe.nb_sommet; i++){
		P.push_back(i);
	}

>>>>>>> Raph/BronKerbosch
	graphe.affiche();
	graphe.BronKerbosch(P, R, X);

	cout << "List clique maximale : ";
	for(auto clique : graphe.clique_maximal){
		cout << "[ ";
		for(auto sommet : clique){
			cout << sommet << ", ";
		}
		cout << "]" << endl;
	}

	return 0;
}
