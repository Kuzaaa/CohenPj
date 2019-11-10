#include <iostream>

#include "Graph.hpp"
#include "suffix_hash_map.hpp"

using namespace std;

//recupère une entrée de type int
void entree(int &choix)
{
	cin >> choix;
	if(cin.fail())
	{
		cout << "Saisie incorrecte." << endl;
		cin.clear();
	}
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
}


int main(){

	int nb_sommet,choix;
	vector<int> P,R,X;
	
	do{
		cout << "Entrer le nombre de sommets ( >= 1 ): ";
		entree(nb_sommet);
	}while(nb_sommet < 1);

	Graph graphe(nb_sommet);

	do{
		cout << "Comment voulez-vous générer votre graphe ?:\n(1)Aléatoirement\n(2)Avec l'algorithme de Barabèsi-Albert" << endl;
		entree(choix);
	}while((choix < 1)||(choix>2));

	if(choix==1)
		graphe.generation_aleatoire1();
	else
		graphe.generation_aleatoire2();

	do{
		cout << "Que voulez-vous faire ?:\n(1)Bron-Kerbosch\n(2)Bron-Kerbosch avec pivot"
			"\n(3)Enumeration de cliques maximales avec arbre de suffixe"
			"\n(4)Enumeration de cliques maximales sans arbre de suffixe" << endl;
		entree(choix);
	}while((choix < 1)||(choix>4));

	switch (choix) {
		case 1:
			for(int i=0; i<nb_sommet; i++){
				P.push_back(i);
			}
			graphe.BronKerbosch(&P,&R,&X);
			break;
		case 2:
			cout << "The cake is a lie" << endl;
			break;
		case 3:
			graphe.maximal_clique_enumeration1();
			break;
		case 4:
			graphe.maximal_clique_enumeration2();
			break;
		default:
			cout << "You shouldn't be here..." << endl;
	}

	return 0;
}
