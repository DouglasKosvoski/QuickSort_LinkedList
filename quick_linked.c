#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ItemLista {
    int valor;
    int posicao;

    struct ItemLista *prev;
    struct ItemLista *prox;
}; typedef struct ItemLista ItemLista;

typedef struct {
    ItemLista *head;
    ItemLista *tail;
} Lista;

Lista *criaLista(int size) {
    Lista *lista = (Lista *) malloc(sizeof(Lista));

    ItemLista *first =  (ItemLista *) malloc(sizeof(ItemLista));
    first -> prev = NULL;
    first -> prox = NULL;
    first -> valor = (int) malloc(sizeof(int));

    lista -> head = first;

    srand((unsigned)time(NULL));

    //seta o valor do primeiro elemento
    first -> valor = rand() % size;
    //first -> val = size;
    first -> posicao = 0;
    ItemLista *elemento = first;
    ItemLista *aux;
    int i = size-1;
    while(i > 0) {
        aux = ( ItemLista *) malloc(sizeof (ItemLista));
        aux -> valor = (int) malloc(sizeof(int));
        aux -> valor = rand() % size; //seta o valor de aux
        aux -> posicao = elemento -> posicao + 1;
        aux -> prev = elemento; //seta o anterior de aux como sendo o elemento
        aux -> prox = NULL;
        elemento -> prox = aux; //seta o proximo do anterior (elemento) como sendo aux
        elemento = aux;
        i--;
    }
    lista -> tail = aux;
    return lista;
}

void printLista(Lista *lista) {
    ItemLista *aux;
    printf("\n---- Lista ----\n\t");
    for(aux = lista -> head; aux != NULL; aux = aux -> prox) {
        printf("%d, ",aux -> valor);
    }
    printf("\n------------\n");
}

void swap(ItemLista *a, ItemLista *b) {
    if (a == b) return;

    int aux = a -> valor;
    a -> valor = b -> valor;
    b -> valor = aux;
}

// Essa função retorna o pivo.
ItemLista *particiona( ItemLista *inicio, ItemLista *fim) {
    int x = (int)fim -> valor;
    struct ItemLista *i = inicio -> prev;

    for(struct ItemLista *j = inicio; j != fim; j = j -> prox) {
        if((int)(j -> valor) <= x) {
            i = (i == NULL) ? inicio : i -> prox;
            swap(i, j);
        }
    }
    i = (i == NULL) ? inicio : i -> prox;
    swap(i, fim);
    return i;
}

void quickSort(ItemLista *inicio, ItemLista *fim) {
  if(inicio != fim && inicio != fim -> prox && fim != NULL) {
      struct ItemLista *p = particiona(inicio, fim);
      quickSort(inicio, p -> prev);
      quickSort(p -> prox, fim);
  }
}

int main() {
    Lista *lista;
    int size = 10;

    printf("Quick: %d \n\n", size);
    lista = criaLista(size);
    printLista(lista);

    quickSort(lista->head, lista->tail);

    printLista(lista);
    return 0;
}
