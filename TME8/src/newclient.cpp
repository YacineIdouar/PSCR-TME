#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>


// Client TCP

int main (){
    // On veut une communication TCP 
    int sock_client;
    if ((sock_client = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("Erreur ouverture de la socket");
        exit(-1);
    }
    struct sockaddr_in serveur;
    memset(&serveur,0,sizeof serveur);
    // On veut se connecter à local host

    // Résolution DNS 
    struct addrinfo hint,*res;
    memset(&hint,0,sizeof hint);
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_family = AF_INET;
    // On récupère l'ip
    int err;
    if ((err = getaddrinfo("localhost",NULL,&hint,&res))!=0){
        printf("Erreur de la récupération DNS %s",gai_strerror(err));
        exit(-1);
    }

    // Mise en place du serveur
    serveur.sin_addr = ((struct sockaddr_in*)(res->ai_addr))->sin_addr; // recuperation de l'ip
    serveur.sin_family = AF_INET;// Communication IPV4
    serveur.sin_port = htons(3500);

    // Etablir la connection
    if (connect(sock_client,(struct sockaddr*)&serveur,sizeof serveur) == -1){
        perror("Erreur d'établissement de la communication");
        exit(-1);
    }

    int message = 42;
    if (write(sock_client,&message,sizeof message)==-1){
        perror("Erreur de l'ecriture");
        exit(-1);
    }

    // Réception de la réponse 

    if (read(sock_client,&message,sizeof message)==-1){
        perror("Erreur de lecture");
        exit(-1);
    }

    printf("La réponse du serveur : %d",message);

    // Fermeture de la connection
    shutdown(sock_client,2);
    close(sock_client);

    return 0;
}