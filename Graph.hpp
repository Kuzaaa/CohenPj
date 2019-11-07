#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

/* graphe représenté par un vecteur de vecteurs,
 * T[i] contiendra les voisins de i avec un n° sommet supérieur
 * pour éviter la redondance
 */
class Graph {
private:
	std::vector<std::vector<int>> liste_voisins;
	int nb_sommet;
	std::vector<std::vector<int>> clique_maximal;
	std::vector<int> list_degeneracy;
public:

    Graph(int n);
    ~Graph();
    void generation_aleatoire1();
	void generation_aleatoire2();
	void BronKerbosch(std::vector<int> P, std::vector<int> R, std::vector<int> X);
    double frand_0_1();
    void affiche();
    //V = Liste_voisins
    void degeneracy();
    void maximal_clique_enumeration1();
protected:

};


#endif /* Graph_hpp */
