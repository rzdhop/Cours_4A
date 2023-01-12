#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_FIFO 8
#define NB_PROD 1
#define NB_CONSO 1

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ready_cond = PTHREAD_COND_INITIALIZER;

typedef struct fifo fifo;
// Structure Fifo communication entre consommateurs et producteurs
struct fifo {
    int tab[SIZE_FIFO]; // Tableau d'éléments stockés
    int ptr_lecteur;    // Index de la prochaine case à lire
    int ptr_ecrivain;   // Index de la prochaine case à écrire
    int nb_elem;        // Nombre d'éléments présents dans la fifo
};

// Fonction d'initialisation de la fifo
void init_fifo(struct fifo *f) {
    f->ptr_ecrivain = 0;
    f->ptr_lecteur = 0;
    f->nb_elem = 0;
}

// Fonction permettant d'insérer une valeur dans la fifo
void put(struct fifo *f, int a) {
    if(f->ptr_ecrivain == SIZE_FIFO){
        f->ptr_ecrivain = 0;
    }
    printf("Ajout de %d a la position %d\n", a, f->ptr_ecrivain);
    f->tab[f->ptr_ecrivain] = a;
    f->nb_elem++;
    f->ptr_ecrivain++;
}

// Fonction permettant de récupérer une valeur depuis la fifo
int get(struct fifo *f) {
    if(f->ptr_lecteur == SIZE_FIFO){
        f->ptr_lecteur = 0;
    }
    int fifoValue = f->tab[f->ptr_lecteur];
    f->nb_elem--;
    f->ptr_lecteur++;
    return fifoValue;
}

// Fonction de production
void *prod(void* arg) {
    fifo *attachedFifo = (fifo*)arg;
    printf("Prod lancé !\n");
    for(int i=0;;i++){
        pthread_mutex_lock(&lock);
        if(attachedFifo->nb_elem == SIZE_FIFO){
            printf("Fifo plein !\r");
            pthread_cond_wait(&ready_cond, &lock);
        }else{
            put(attachedFifo, i);
        }
        pthread_mutex_unlock(&lock);
        sleep(0.2);
    }
}

// Fonction de consommation
void *conso(void* arg) {
    fifo *attachedFifo = (fifo*)arg;
    printf("Conso lancé !\n");
    int fifoValue, tmp;
    for(int i=0;;i++){
        pthread_mutex_lock(&lock);
        if(attachedFifo->nb_elem == 0){
            printf("Fifo Vide !\r");
            pthread_cond_broadcast(&ready_cond);
        }else{
            tmp = get(attachedFifo);
            if(fifoValue != tmp){
                fifoValue = tmp;
                printf("Valeur %d récupéré !\n", fifoValue);
            }
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

// Fonction principale
int main() {
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n Imposible d'initialiser le mutex...\n");
        return 1;
    }
    pthread_t prod_id[NB_PROD];
    pthread_t conso_id[NB_CONSO];

    fifo *myfifo = (fifo*)malloc(sizeof(fifo));

    for(int i=0; i < NB_PROD; i++){
        pthread_create(&prod_id[i], NULL, prod, (void*)myfifo);
    }
    for(int i=0; i < NB_CONSO; i++){ 
        pthread_create(&conso_id[i+1], NULL, conso, (void*)myfifo);
    }

    for(int i=0; i < NB_CONSO+NB_PROD; i+=2){    
        pthread_join(prod_id[i], NULL);
        pthread_join(conso_id[i+1], NULL);
    }
    free(myfifo);
    pthread_mutex_destroy(&lock);
    return 0;
}