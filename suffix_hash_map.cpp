#include "suffix_hash_map.hpp"

using namespace std;

//ajoute a suffixes tous les suffixes de clique
void get_suffixe (vector<int>* clique,vector<vector<int>>* suffixes){
	vector<int> suffixe_act;

	for(auto i=0;i<(int)clique->size();i++){
		for(auto j=i;j<(int)clique->size();j++){

			//on ajoute le sommet d'après au dernier suffixe pour créer le nouveau suffixe
			suffixe_act.push_back((*clique)[j]);
			suffixes->push_back(suffixe_act);
		}
		suffixe_act.clear();

	}
}



