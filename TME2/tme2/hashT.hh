// Définiton de la classe de table de hashage 

#pragma once 
#include<cstddef>
#include <vector>
#include <forward_list>
#include <ostream>
template<typename K, typename V> 

class hashT{

    // Création de la paire clé/value
    class entryK{
        public:
            K key;
            V value;

            // Constructeur pour la class entryK
            entryK (K ket,V value){
                this->key = key;
                this->value = value;
            }
            
     };
     
    //typedef des structures
    typedef std::vector<std::forward_list<entryK> > bucket_t; // Définiton de la structure contenant la table de hash       

     bucket_t buckets;
     size_t init;

     public :
     // Constructeur
     hashT(size_t init){
        this->init = init;
        buckets.reserve(init); 
        for (size_t i =0; i < init;i++ ){
            std::forward_list<entryK> list;
            buckets.push_back(list); // On initialise la table avec des listes vides 
        }   
     }

     // Accesseur à l'adresse du pointeur de la valeur qui contient key. 
     V* get (K key){

        size_t indice = (std::hash<K>()(key)) % buckets.size(); // On récupère l'indice de la clé key dans la table.
        // On cherche dans la forward_list d'indice de l'élement !
        auto it = buckets[indice].begin();
        for (;it!=buckets[indice].end();it++){ 
            if(it->key==key){
                return &(it->value);
            }
        }
        return nullptr;
     }


bool put (K key,V value){
   
    // On calcile l'indice dans la table de la clé 
    int indice = std::hash<K>()(key) % buckets.size();
    for (auto elem : buckets[indice]){        
            if (elem.key==key){
                elem.value = value;
                return true;
            }
        }
    // On insère le nouvel élement dans son bucket !!
    buckets[indice].push_front(entryK (key,value));
    return false;
}
    
};
    
    

    
