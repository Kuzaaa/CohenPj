#include <iterator>
#include <algorithm>
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
		clique_maximal.push_back(P);
	}

	//Pour tous les sommets de P
	for(auto sommet : P){
		std::vector<int> newP, newR, newX;

		//R⋃sommet
		newR = R;
		newR.push_back(sommet);

		//P⋂⌈(sommet)
		for(auto i : P){
			auto result = std::find(std::begin(liste_voisins.at(sommet)),std::end(liste_voisins.at(sommet)),i);
			if (result != std::end(liste_voisins.at(sommet))){
				newP.push_back(i);
			}
		}

		//P⋂⌈(sommet)
		for(auto i : X){
			auto result = std::find(std::begin(liste_voisins.at(sommet)),std::end(liste_voisins.at(sommet)),i);
			if (result != std::end(liste_voisins.at(sommet))){
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
