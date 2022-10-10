#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include"hashT.hh"



int main () {
	using namespace std;
	using namespace std::chrono;

	// définiton du vecteur de mots différents.

	/*vector<string> vecteur_mots_diff ;
	int nombre_mots_diff = 0;*/

	// Définition du vecteur de pair
	vector<pair<string,int>> vecteur_pair;
	int nombre_mots_diff = 0;

	// On utilise la table de Hash
	hashT<string,int> table_hash (10000);

	ifstream input = ifstream("./WarAndPeace.txt");
	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");

		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;

		//Modification du code 

		// Trouver si le mot existe dans la liste des pairs 
		//auto it = find_if(vecteur_pair.begin(),vecteur_pair.end(),[word](auto& a){return a.first==word ;});

		// Trouver le mot dans la table 
		int* valeur = table_hash.get(word);
		if(valeur==nullptr){
			table_hash.put(word,1);
		} 
		else{
			(*valeur)++;
		}


		/*if (it==vecteur_pair.end()){
				// Incrémentation du competur des mots différents + ajout du nouveau mot dans la liste
				nombre_mots_diff++;
				vecteur_pair.push_back(make_pair(word,1));
			}

		else{
			// Incrémentation du nombre d'apparition du mot
			it->second++;
		}	*/
	}
	// Fermeture du fichie
	input.close();


	/*for(size_t i=0;i<vecteur_pair.size();++i){
			if (vecteur_pair[i].first == "toto"){
				cout << "nombre apparition de toto " << vecteur_pair[i].second << endl;
			}
			if (vecteur_pair[i].first == "war"){
				cout << "nombre apparition de war " << vecteur_pair[i].second << endl;
			}
			if (vecteur_pair[i].first == "peace"){
				cout << "nombre apparition de peace " << vecteur_pair[i].second << endl;
			}
	}*/

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Nombre de mots différents : " << nombre_mots_diff << endl;

    return 0;
}


