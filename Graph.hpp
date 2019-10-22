#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

/*graphe représenté par un vecteur de vecteurs, T[i] contiendra les voisins de i avec un n° sommet supérieur
 * pour éviter la redondance
 */
class Graph {
private:
	std::vector<std::vector<int>> liste_voisins;
	int nb_sommets;
public:
    Graph();
    ~Graph();
    void generation_aleatoire1();
    double frand_0_1();
protected:

};


#endif /* Graph_hpp */
