#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

// Serveur TCP

int main(){
    int sock_recp;
    if ((sock_recp = socket(AF_INET,SOCK_STREAM,0)) == -1){
        perror("Erreur ouverture socket de connexion");
        exit(-1);
    }
    // Mise en place de la communication

    struct sockaddr_in addr_cnt,exped;
    int cpt ; // Recption de la lecture
    int size_expd = sizeof(exped);
    // Mise en place de la communiaction
    memset(&addr_cnt, 0, sizeof addr_cnt);
    addr_cnt.sin_addr.s_addr = htonl(INADDR_ANY); // Acceptation de tous les messages à detination du serveur
    addr_cnt.sin_port = htons(3500);
    addr_cnt.sin_family = AF_INET;

    // On fait le bind de la structure sur le fichier ouvert (socket)
    if (bind(sock_recp,(struct sockaddr*)&addr_cnt,sizeof addr_cnt) == -1){
        perror("Erreur lors du bind");
        exit(-1);
    }
    listen(sock_recp,10); // On accepte 10 connexions au total 

    // Partie traitement des requetes

    while(1){
        int sock_reponse;
        if((sock_reponse = accept(sock_recp,(struct sockaddr*)&exped,(socklen_t*)&size_expd)) < 0 ){
            perror("impossible d'accepter la connexion");
            exit(-1);
        }
        // Création d'un processus pour handle la connexion 
        if (fork()==0){
            if (read(sock_reponse,&cpt,sizeof cpt) < 0){
                perror("Probleme lecture");
                exit(-1);
            }
            cpt += 1100;
            if (write(sock_reponse,&cpt,sizeof cpt) < 0){
                perror("Probleme write");
                exit(-1);
            }

            shutdown(sock_reponse,2);
            close(sock_reponse);
            return 0; 
        }
    }
    close(sock_recp);
return 0;
}