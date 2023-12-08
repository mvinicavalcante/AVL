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
    } else {
        if(valor > raiz->valor) {
            raiz->dir = inserir(raiz->dir, valor);
            if(*cresceu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        *cresceu = 0; //porque ficaria desbalanceado, ele zera
                        //o crescimento pq faz a rotação
                        return rotacao(raiz);
                        break;
                    case -1:
                        *cresceu = 0;
                        break;
                }
            }
        } else {
            raiz->esq = inserir(raiz->esq, valor);
            if(*cresceu) {
                switch(raiz->fb) {
                case 0:
                    raiz->fb = -1;
                    *cresceu = 1;
                    break;
                case 1:
                    *cresceu = 0;
                    break;
                case -1:
                    *cresceu = 0;
                    return rotacao(raiz);
                    break;
                }
            }
        }
    }
    return raiz;
}

arvore rotacao(arvore pivo) {
    if(pivo->fb > 0) {
    //rotação esquerda
        if(pivo->dir->fb >= 0) {
            if(pivo->dir->fb == 0) {
                pivo->fb = 1;
                pivo->dir->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
            }
        } else {
            pivo->fb = -1;
            pivo->dir->fb = 1;
        }

    } else {

    }
}


