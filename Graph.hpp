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
	std::vector<int> list_degen;
	int k_degen;
public:
	std::vector<std::vector<int>> clique_maximal;
	int nb_sommet;

    Graph(int n);
    ~Graph();
    void generation_aleatoire1();
	void generation_aleatoire2();
	void BronKerbosch(std::vector<int> P, std::vector<int> R, std::vector<int> X);
    double frand_0_1();
    void affiche();
    void degeneracy();
    void bron_kerbosch_degeneracy();
    void bron_kerbosch_pivot(std::vector<int> P, std::vector<int> R, std::vector<int> X);
protected:

};


#endif /* Graph_hpp */
