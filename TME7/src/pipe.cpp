
#define _GNU_SOURCE
#include <unistd.h>
#include<iostream>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include<string>


using namespace std;

int main (int argc, char** argv){

    // On crée un tableau de file descriptor 
    int pipeFd[2];
    
    if (pipe(pipeFd)==-1){
        perror("Erreur du pipe");
        exit(-1);
    }

    // On sépare les arguments dans le main

    int cpt = 0;
    int parcours = 2;
        while(strcmp(argv[2], "_")){
            cpt++;
            parcours++;
        }
        // cpt => contient le nombre d'argument de 1
        int addPath2 = parcours+1;// parcours l'indice contient le path de f2


        // On récupère le taille des arguments
        char**  argument1 = new char*[cpt+1];

        for (int j=0;j<cpt;j++){
            argument1[j] = argv[2+j];
        }
        argument1[cpt] = NULL; // Liste des arguments de la première function qui sont prêt

        char** argument2 = new char*[argc-parcours+1];
        int i =0;
        while( parcours < argc){
            argument2[i]= argv[parcours];
            i++;
            parcours++;
        }
        argument2[i+1] = NULL;// Lise des arguments de la deuxième function sont prêt 



    if (fork() == 0){
        dup2(pipeFd[1],STDOUT_FILENO);// On modifie l'entrée standard 
        close(pipeFd[0]);
        // On récupère les argument du premier exec
        if (execv(argv[2],argument1)==-1){
            perror("Erreur lancement fun1");
        };
    }

    if (fork()==0){
        dup2(pipeFd[0],STDIN_FILENO);
        close(pipeFd[1]);
        if (execv(argv[addPath2],argument2)==-1){
            perror("Erreur lancement fun2");
        };

    }

    return 0;
    
}


