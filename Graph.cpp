#include <iterator>
#include <algorithm>
#include <unordered_set>
#include "Graph.hpp"
#include "suffix_hash_map.hpp"

using namespace std;
//set personnalisÃ© pour pouvoir hasher des vector<int>
using MySet = std::unordered_set<std::vector<int>, VectorHash>;

Graph::Graph(int n)  {
	nb_sommet = n;
	k_degen = 0;
}

//Permet de construire un sous sous-graphe a partir d'un Graphe graphe et d'un entier e
Graph::Graph(Graph* graphe,int e){

	//On initialise k_degen
	k_degen = 0;

	//On rÃ©cupÃ¨re la liste de voisin de e, et on rentre sa valeur dans la liste de correspondance
	liste_voisins.push_back(graphe->liste_voisins[e]);
	correspondanceOrignFct.push_back(e);

	//On stock tous les voisins qui sont situÃ©s aprÃ¨s dans la liste de degenerescence.
	//De plus, on recupere les listes_voisins de tout ceux-ci et on rentre leur valeur dans la liste de correspondance
	for(auto voisin : graphe->liste_voisins[e]){
		auto placeI = find(graphe->list_degen.begin(),graphe->list_degen.end(), e);
		auto result = find(placeI, graphe->list_degen.end(), voisin);
		if(result != graphe->list_degen.end()){
			liste_voisins.push_back(graphe->liste_voisins[voisin]);
			correspondanceOrignFct.push_back(voisin);
		}
	}

	//On cree des nouvelles listes de voisins qui remplaceront celles copiees Ã  l'initialisation
	//Dont les seuls sommets gardes seront ceux dans la liste de correspondance
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


	//On initialise nb_sommet
	nb_sommet = (int) correspondanceOrignFct.size();

	//On transforme la valeur des sommet afin que celle-ci corresponde Ã  leur indice dans la liste de correspondance
	for(int j=0;j<(int) newListe_voisins.size();j++){
		for(int k=0;k<(int) newListe_voisins[j].size();k++){
			auto result = find(correspondanceOrignFct.begin(),correspondanceOrignFct.end(), newListe_voisins[j][k]);
			newListe_voisins[j][k] = distance(correspondanceOrignFct.begin(), result);
		}
	}
	liste_voisins = newListe_voisins;
}

Graph::~Graph() {}

//Transforme les valeurs des sommets d'un sous-graphe avec les valeurs correspondante du graphe
void Graph::formatOrigin(vector<int>* liste,vector<int>* newListe){

	//On remplace les valeurs de tous les sommets de la liste avec ceux de la liste de correspondance rempli au prÃ©alable
	for(int k=0;k<(int) liste->size();k++){
		newListe->push_back(correspondanceOrignFct[(*liste)[k]]);
	}
	//On vide la liste de correspondance pour le prochain sous-graphe
	correspondanceOrignFct.clear();
}

void Graph::generation_aleatoire1(){
	double p = frand_0_1(); //p flottant alÃ©atoire entre 0 et 1
	int sommet,voisin;
	double p_apparition;
	vector<int> voisins;

	cout << "p=" << p << endl;

	for(sommet=0;sommet<nb_sommet;sommet++){//initialisation des listes vides pour liste_voisins
		vector<int> liste;
		liste_voisins.push_back(liste);
	}

	for(sommet=0;sommet<nb_sommet;sommet++){ //pour chaque sommet
		for(voisin=sommet+1;voisin<nb_sommet;voisin++){ //pour chaque voisin potentiel
			p_apparition = frand_0_1();//probabilitÃ© d'apparition alÃ©atoire entre 0 et 1

			//cout verifiant comment se forme le graphe
			//cout << "sommet:" << sommet <<"voisin:" << voisin << "p=" << p_apparition << endl;

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

	//Initialise un tableau de degrÃ©s
	for(auto cpt=0; cpt<nb_sommet; cpt++){
		deg[cpt] = 0;
	}

	//initialise les listes de voisins
	for(sommet=0;sommet<nb_sommet;sommet++){
		vector<int> sommets;
		liste_voisins.push_back(sommets);
	}

	//Initialise le graphe triangle de dÃ©part
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
				//cout verifiant comment se forme le graphe
				//cout << "sommet:" << sommet <<" voisin:" << voisin << " p_app=" << p_apparition << " p="<< p << endl;
				if(p<p_apparition){
					//On ajoute la nouvelle arÃªte dans les listes de voisins des sommets concernÃ©s
					liste_voisins[voisin].push_back(sommet);
					liste_voisins[sommet].push_back(voisin);
					//On actualise les degrÃ©s des sommets et le nombre total de sommet
					deg[sommet]++;
					deg[voisin]++;
					nb_tot_degres+=2;
					i++;
					//Si on a crÃ©Ã© 2 nouvelles arÃªtes, on passe au sommet suivant
					if(i==m){
						break;
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

	//Condition d'arrÃªt
	if (P.empty() && X.empty()){
		clique_maximal.push_back(R);
	}

	//Tant qu'il y a des sommets
	while (!P.empty()){
		int sommet = P[0];
		std::vector<int> newP, newR, newX;

		//Râ‹ƒsommet
		newR = R;
		newR.push_back(sommet);

		//Pâ‹‚âŒˆ(sommet)
		for(auto i : P){
			auto result = find(liste_voisins[sommet].begin(), liste_voisins[sommet].end(), i);
		    if (result != liste_voisins[sommet].end()) {
				newP.push_back(i);
			}
		}

		//Xâ‹‚âŒˆ(sommet)
		for(auto i : X){
			auto result = find(liste_voisins[sommet].begin(),liste_voisins[sommet].end(),i);
			if (result != liste_voisins[sommet].end()){
				newX.push_back(i);
			}
		}

		//Appel de rÃ©currence
		BronKerbosch(newP,newR,newX);

		//P\sommet
		P.erase(remove(P.begin(), P.end(), sommet), P.end());

		//Xâ‹ƒsommet
		X.push_back(sommet);
	}
}

//Tri la liste de voisins avec l'ordre de degerenescence
void Graph::liste_adj_degen(){

	//Pour chaque sommet i
	for(int i  = 0; i<nb_sommet; i++){
		vector<int> voisins_degen;
		//Pour chaque sommet dans l'ordre de la liste de degenerescence it
		for(auto it = list_degen.rbegin(); it != list_degen.rend(); it++){
			//Pour chaque voisin de i
			for(auto sommet : liste_voisins[i]){
				//Si le sommet it et le voisins actuel son egaux alors
				if(*it == sommet){
					//On ajoute le sommet a la liste de voisins trie
					voisins_degen.push_back(sommet);
				}
			}
		}
		//On ajoute la liste des voisins tries du sommet actuel a la liste des voisins complete
		liste_adj_d.push_back(voisins_degen);
	}
	//On affiche la liste de voisins trie
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

	//liste degres sommet par sommet
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
		//Cas D non vide
		if(cpt < nb_sommet){

			//ajoute le premier sommet trouvï¿½ dans ordre
			list_degen.push_back(D[cpt][0]);
			if(k_degen < degrestmp[D[cpt][0]]){
				k_degen = degrestmp[D[cpt][0]];
			}
			degrestmp[list_degen[list_degen.size()-1]] = -1;

			//on actualise les degres
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
}


void Graph::bron_kerbosch_degeneracy(){
	int cpt = 0, index;
	//Pour chaque sommet de la liste de degenerescence
	for(auto i : list_degen){
		vector<int> P;
		vector<int> X;
		//Pour chaque voisins de i
		for(auto sommet : liste_voisins[i]){
			index = 0;
			//Pour chaque sommet de la liste de degenerescence
			for (auto s_degen : list_degen){
				//Si le voisins actuel est egal dans la liste de degenerescence
				if(s_degen == sommet){
					//On recupere son indexe
					//Si le voisins apparait plus a droite dans la liste de degenerescence
					if(cpt < index){
						//Alors il est ajouter dans P
						P.push_back(sommet);
					}
					//Sinon
					else{
						//Il est ajouter dans X
						X.push_back(sommet);
					}
				}
				index++;
			}

		}
		cpt++;


		//cout X et P
		/*
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
		cout << endl << endl;*/

		//R vaut la sommet actuel
		vector<int> R;
		R.push_back(i);
		//Appelle a BronKerboschPivot
		bron_kerbosch_pivot(P, R, X);
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

	//Si P union X est vide
	if (PuX.empty()){
		clique_maximal.push_back(R);
	}
	else{
		//On choisit un pivot maximisant |P inter voisins(u)|
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

		//P prive des voisins du pivot
		int test;
		vector<int> P_sans_voisins_u;
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

		//Tant que P est non vide
		int v;
		while(!P_sans_voisins_u.empty()){
			v = P_sans_voisins_u[0];

			vector<int> P_n_voisins_v;
			//P inter voisins de v
			for(auto i : P){
				auto result = find(begin(liste_voisins.at(v)),end(liste_voisins.at(v)),i);
				if (result != end(liste_voisins.at(v))){
					P_n_voisins_v.push_back(i);
				}
			}

			vector<int> X_n_voisins_v;
			//X inter voisins de v
			for(auto i : X){
				auto result = find(begin(liste_voisins.at(v)),end(liste_voisins.at(v)),i);
				if (result != end(liste_voisins.at(v))){
					X_n_voisins_v.push_back(i);
				}
			}

			//On ajoute le pivot a R
			vector<int> newR = R;
			newR.push_back(v);

			//Recursivite
			bron_kerbosch_pivot(P_n_voisins_v, newR, X_n_voisins_v);

			//P prive du pivot
			P.erase(remove(P.begin(), P.end(), v), P.end());
			P_sans_voisins_u.erase(remove(P_sans_voisins_u.begin(), P_sans_voisins_u.end(), v), P_sans_voisins_u.end());
			//X union pivot
			X.push_back(v);
		}
	}
}


void Graph::maximal_clique_enumeration1(){
	//dÃ©gÃ©nÃ©rescence + ordre de dÃ©gÃ©nÃ©rescence de G
	degeneracy();
	affiche_liste_degen();

	//liste d'adjacence dÃ©gÃ©nÃ©rÃ©e
	liste_adj_degen();
	cout << "test" << endl;

	//arbre de suffixe reprÃ©sentÃ© par un unordered_set<vector<int>> avec la clÃ© = les suffixes des cliques
	MySet T;
	for(int j=0;j<nb_sommet;j++){

		//crÃ©ation sous graphe Gj selon l'ordre de dÃ©gÃ©nÃ©rescence
		Graph sous_graphe(this,list_degen[j]);

		//cliques maximales de Gj

		//Appelle pour BronKerbosch standard
		/*vector<int> P;
		vector<int> R;
		vector<int> X;
		for(int i=0; i<sous_graphe.nb_sommet; i++){
			P.push_back(i);
		}*/

		//sous_graphe.BronKerbosch(P,R,X);

		//Appelle pour BronKerboschDegeneracy
		sous_graphe.degeneracy();
		sous_graphe.bron_kerbosch_degeneracy();

		for(auto K : sous_graphe.clique_maximal){

			//transformation avec les bons numÃ©ros de sommet
			vector<int> K_ok;
			sous_graphe.formatOrigin(&K,&K_ok);

			//ordonner les sommets selon l'ordre de dÃ©gÃ©nÃ©rescence
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

				//insÃ©rer K dans T
				vector<vector<int>> k_suffixe;
				get_suffixe(&k_ordonne,&k_suffixe);
				for(auto suffixe : k_suffixe){
					T.insert(suffixe);
				}

				//on cout les cliques max
				cout << "K : ";
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
	//dÃ©gÃ©nÃ©rescence + ordre de dÃ©gÃ©nÃ©rescence de G
	degeneracy();
	affiche_liste_degen();

	//liste d'adjacence dÃ©gÃ©nÃ©rÃ©e
	liste_adj_degen();
	cout << "test" << endl;
	for(auto j=0;j<nb_sommet;j++){

		//crÃ©ation sous graphe Gj selon l'ordre de dÃ©gÃ©nÃ©rescence
		Graph sous_graphe(this,list_degen[j]);

		//clique maximales de Gj
		/*
		vector<int> P;
		vector<int> R;
		vector<int> X;
		for(int i=0; i<sous_graphe.nb_sommet; i++){
			P.push_back(i);
		}*/
		sous_graphe.degeneracy();
		sous_graphe.bron_kerbosch_degeneracy();

		for(auto K : sous_graphe.clique_maximal){

			//transformation avec les bons numÃ©ros de sommet
			vector<int> K_ok;
			sous_graphe.formatOrigin(&K,&K_ok);

			for(auto x : K_ok){

				//voisins de x avec rang dÃ©gÃ©nÃ©rescence infÃ©rieur
				vector<int> voisins_lower_degen_x;
				int cpt_liste_voisins = liste_adj_d[x].size()-1;
				int cpt_degen = 0;
				while(cpt_degen < j && cpt_liste_voisins >=0){
					if(liste_adj_d[x][cpt_liste_voisins]==list_degen[cpt_degen]){
						voisins_lower_degen_x.push_back(list_degen[cpt_degen]);
						cpt_liste_voisins--;
					}
					cpt_degen++;
				}

				//on cherche si un voisin de x dans G avec un rang de dÃ©gÃ©nÃ©rescence infÃ©rieur est voisin de tous les sommets de K
				bool reject_k = false;
				for(auto voisin_x : voisins_lower_degen_x){
					bool adjacent = true;
					for(auto sommet_k : K_ok){
						if(sommet_k != x && adjacent){
							auto result = find(liste_voisins[sommet_k].begin(),liste_voisins[sommet_k].end(),voisin_x);
							if (result == liste_voisins[sommet_k].end()){//voisin_x n'est pas voisin de sommet_k
								adjacent = false;
							}
						}
					}
					if(adjacent) {//on a trouvÃ© un voisin_x adjacent Ã  tous les sommets de K
						reject_k = true;
						break;
					}
				}
				if(!reject_k){//on a pas trouvÃ© de voisin de x adjacent Ã  tous les sommets de K
					cout << "K : ";
					cout << "[ ";
					for(auto sommet : K_ok){
						cout << sommet << ", ";
					}
					cout << "]" << endl;
					break;
				}
			}
		}
	}
}

double Graph::frand_0_1(){
	return rand()/(double)RAND_MAX ;
}

int Graph::get_k_degen(){
	return k_degen;
}

std::vector<std::vector<int>> Graph::getListe_clique(){
	return clique_maximal;
}

void Graph::affiche_liste_degen(){
	cout << "Graphe " << k_degen << " degenere" << endl;
	cout << "Liste de degenerescence : ";
	for(auto entier : list_degen){
		cout << entier << ", ";
	}
	cout << endl;
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
