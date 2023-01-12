#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NB_THREADS 10

typedef struct routine_args routine_args;
struct routine_args {
    int indexRoutine;
    int* returnValue;
};

//agis en tant que garbage collector
typedef struct thread_context thread_context;
struct thread_context{
    routine_args *routineArgs;
    pthread_t id;
};

void *routine(void *args){
    routine_args *localargs = (routine_args*)args;

    printf("Tache : %d\n", localargs->indexRoutine);

    *(localargs->returnValue) = localargs->indexRoutine *10;
}

int main(){
    pthread_t threads_id[NB_THREADS];
    int *returnValues[NB_THREADS];
    thread_context *threadsContext[NB_THREADS];

    for(int i=0; i < NB_THREADS; i++){
        returnValues[i] = (int*)malloc(sizeof(int));
        routine_args *args = (routine_args*)malloc(sizeof(routine_args));
        threadsContext[i] = (thread_context*)malloc(sizeof(thread_context));
        args->indexRoutine = i;
        args->returnValue = returnValues[i];

        threadsContext[i]->routineArgs = args;
        pthread_create(&threads_id[i], NULL, routine, (void*)args);
        threadsContext[i]->id = threads_id[i];
    }
    
    for(int i=0; i < NB_THREADS; i++){
        pthread_join(threads_id[i], NULL);
    }
    for(int i=0; i < NB_THREADS; i++){
        printf("Thread : %d -> Retour : %d\n", i, *returnValues[i]);
        free(returnValues[i]);
        free(threadsContext[i]->routineArgs);
        free(threadsContext[i]);
    }
   

    return 0;
}