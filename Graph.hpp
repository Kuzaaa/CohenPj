#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

struct VectorHash { //pour hasher des vector<int>
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

/* graphe represente par une liste d'adjacence,
 * liste_voisins[i] contiendra les voisins du sommet i
 */
class Graph {
private:
	std::vector<std::vector<int>> liste_voisins;
	std::vector<int> list_degen;
	int k_degen;
	std::vector<std::vector<int>> liste_adj_d;
	std::vector<int> correspondanceOrignFct;
	std::vector<std::vector<int>> clique_maximal;
	int nb_sommet;
public:

    Graph(int n);
	Graph(Graph* graphe, int e);
    std::vector<std::vector<int>> getListe_clique();
    int get_k_degen();
	void formatOrigin(std::vector<int>* liste,std::vector<int>* newListe);
    void generation_aleatoire1();
	void generation_aleatoire2();
	void BronKerbosch(std::vector<int> P, std::vector<int> R, std::vector<int> X);
    double frand_0_1();
    void affiche();
    void affiche_liste_degen();
    void degeneracy();
    void bron_kerbosch_degeneracy();
    void bron_kerbosch_pivot(std::vector<int> P, std::vector<int> R, std::vector<int> X);
    void liste_adj_degen();
    void maximal_clique_enumeration1();
    void maximal_clique_enumeration2();
protected:

};


#endif /* Graph_hpp */
