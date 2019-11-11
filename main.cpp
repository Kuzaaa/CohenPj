#include <iostream>
#include <limits>
#include <string>
#include <chrono>
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
	std::chrono::system_clock::time_point start;
	std::chrono::duration<double> sec;
	srand(time(NULL));
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

		graphe.affiche();

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
				start = std::chrono::system_clock::now();
				graphe.BronKerbosch(P,R,X);
				sec = std::chrono::system_clock::now() - start;
				for(auto clique : graphe.getListe_clique()){
					cout << "[ ";
					for(auto sommet : clique){
						cout << sommet << ", ";
					}
					cout << "]" << endl;
				}
				break;
			case 2:
				start = std::chrono::system_clock::now();
				graphe.degeneracy();
				graphe.bron_kerbosch_degeneracy();
				sec = std::chrono::system_clock::now() - start;
				graphe.affiche_liste_degen();
				for(auto clique : graphe.getListe_clique()){
					cout << "[ ";
					for(auto sommet : clique){
						cout << sommet << ", ";
					}
					cout << "]" << endl;
				}
				break;
			case 3:
				start = std::chrono::system_clock::now();
				graphe.maximal_clique_enumeration1();
				sec = std::chrono::system_clock::now() - start;
				cout << "k : " << graphe.get_k_degen() << endl;
				break;
			case 4:
				start = std::chrono::system_clock::now();
				graphe.maximal_clique_enumeration2();
				sec = std::chrono::system_clock::now() - start;

				break;
			default:
				cout << "You shouldn't be here..." << endl;
		}

		cout << "Temps d'execution: " << sec.count() << "secondes." << endl;

	return 0;
}
