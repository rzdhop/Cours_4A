#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE_FIFO 8
#define NB_PROD 1
#define NB_CONSO 1

// Structure Fifo communication entre consommateurs et producteurs
struct fifo {
    int tab[SIZE_FIFO]; // Tableau d'éléments stockés
    int ptr_lecteur;    // Index de la prochaine case à lire
    int ptr_ecrivain;   // Index de la prochaine case à écrire
    int nb_elem;        // Nombre d'éléments présents dans la fifo
} fifo;

// Fonction d'initialisation de la fifo
void init_fifo(struct fifo *f) {

}

// Fonction permettant d'insérer une valeur dans la fifo
void put(struct fifo *f, int a) {

}

// Fonction permettant de récupérer une valeur depuis la fifo
int get(struct fifo *f) {

}


// Fonction de production
void *prod(void* arg) {
        
}

// Fonction de consommation
void *conso(void* arg) {
    
}

// Fonction principale
int main() {
    
}
