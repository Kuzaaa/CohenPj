#include <iostream>
#include <time.h>
#include <cmath>
#include <chrono>
#include "Graph.hpp"

using namespace std;

int main(){
	vector<int> P;
	vector<int> R;
	vector<int> X;

	Graph graphe(20000);
	srand(time(NULL));
	graphe.generation_aleatoire2();

	for(int i=0; i<=graphe.nb_sommet; i++){
		P.push_back(i);
	}

	//graphe.affiche();
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	graphe.BronKerbosch(P, R, X);
	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	cout << "Temps d'execution: " << sec.count() << "secondes." << endl;

	/*cout << "List clique maximale : ";
	for(auto clique : graphe.clique_maximal){
		cout << "[ ";
		for(auto sommet : clique){
			cout << sommet << ", ";
		}
		cout << "]" << endl;
	}*/

	return 0;
}
