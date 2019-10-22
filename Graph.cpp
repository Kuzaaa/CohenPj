#include "Graph.hpp"

using namespace std;

Graph::Graph(int n)  {
	nb_sommet = n;
}
Graph::~Graph() {}

void Graph::generation_aleatoire1(){
	double p = frand_0_1();
	int sommet,voisin;
	double p_apparition;
	vector<int> voisins;
	cout << "p=" << p << endl;
	for(sommet=0;sommet<nb_sommet;sommet++){
		for(voisin=sommet+1;voisin<nb_sommet;voisin++){
			p_apparition = frand_0_1();
			cout << "sommet:" << sommet <<"voisin:" << voisin << "p=" << p_apparition << endl;
			if(p_apparition <= p){
				voisins.push_back(voisin);
			}
		}
		liste_voisins.push_back(voisins);
		voisins.clear();
	}
}

double Graph::frand_0_1(){
	return rand()/(double)RAND_MAX ;
}

void Graph::affiche(){
	for(auto voisins : liste_voisins){
		cout << "[ ";
		for(auto sommet : voisins){
			cout << sommet << ", ";
		}
		cout << "]" << endl;
	}
}
