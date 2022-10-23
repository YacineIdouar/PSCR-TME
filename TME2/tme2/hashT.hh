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
            entryK (K key,V value){
                this->key = key;
                this->value = value;
            }
            
     };

     // On définit la classe iterateur
     

    //typedef des structures
    typedef std::vector<std::forward_list<entryK> > bucket_t; // Définiton de la structure contenant la table de hash       
    typedef typename std::vector<std::forward_list<entryK>>::iterator vect_it_t;
    typedef typename std::forward_list<entryK>::iterator fl_it_t;

    class Iterator{
       vect_it_t vertical_it;
       fl_it_t horizontal_it;
       // Constructeur de la classe
       Iterator(vect_it_t vect, fl_it_t forl){
        vertical_it = vect;
        horizontal_it = forl;
       } 
     };

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

// Mise a jour de la structure 
bool put (K key,V value){
   
    // On calcule l'indice dans la table de la clé 
    int indice = std::hash<K>()(key) % buckets.size();
    auto it = buckets[indice].begin();
        for (;it!=buckets[indice].end();it++){ 
            if(it->key==key){
                it->value++;
                return true;
            }
        }
    // On insère le nouvel élement dans son bucket !!
    buckets[indice].push_front(entryK (key,value));
    return false;
}

// Défintion des itérateurs
Iterator begin(){
    return Iterator(buckets.begin(),buckets.begin().begin());
}
Iterator end (){
    return nullptr;
}

Iterator& operator ++ (Iterator it){
    if (++it.horizontal_it != it.horizontal_it.end()){
        return it.horizontal_it;
    }
    else{
        if(++it.vertical_it != it.vertical_it.end()){
            it.horizontal_it = it.vertical_it.begin();
            return it.horizontal_it;
        }
    }
    return it.end();
}
    
};
    
    

    
