// Définiton de la classe de table de hashage 

#pragma once 
#include<cstddef>
#include <vector>

template<typename K, typename V> 

class hashT{

    // Création de la paire clé/value
    class entryK{
        public:
            const K key;
            V value;

            // Constructeur pour la class entryK
            entryK (const K ket,V value){
                this->key = key;
                this->value = value;
            }
            
     };
     
    //typedef des structures intéressante !! 
    typedef std::forward_list<entryK> list_t;
    typedef std::vector<list_t> bucket_t; // Définiton de la structure contenant la table de hash       

     bucket_t buckets;
     size_t init;

     public :
     // Constructeur
     hashT(size_t init = 100){
        buckets.reserve(init); // 
        for (size_t i =0; i < init;i++ ){
            buckets.push_back(list_t); // On initialise la table avec des list vides 
        }   
     }
     // Accesseur à l'adresse du pointeur de la valeur qui contient key en clé. 
     V* get (const K& key){
        size_t indice = std::hash<K>()(key) % buckets.size(); // On récupère l'indice de la clé key dans la table.

        // Poineteur sur "Kentry" pour parcourirs la liste des couples
        entryK* parcours;

        for (parcours = buckets[indice] ; parcours ; ){
            if ((parcours->key) == key) // Si on retrouve la valeur key dans la list oon break la boucle 
                break;
            // Sinon on avance 
            parcours = parcours->iterator;
        }
        return parcours;
     }

bool put (const K& key, const V& value){

    // On calcile l'indice dans la table de la clé 
    int indice = std::hash<K>()(key) % buckets.size();
    entryK* parcours = buckets[indice];
    while (parcours)
    {
        if (parcours->key == key){
            parcours->value = value;
            return true;
        }
    }
    // On insère le nouvel élement dans son bucket !!
    buckets[indice].push_front(new entryK (ket,value));
    return false;

}
    
};
    
    

    
