#include "Sahred_result.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include<sys/stat.h>
#include<iostream>
#include <unistd.h>
#include <sys/wait.h>



using namespace std;

int main (){ 
    void* addr = mmap(NULL,sizeof(Shared_result<int>),PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,-1,0); // Création du shared memory anonyme !
    Shared_result<int>* res = new(addr) Shared_result<int>();

    if (fork()==0){
        res->set_data(4);
        exit(0);
    }

    if (fork()==0){
        
        cout << res->get_data()<< endl;
        exit(0);
    }

    wait(0);
    wait(0);

    munmap(addr,sizeof(Shared_result<int>));

    return 0;

    

}
