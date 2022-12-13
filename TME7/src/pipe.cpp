#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <fcntl.h>              

int main (int argc, char* argv[]){
    // Création du pipe 
    int fd[2];
    pipe(fd);// fd contient les deux extrémité du pipe

    char* buff[argc];

     // On doit séparer les arguments !

     int cpt = 1;
     int i= 0;

     while (strcmp(argv[cpt],"@")!=0){
        buff[i] = strdup(argv[cpt]);     
        i++;
        cpt++;
     }

     // Le buffer contient les arguments de la première commande 
     buff[i] = NULL;    
    // On avance i et cpt pour avoir les prochians arguments ! 
    cpt ++;
    int path2 = cpt;
    i = 0; 
    char* buff2[argc];
    while (cpt < argc)
    {   
        buff2[i] = strdup(argv[cpt]);
        cpt++;
        i++ ;       
    }
    buff2[i] = NULL;
    i=0;

    if (fork()==0){
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        if (execv(argv[1],buff) <0){
            perror("fail exec");
        }
    }

    if (fork()==0){
        dup2(fd[0],STDIN_FILENO);
        close(fd[1]);
        if (execv(argv[path2],buff2) <0){
            perror("fail exec2");
        }
    }
    
    return 0;

}
