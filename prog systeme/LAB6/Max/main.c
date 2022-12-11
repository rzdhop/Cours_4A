#include "header.h"
#include <string.h>

#define SIZE_ARRAY 100000000

struct context
{
    int * ptr_start;
    int * ptr_end;
    int index_demarrage;
    int nb_thread;
    int max;
};

pthread_t *tid;

int max_partial(int* s, int* e)
{
    int max = 0;
    while(s < e)
    {
        if (*s > max) max = *s;
        s++;
    }
    return max;
}

void* max_thread(void* arg)
{
    struct context *ctx = arg;
    int nombre_iteration = ceil(log2(ctx->nb_thread));
    // Max partiel
    // Trie partiel des sections pointées
    sort_partial(ctx->ptr_start, ctx->ptr_end);

    int it;
    for (it = 0; it < nombre_iteration; ++it)
    {
        if (ctx->index_demarrage % (2 << it) == 0)
        {
            int thread_waited = ctx->index_demarrage + (1 << it);
            if (thread_waited >= ctx->nb_thread) return ctx;

            // Attente du thread
            struct context *ctx_merge;
            assert(pthread_join(tid[thread_waited], (void**)&ctx_merge) == 0);

            // Fusion des threads voisin
            //ajout du merge partiel (non max)
            merge(ctx->ptr_start, ctx->ptr_end, ctx_merge->ptr_start,ctx_merge->ptr_end);
            free(ctx_merge);
        }
        else
        {
            return ctx;
        }
    }
    return ctx;
}

void sort(int* tab, size_t nb_elem, int nb_thread)
{
    int elem_by_thread = ceil((double)SIZE_ARRAY/nb_thread);
    //printf("\t |%d|\n", elem_by_thread)
    tid = malloc(nb_thread * sizeof(pthread_t));
    // Création des threads
    int i;
    for (i = nb_thread - 1; i >= 0; --i)
    {
        struct context *ctx = malloc(sizeof(struct context));

        ctx->ptr_start = tab + i * elem_by_thread;
        ctx->ptr_end = tab + (i + 1) * elem_by_thread;
        if (ctx->ptr_end > tab + nb_elem) ctx->ptr_end = tab + nb_elem;
        ctx->index_demarrage = i;
        ctx->nb_thread = nb_thread;
        assert(pthread_create(&tid[i], NULL, max_thread, ctx) == 0);
    }
    struct context *ctx;
    assert(pthread_join(tid[0], (void**)&ctx) == 0);
    int max = ctx->max;
    free(ctx);
    free(tid);
}

void shuffle(int * b, int size)
{
    srand(time(NULL));
    int i;
    for (i = 0; i < size/2; ++i)
    {
        int first = rand() % size;
        int second = rand() % size;
        int tmp = b[first];
        b[first] = b[second];
        b[second] = tmp;
    }
}

int cmp (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}

void sort_partial(int* start, int* end)
{
    qsort(start, end - start, sizeof(int), cmp);
}

void merge(int *s1, int *e1, int* s2, int* e2)
{
    int *start = s1;

    if (s2 == e2) return;

    assert((e1 - s1) > 0);
    assert((e2 - s2) > 0);

    int size = (e2 - s1);
    int *out = malloc(sizeof(int) * size);
    int *tmpbuf = out;

    while (!(s1 >= e1 || s2 >= e2))
    {
        if (*s1 > *s2)
        {
            *out = *s2;
            ++s2;
        }
        else
        {
            *out = *s1;
            ++s1;
        }
        ++out;
    }

    while(s2 < e2)
    {
        *out = *s2;
        ++out;
        ++s2;
    }

    while(s1 < e1)
    {
        *out = *s1;
        ++out;
        ++s1;
    }

    memcpy(start, tmpbuf, size * sizeof(int));
    free(tmpbuf);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s nb_thread\n", argv[0]);
        exit(-1);
    }
    int nb_thread = atoi(argv[1]);
    int *buffer = malloc(sizeof(int) * SIZE_ARRAY);
    int i;
    for (i = 0; i < SIZE_ARRAY; ++i)
    {
        buffer[i] = i ;
    }
    shuffle(buffer, SIZE_ARRAY);

    double startTime, endTime;
    startTime = getRealTime();

    //affiche le contenue tu buffer avant le trie
    for(int i=0; i < 100; i++){
      printf("%d, ", buffer[i]);
    }
    printf("\n\n");

    sort(buffer, SIZE_ARRAY, nb_thread);

    //apres le trie
    for(int i = 0; i < 100; i++){
      printf("%d, ", buffer[i]);
    }
    printf("\n\n");

    endTime = getRealTime();

    free(buffer);
    fprintf(stderr, "Real time used = %lf\n", (endTime - startTime));
    return 0;
}
