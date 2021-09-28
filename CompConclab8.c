#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

//variáveis globais
int lock1=1,lock2=1; //Permite que as threads sejam liberadas
sem_t semX, semT;

void * thread1 (void *arg)
{
    sem_wait(&semT); //wait dentro de um looping de execucao
    printf("Fique a vontade.\n");
    sem_post(&semT);
    sem_wait(&semX); //evitando condicao de corrida
    lock2++;
    sem_post(&semX);
    pthread_exit(NULL);
}

void * thread2 (void *arg)
{
    printf("Seja bem vindo!\n");
    sem_post(&semT);
    sem_post(&semX);
    pthread_exit(NULL);
}

void * thread3 (void *arg)
{
    while(lock2<3){}
    printf("Volte Sempre!\n");
    pthread_exit(NULL);
}

void * thread4 (void *arg)
{
    sem_wait(&semT); //wait dentro de um looping de execucao
    printf("Sente-se por favor.\n");
    sem_post(&semT);
    sem_wait(&semX); //evitando condicao de corrida
    lock2++;
    sem_post(&semX);
    pthread_exit(NULL);
}

int main()
{
    int i;
    pthread_t threads[4];
    sem_init(&semX, 0, 0);
    sem_init(&semT, 0, 0);
    pthread_create(&threads[0],NULL,thread1,NULL); //Criando das Threads
    pthread_create(&threads[1],NULL,thread2,NULL);
    pthread_create(&threads[2],NULL,thread3,NULL);
    pthread_create(&threads[3],NULL,thread4,NULL);

    for (i=0;i<4;i++) {pthread_join(threads[i], NULL);} //pthread_join
    pthread_exit(NULL);
    return 0;

}
