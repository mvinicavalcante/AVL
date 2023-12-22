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
                balancear(raiz, valor, *cresceu);
            }
        } else {
            raiz->esq = inserir(raiz->esq, valor);
            if(*cresceu) {
                balancear(raiz, valor, *cresceu);
            }
        }
    }
    return raiz;
}

void balancear(arvore pivo, int valor, int *cresceu) {
    if(valor > pivo->dir) {
        switch(pivo->fb) {
            case 0:
                pivo->fb = 1;
                *cresceu = 1;
                break;
            case 1:
                *cresceu = 0; //porque ficaria desbalanceado, ele zera
                //o crescimento pq faz a rota��o
                return rotacao(pivo);
                break;
            case -1:
                *cresceu = 0; //aqui n�o cresceu, apenas adc um elemento � direita
                break;
        }
    } else {
        switch(pivo->fb) {
            case 0:
                pivo->fb = -1;
                *cresceu = 1;
                break;
            case 1:
                pivo->fb = 0;
                cresceu = 0;
                break;
            case -1:
                pivo->fb = 0;
                rotacao(pivo);
                break;
        }
    }

}

arvore rotacao(arvore pivo) {
    if (pivo->fb > 0) {
        // Rota��o � esquerda -> Desbalanceamento para a direita
        if (pivo->dir->fb >= 0) {
            if (pivo->dir->fb == 0) {
                pivo->fb = 1;
                pivo->dir->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
            }
            // Rota��o simples � esquerda
            return rotacaoSimplesEsquerda(pivo);
        } else {
            // Rota��o dupla � esquerda
            return rotacaoDuplaEsquerda(pivo);
        }
    } else {
        // Rota��o � direita -> Desbalanceamento para a esquerda
        if (pivo->esq->fb <= 0) {
            if (pivo->esq->fb == 0) {
                pivo->fb = -1;
                pivo->esq->fb = 1;
            } else {
                pivo->fb = 0;
                pivo->esq->fb = 0;
            }
            // Rota��o simples � direita
            return rotacaoSimplesDireita(pivo);
        } else {
            // Rota��o dupla � direita
            return rotacaoDuplaDireita(pivo);
        }
    }
}

arvore rotacaoSimplesEsquerda(arvore pivo) {
    arvore novaRaiz = pivo->dir;
    pivo->dir = novaRaiz->esq;
    novaRaiz->esq = pivo;
    return novaRaiz;
}

arvore rotacaoSimplesDireita(arvore pivo) {
    arvore novaRaiz = pivo->esq;
    pivo->esq = novaRaiz->dir;
    novaRaiz->dir = pivo;
    return novaRaiz;
}

arvore rotacaoDuplaEsquerda(arvore pivo) {
    pivo->dir = rotacaoSimplesDireita(pivo->dir);
    return rotacaoSimplesEsquerda(pivo);
}

arvore rotacaoDuplaDireita(arvore pivo) {
    pivo->esq = rotacaoSimplesEsquerda(pivo->esq);
    return rotacaoSimplesDireita(pivo);
}




