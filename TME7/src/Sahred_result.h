#pragma once
#include <semaphore.h>
#include<stdlib.h>
#include<stdio.h>

template<typename T> 
class Shared_result{
    private : 
        T data;
    public :
    sem_t bloc;

    Shared_result() {
        if (sem_init(&bloc,1,0)==-1){
            perror("Problème init semaphore ");
        }
    }

    void set_data(T data){
        this->data = data;
        sem_post(&bloc);
    }

    T get_data(){
        sem_wait(&bloc);
        return data;
    }

};