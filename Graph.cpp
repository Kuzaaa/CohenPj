#include <iterator>
#include <algorithm>
#include <unordered_set>
#include "Graph.hpp"
#include "suffix_hash_map.hpp"

using namespace std;
using MySet = std::unordered_set<std::vector<int>, VectorHash>;

Graph::Graph(int n)  {
	nb_sommet = n;
	k_degen = 0;
}

Graph::Graph(Graph graphe,int i){
	k_degen = 0;
	liste_voisins.push_back(graphe.liste_voisins[i]);
	correspondanceOrignFct.push_back(i);

	//On stock tous les voisins inferieurs dans une liste.
	//Avec leur indice, on peut retrouver leur valeur.
	//De plus, on initialise les listes_voisins
	for(auto voisin : graphe.liste_voisins[i]){
		auto placeI = find(graphe.list_degen.begin(),graphe.list_degen.end(), i);
		auto result = find(placeI, graphe.list_degen.end(), voisin);
		if(result != graphe.list_degen.end()){
			liste_voisins.push_back(graphe.liste_voisins[voisin]);
			correspondanceOrignFct.push_back(voisin);
		}
	}

	vector<vector<int>> newListe_voisins;
	for(auto L: liste_voisins){
		vector<int> newListe;
		for(auto i : L){
			auto result = find(correspondanceOrignFct.begin(), correspondanceOrignFct.end(), i);
		    if (result != correspondanceOrignFct.end()) {
				newListe.push_back(i);
			}
		}
		newListe_voisins.push_back(newListe);
	}



	nb_sommet = (int) correspondanceOrignFct.size();

	for(int j=0;j<(int) newListe_voisins.size();j++){
		for(int k=0;k<(int) newListe_voisins[j].size();k++){
			auto result = find(correspondanceOrignFct.begin(),correspondanceOrignFct.end(), newListe_voisins[j][k]);
			newListe_voisins[j][k] = distance(correspondanceOrignFct.begin(), result);
		}
	}

	liste_voisins = newListe_voisins;

}

Graph::~Graph() {}

vector<int> Graph::formatOrigin(vector<int> liste){
	vector<int> newListe;

	for(int k=0;k<(int) liste.size();k++){
		newListe.push_back(correspondanceOrignFct[liste[k]]);
	}

	correspondanceOrignFct.clear();
	return newListe;
}

void Graph::generation_aleatoire1(){
	double p = frand_0_1(); //p flottant aléatoire entre 0 et 1
	int sommet,voisin;
	double p_apparition;
	vector<int> voisins;

	cout << "p=" << p << endl;

	for(sommet=0;sommet<nb_sommet;sommet++){
		vector<int> liste;
		liste_voisins.push_back(liste);
	}

	for(sommet=0;sommet<nb_sommet;sommet++){ //pour chaque sommet
		for(voisin=sommet+1;voisin<nb_sommet;voisin++){ //pour chaque voisin potentiel
			p_apparition = frand_0_1();//probabilité d'apparition aléatoire entre 0 et 1

			cout << "sommet:" << sommet <<"voisin:" << voisin << "p=" << p_apparition << endl;

			if(p_apparition <= p){
				liste_voisins[sommet].push_back(voisin); //on ajoute le voisin dans le sommet
				liste_voisins[voisin].push_back(sommet); //on ajoute le sommet dans le voisin
			}
		}
	}
}


void Graph::generation_aleatoire2(){
	double p, p_apparition;
	int i(0), m(2), sommet, voisin, nb_tot_degres(0), deg[nb_sommet];
	vector<int> voisins;

	//Initialise un tableau de degrés
	for(auto cpt=0; cpt<nb_sommet; cpt++){
		deg[cpt] = 0;
	}

	//initialise les listes de voisins
	for(sommet=0;sommet<nb_sommet;sommet++){
		vector<int> sommets;
		liste_voisins.push_back(sommets);
	}

	//Initialise le graphe triangle de départ
	if(nb_sommet>=3){
		for(sommet=0;sommet<3;sommet++){
			for(voisin=sommet+1;voisin<3;voisin++){
				liste_voisins[sommet].push_back(voisin);
				liste_voisins[voisin].push_back(sommet);
				deg[sommet]++;
				deg[voisin]++;
				nb_tot_degres+=2;
			}
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
					liste_voisins[voisin].push_back(sommet);
					liste_voisins[sommet].push_back(voisin);
					deg[sommet]++;
					deg[voisin]++;
					nb_tot_degres+=2;
					i++;
					//Si on a créé 2 nouvelles arêtes, on passe au sommet suivant
					if(i==m){
						voisin=sommet;
					}
				}
			}
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
	while (!P.empty()){
		int sommet = P[0];
		std::vector<int> newP, newR, newX;

		//R⋃sommet
		newR = R;
		newR.push_back(sommet);

		//P⋂⌈(sommet)
		for(auto i : P){
			auto result = find(liste_voisins[sommet].begin(), liste_voisins[sommet].end(), i);
		    if (result != liste_voisins[sommet].end()) {
				newP.push_back(i);
			}
		}

		//X⋂⌈(sommet)
		for(auto i : X){
			auto result = find(liste_voisins[sommet].begin(),liste_voisins[sommet].end(),i);
			if (result != liste_voisins[sommet].end()){
				newX.push_back(i);
			}
		}

		//Appel de récurrence
		BronKerbosch(newP,newR,newX);

		//P\sommet
		P.erase(remove(P.begin(), P.end(), sommet), P.end());

		//X⋃sommet
		X.push_back(sommet);
	}
}

void Graph::liste_adj_degen(){
	for(int i  = 0; i<nb_sommet; i++){
		vector<int> voisins_degen;
		for(auto it = list_degen.rbegin(); it != list_degen.rend(); it++){
			for(auto sommet : liste_voisins[i]){
				if(*it == sommet){
					voisins_degen.push_back(sommet);
				}
			}
		}

		liste_adj_d.push_back(voisins_degen);
	}
	cout << endl;
	for(auto voisins : liste_adj_d){
		cout << "[ ";
		for(auto sommet : voisins){
			cout << sommet << ", ";
		}
		cout << "]" << endl;
	}
}

void Graph::degeneracy(){
	int i;

	//liste degres sommet par sommet a update
	vector<int> degrestmp;

	//init degres tmp a num sommet et 0
	for(unsigned int i = 0; i<liste_voisins.size(); i++){
		degrestmp.push_back(0);
	}

	//calcule des degres des sommets
	i = 0;
	for(auto voisins : liste_voisins){
		for(unsigned int cpt = 0; cpt<voisins.size(); cpt++){
			degrestmp[i]++;
		}
		i++;
	}

	for(unsigned int j = 0; j<liste_voisins.size(); j++){

		i=0;

		//Liste de degres
		vector<vector<int>> D;

		//init de D
		for(unsigned int cpt = 0; cpt<degrestmp.size(); cpt++){
			vector<int> desc_sommet;
			D.push_back(desc_sommet);
		}

		//Remplissage de D
		i=0;
		for(auto sommet : degrestmp){
			if(sommet != -1){
				D[sommet].push_back(i);
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
			list_degen.push_back(D[cpt][0]);
			if(k_degen < degrestmp[D[cpt][0]]){
				k_degen = degrestmp[D[cpt][0]];
			}
			degrestmp[list_degen[list_degen.size()-1]] = -1;

			i=0;
			for(auto voisins : liste_voisins){
				for(auto sommet : voisins){
					if(sommet == list_degen[list_degen.size()-1] && degrestmp[i] != -1){
						degrestmp[i]--;
					}
				}
				i++;
			}
		}
	}
	cout << "k : " << k_degen << endl;
	cout << "List degeneracy : ";
	for(auto entier : list_degen){

		cout << entier << ", ";
	}
	cout << endl;
}


void Graph::bron_kerbosch_degeneracy(){

	int j;

	for(auto i : list_degen){
		std::vector<int> P;
		std::vector<int> X;
		for(auto sommet : liste_voisins[i]){
			P.push_back(sommet);
		}
		j = 0;
		for(auto voisins : liste_voisins){
			for(auto sommet : voisins){
				if(sommet == i){
					X.push_back(j);
				}
			}
			j++;
		}
		//Print X et P au cas ou
		cout << "i: " << i << endl;
		cout << "P: ";
		for(auto tmp : P){
			cout << tmp;
		}
		cout << endl;
		cout << "X: ";
		for(auto tmp : X){
			cout << tmp;
		}
		cout << endl << endl;



		//Later :
		std::vector<int> R;
		R.push_back(i);
		bron_kerbosch_pivot(P, R, X);


	}
	cout << endl;
	for(auto clique : clique_maximal){
		cout << "[ ";
		for(auto sommet : clique){
			cout << sommet << ", ";
		}
		cout << "]" << endl;
	}
}

void Graph::bron_kerbosch_pivot(std::vector<int> P, std::vector<int> R, std::vector<int> X){

	//P union X
	std::vector<int> PuX;
	for(auto sommetP : P){
		PuX.push_back(sommetP);
	}
	for(auto sommetX : X){
		PuX.push_back(sommetX);
	}

	//Si PuX is empty
	if (PuX.empty()){
		clique_maximal.push_back(R);
	}
	else{
		//Choosing best u maximizing |P n voisins(u)|
		int max = 0,cpt = 0;
		int best_pivot = PuX[0];
		for(auto pivot : PuX){
			for(auto sommet : liste_voisins[pivot]){
				for(auto p : P){
					if(p == sommet){
						cpt++;
					}
				}
			}
			if(cpt > max){
				max = cpt;
				best_pivot = pivot;
			}
			cpt = 0;
		}

		//P/voisins(u)
		int test;
		std::vector<int> P_sans_voisins_u;
		for(auto p : P){
			test = 1;
			for(auto sommet : liste_voisins[best_pivot]){
				if(p == sommet){
					test = 0;
				}
			}
			if(test == 1){
				P_sans_voisins_u.push_back(p);
			}
		}

		for(auto v : P_sans_voisins_u){

			std::vector<int> P_n_voisins_v;
			/*
			for(auto sommet : liste_voisins[v]){
				for(auto p : P){
					if(sommet == p){
						P_n_voisins_v.push_back(sommet);
					}
				}
			}*/

			std::vector<int> X_n_voisins_v;
			/*
			for(auto sommet : liste_voisins[v]){
				for(auto x : X){
					if(sommet == x){
						X_n_voisins_v.push_back(sommet);
					}
				}
			}*/


			//P⋂⌈(sommet)
			for(auto i : P){
				auto result = std::find(std::begin(liste_voisins.at(v)),std::end(liste_voisins.at(v)),i);
				if (result != std::end(liste_voisins.at(v))){
					P_n_voisins_v.push_back(i);
				}
			}

			//P⋂⌈(sommet)
			for(auto i : X){
				auto result = std::find(std::begin(liste_voisins.at(v)),std::end(liste_voisins.at(v)),i);
				if (result != std::end(liste_voisins.at(v))){
					X_n_voisins_v.push_back(i);
				}
			}

			R.push_back(v);

			cout << endl;
			cout << "[ ";
			for(auto sommet : R){
				cout << sommet << ", ";
			}
			cout << "]" << endl;


			bron_kerbosch_pivot(P_n_voisins_v, R, X_n_voisins_v);


			//P \ sommet
			P.erase(std::remove(P.begin(),P.end(),v), P.end());
			//X u sommet
			X.push_back(v);
			/*
			for(auto it = P.begin(); it != P.end(); it++){
				if(*it == v){
					P.erase(it);
				}
			}
			X.push_back(v);*/
		}
	}
}


void Graph::maximal_clique_enumeration1(){
	degeneracy();
	cout << "k=" << k_degen << endl;
	liste_adj_degen();
	cout << "liste adjacence degen : " << endl;
	for(auto voisins : liste_adj_d){
		cout << "[ ";
		for(auto sommet : voisins){
			cout << sommet << ", ";
		}
		cout << "]" << endl;
	}
	MySet T;
	for(int j=0;j<nb_sommet;j++){
		//clique maximale de G(j)
		Graph sous_graphe(*this,j);
		cout << "sous graphe de " << j << endl;
		//sous_graphe.affiche();
		vector<int> P;
		vector<int> R;
		vector<int> X;
		for(int i=0; i<sous_graphe.nb_sommet; i++){
			P.push_back(i);
		}
		sous_graphe.BronKerbosch(P,R,X);
		if(sous_graphe.clique_maximal.empty()){
			cout << "pas de clique max" << endl;
		}
		for(auto K : sous_graphe.clique_maximal){
			vector<int> K_ok = sous_graphe.formatOrigin(K);
			/*cout << "K_ok : " << endl;
			cout << "[ ";
			for(auto sommet : K_ok){
				cout << sommet << ", ";
			}
			cout << "]" << endl;*/
			//ordonner les sommets
			int occ[nb_sommet]={0};
			vector<int> k_ordonne;
			for(auto i : K_ok){
				occ[i]=1;
			}
			for(auto i : this->list_degen){
				if(occ[i]!=0){
					k_ordonne.push_back(i);
					occ[i]=0;
				}
			}

			//chercher K dans T

			auto recherche = T.find(k_ordonne);
			if (recherche == T.end()){ //pas de match
				//insérer K dans T
				vector<vector<int>> k_suffixe = get_suffixe(k_ordonne);
				for(auto suffixe : k_suffixe){
					T.insert(suffixe);
				}
				cout << "k_ordonne : " << endl;
				cout << "[ ";
				for(auto sommet : k_ordonne){
					cout << sommet << ", ";
				}
				cout << "]" << endl;
			}
		}
	}
}

void Graph::maximal_clique_enumeration2(){
	degeneracy();
	cout << "k=" << k_degen << endl;
	liste_adj_degen();
	cout << "liste adjacence degen : " << endl;
	for(auto voisins : liste_adj_d){
		cout << "[ ";
		for(auto sommet : voisins){
			cout << sommet << ", ";
		}
		cout << "]" << endl;
	}
	for(auto j=0;j<nb_sommet;j++){
		//clique maximale de G(j)
		Graph sous_graphe(*this,j);
		cout << "sous graphe de " << j << endl;
		//sous_graphe.affiche();
		vector<int> P;
		vector<int> R;
		vector<int> X;
		for(int i=0; i<sous_graphe.nb_sommet; i++){
			P.push_back(i);
		}
		sous_graphe.BronKerbosch(P,R,X);
		if(sous_graphe.clique_maximal.empty()){
			cout << "pas de clique max" << endl;
		}
		for(auto K : sous_graphe.clique_maximal){
			vector<int> K_ok = sous_graphe.formatOrigin(K);
			for(auto x : K_ok){
				//voisins de x avec rang degen inférieur
				vector<int> voisins_lower_degen_x;
				int cpt_liste_voisins = liste_voisins[x].size()-1;
				int cpt_degen = 0;
				while(cpt_degen < j && cpt_liste_voisins >=0){
					if(liste_voisins[x][cpt_liste_voisins]==list_degen[cpt_degen]){
						voisins_lower_degen_x.push_back(list_degen[cpt_degen]);
						cpt_liste_voisins--;
					}
					cpt_degen++;
				}

				bool reject_k = false;
				for(auto voisin_x : voisins_lower_degen_x){
					bool adjacent = true;
					if(adjacent){
						for(auto sommet_k : K_ok){
							if(sommet_k != x && adjacent){
								auto result = find(liste_voisins[sommet_k].begin(),liste_voisins[sommet_k].end(),voisin_x);
								if (result == liste_voisins[sommet_k].end()){
									adjacent = false;
								}
							}
						}
					}
					if(adjacent) {
						reject_k = true;
						break;
					}
				}
				if(!reject_k){
					cout << "K_ok : " << endl;
					cout << "[ ";
					for(auto sommet : K_ok){
						cout << sommet << ", ";
					}
					cout << "]" << endl;
				}

			}
		}
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
