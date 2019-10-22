#include "Graph.hpp"

using namespace std;

Graph::Graph()  {}
Graph::~Graph() {}

void Graph::generation_aleatoire1(){
	double alea = frand_0_1();
	cout << alea << endl;
}

double Graph::frand_0_1(){
	return rand()/(double)RAND_MAX ;
}
