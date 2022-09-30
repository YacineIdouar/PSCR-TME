#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>



int main () {
	using namespace std;
	using namespace std::chrono;

	// définiton du vecteur de mots différents.
	vector<string> vecteur_mots_diff ;
	int nombre_mots_diff = 0;

	// Définition du vecteur de pair
	vector<pair<string,int>> vecteurs_pair;

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

		// Modif du code 
		if (find(vecteur_mots_diff.begin(),vecteur_mots_diff.end(),word)==vecteur_mots_diff.end()){
			
				// Incrémentation du competur des mots différents
				nombre_mots_diff++;
				vecteur_mots_diff.push_back(word);
			}



		// recherche de paire
		size_t i;
		for(i=0;i<vecteurs_pair.size();++i){
			if (vecteurs_pair[i].first == word){
				vecteurs_pair[i].second ++;
			}
		}
		// ajout de pair dans le vecteur si mot non trouvé !!
		if (i==vecteurs_pair.size()){
			vecteurs_pair.push_back(make_pair(word,1));
		}
			
		
	}
	// Fermeture du fichie
	input.close();


	for(size_t i=0;i<vecteurs_pair.size();++i){
			if (vecteurs_pair[i].first == "toto"){
				cout << "nombre apparition de toto " << vecteurs_pair[i].second << endl;
			}
			if (vecteurs_pair[i].first == "war"){
				cout << "nombre apparition de war " << vecteurs_pair[i].second << endl;
			}
			if (vecteurs_pair[i].first == "peace"){
				cout << "nombre apparition de peace" << vecteurs_pair[i].second << endl;
			}
	}

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Nombre de mots différents : " << nombre_mots_diff << endl;

    return 0;
}


