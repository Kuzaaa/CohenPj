#include <iterator>
#include <algorithm>
#include "Graph.hpp"

using namespace std;

Graph::Graph(int n)  {
	nb_sommet = n;
}
Graph::~Graph() {}

void Graph::generation_aleatoire1(){
	double p = frand_0_1(); //p flottant aléatoire entre 0 et 1
	int sommet,voisin;
	double p_apparition;
	vector<int> voisins;

	cout << "p=" << p << endl;

	for(sommet=0;sommet<nb_sommet;sommet++){ //pour chaque sommet
		for(voisin=sommet+1;voisin<nb_sommet;voisin++){ //pour chaque voisin potentiel
			p_apparition = frand_0_1();//probabilité d'apparition aléatoire entre 0 et 1

			cout << "sommet:" << sommet <<"voisin:" << voisin << "p=" << p_apparition << endl;

			if(p_apparition <= p){
				voisins.push_back(voisin); //on ajoute le voisin
			}
		}
		liste_voisins.push_back(voisins); //on ajoute la liste de voisins du sommet
		voisins.clear();
	}

	
}


void Graph::generation_aleatoire2(){
	double p, p_apparition;
	int i(0), degeneracy(2), sommet, voisin, nb_tot_degres(0), deg[nb_sommet];
	vector<int> voisins;

	//Initialise un tableau de degrés
	for(auto cpt=0; cpt<nb_sommet; cpt++){
		deg[cpt] = 0;
	}

	//Initialise le graphe triangle de départ
	if(nb_sommet>=3){
		for(sommet=0;sommet<3;sommet++){
			for(voisin=sommet+1;voisin<3;voisin++){
				voisins.push_back(voisin);
				deg[sommet]++;
				deg[voisin]++;
				nb_tot_degres+=2;
			}
			liste_voisins.push_back(voisins);
			voisins.clear();
		}

		//Pour chaque nouveau sommet
		for(sommet=3;sommet<nb_sommet;sommet++){
			i=0;
			//On essaye de le lier aux sommets existants dans le graphe
			for(voisin=0; voisin<sommet; voisin++){
				p_apparition = (double) deg[voisin]/ (double) nb_tot_degres;
				p = frand_0_1();
				cout << "sommet:" << sommet <<" voisin:" << voisin << " p_app=" << p_apparition << " p="<< p << endl;
				if(p<p_apparition){
					//On ajoute la nouvelle arête
					liste_voisins.at(voisin).push_back(sommet);
					deg[sommet]++;
					deg[voisin]++;
					nb_tot_degres+=2;
					i++;
					//Si on a créé 2 nouvelles arêtes, on passe au sommet suivant
					if(i==degeneracy){
						voisin=sommet;
					}
				}
			}
			vector<int> sommets;
			liste_voisins.push_back(sommets);
		}
	}

	//Sinon il n'y a pas assez de sommet pour le graphe triangle initial
	else{
		cout << "Pas assez de sommets, il en faut 3 minimum." << endl;
	}
}

void Graph::BronKerbosch(std::vector<int> P, std::vector<int> R, std::vector<int> X){

	//Condition d'arrêt
	if (P.empty() && X.empty()){
		clique_maximal.push_back(R);
	}

	//Pour tous les sommets de P
	for(auto sommet : P){
		std::vector<int> newP, newR, newX;

		//R⋃sommet
		newR = R;
		newR.push_back(sommet);

		//P⋂⌈(sommet)
		for(auto i : P){
			auto result = std::find(liste_voisins[sommet].begin(), liste_voisins[sommet].end(), i);
		    if (result != liste_voisins[sommet].end()) {
				newP.push_back(i);
		    }
		}

		//P⋂⌈(sommet)
		for(auto i : X){
			auto result = std::find(std::begin(liste_voisins[sommet]),std::end(liste_voisins[sommet]),i);
			if (result != std::end(liste_voisins[sommet])){
				newX.push_back(i);
			}
		}

		//Appel de récurrence
		BronKerbosch(newP,newR,newX);

		//P\sommet
		P.erase(std::remove(P.begin(),P.end(),sommet), P.end());
		//X⋃sommet
		X.push_back(sommet);
	}
}

void Graph::degeneracy(){
	int i;

	//liste degres sommet par sommet a update
	std::vector<std::vector<int>> degrestmp;

	//init degres tmp a num sommet et 0
	for(unsigned int i = 0; i<liste_voisins.size(); i++){
		std::vector<int> desc_sommet;
		desc_sommet.push_back((int)i);
		desc_sommet.push_back(0);
		degrestmp.push_back(desc_sommet);
	}

	//calcule des degres des sommets
	i = 0;
	for(auto voisins : liste_voisins){
		for(auto sommet : voisins){
			degrestmp[i][1]++;
			degrestmp[sommet][1]++;
		}
		i++;
	}

	for(unsigned int j = 0; j<liste_voisins.size(); j++){

		i=0;

		//Liste de degres
		std::vector<std::vector<int>> D;

		//init de D
		for(auto sommet : degrestmp){
			std::vector<int> desc_sommet;
			D.push_back(desc_sommet);
		}

		//Remplissage de D
		i=0;
		for(auto sommet : degrestmp){
			if(sommet[1] != -1){
				D[sommet[1]].push_back(i);
			}
			i++;
		}

		int cpt = 0;

		//tant que D[cpt] est vide on passe a cpt+1
		while(cpt<nb_sommet && D[cpt].empty() == 1){
			cpt++;
		}

		//Test si cpt < nb_sommet
		//Cas D !(empty)
		if(cpt < nb_sommet){

			//ajoute le premier sommet trouv� dans ordre
			list_degeneracy.push_back(D[cpt][0]);
			degrestmp[list_degeneracy[list_degeneracy.size()-1]][1] = -1;

			i=0;
			for(auto voisins : liste_voisins){
				for(auto sommet : voisins){
					if(sommet == list_degeneracy[list_degeneracy.size()-1] && degrestmp[i][1] != -1){
						degrestmp[i][1]--;
					}
					if(list_degeneracy[list_degeneracy.size()-1] == i && degrestmp[sommet][1] != -1){
						degrestmp[sommet][1]--;
					}
				}
				i++;
			}
		}
	}
	cout << "List degeneracy : ";
	for(auto entier : list_degeneracy){

		cout << entier << ", ";
	}
	cout << endl;
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
