#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

arvore inserir(arvore raiz, int valor, int *cresceu) {
    if(raiz == NULL) {
        arvore nova = (arvore) malloc(sizeof(struct no));
        nova->valor = valor;
        nova->esq = NULL;
        nova->dir = NULL;
        nova->fb = 0;
        *cresceu = 1;
        return nova;
    }
}
