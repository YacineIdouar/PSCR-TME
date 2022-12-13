#include<sys/types.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include <sys/wait.h>
#include <time.h>

int pv = 3;

void randsleep() {
    int r = rand();
    double ratio = (double)r / (double) RAND_MAX;
    struct timespec tosleep;
    tosleep.tv_sec =0;
    // 300 millions de ns = 0.3 secondes
    tosleep.tv_nsec = 300000000 + ratio*700000000;
    struct timespec remain;
    while ( nanosleep(&tosleep, &remain) != 0) {
        tosleep = remain;
    }
  }



 void handler (int sig){
    printf("le process %d a : %d pv\n",getpid(),pv);
    if (--pv == 0){
        exit(0);
    }

 }

 void handler_wait (int sig){
    int status;
    printf("wait du fils ");
    wait(&status);
    exit(0);
 }


// Simulation du combat de signaux 
void attaque(pid_t adversaire){

    // Init du handler
    sigset_t set;
    struct sigaction action;
    sigemptyset(& set);

    action.sa_mask = set;
    action.sa_flags = 0;
    action.sa_handler = handler;

    sigaction(SIGINT,&action,NULL);

    printf("Le process %d attaque ! \n",getpid());

    if (kill(adversaire,SIGINT)== -1){
        printf("L'adversaire %d est mort !\n",adversaire);
        exit(0);
    }

    randsleep();
}

void defense(){

    sigset_t set;
    struct sigaction action;
    sigemptyset(& set);

    action.sa_mask = set;
    action.sa_flags = 0;
    action.sa_handler = SIG_IGN;

    printf("Le process %d defend ! \n",getpid());
    sigaction(SIGINT,&action,NULL);
    randsleep();
}

void combat(pid_t adversaire){
    while(1){
    defense();
    attaque(adversaire);
    }
}

int main(){
    pid_t pid_fils ;
    if((pid_fils = fork()) == 0){
        combat(getppid());
        return 0;
    }
    signal(SIGCHLD,handler_wait); // On fait un wait du fils dans le handler 
    combat(pid_fils);
    return 0;
}