#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

/*
    inicializa��o
        p
       / \
      t1  u
         / \
        t2  t3


    final
        u
       / \
      p   t3
     / \
    t1  t2

*/

arvore rotacao_simples_esquerda(arvore pivo) {
    // Inicializa��o
    arvore u, t1, t2, t3;
    u = pivo->dir;
    t1 = pivo->esq;
    t2 = u->esq;
    t3 = u->dir;

    // Atualiza��o dos ponteiros
    u->esq = pivo;
    pivo->dir = t2;

    return u;
}

arvore rotacao_simples_direita(arvore pivo) {
    // Inicializa��o
    arvore u, t1, t2, t3;
    u = pivo->esq;
    t1 = pivo->dir;
    t2 = u->dir;
    t3 = u->esq;

    // Atualiza��o dos ponteiros
    u->dir = pivo;
    pivo->esq = t2;

    return u;
}

arvore rotacao_dupla_esquerda(arvore pivo) {
    pivo->dir = rotacao_simples_direita(pivo->dir);
    return rotacao_simples_esquerda(pivo);
}

arvore rotacao_dupla_direita(arvore pivo) {
    pivo->esq = rotacao_simples_esquerda(pivo->esq);
    return rotacao_simples_direita(pivo);
}

arvore rotacao(arvore pivo) {
    if (pivo->fb > 0) {
        // Rota��o esquerda
        if (pivo->dir->fb >= 0) {
            if (pivo->dir->fb == 0) {
                pivo->fb = 1;
                pivo->dir->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
            }
            return rotacao_simples_esquerda(pivo);
        } else {
            return rotacao_dupla_esquerda(pivo);
        }
    } else {
        // Rota��o direita
        if (pivo->esq->fb <= 0) {
            if (pivo->esq->fb == 0) {
                pivo->fb = -1;
                pivo->esq->fb = 1;
            } else {
                pivo->fb = 0;
                pivo->esq->fb = 0;
            }
            return rotacao_simples_direita(pivo);
        } else {
            return rotacao_dupla_direita(pivo);
        }
    }
}

arvore inserir(arvore raiz, int valor, int *cresceu) {
    // Caso base
    if (raiz == NULL) {
        // 1. Alocar espa�o em mem�ria
        arvore nova = (arvore) malloc(sizeof(struct no));
        // 2. Inicializar o novo n�
        nova->valor = valor;
        nova->esq = NULL;
        nova->dir = NULL;
        nova->fb = 0;

        // 3. Retornar o ponteiro para a raiz (relativa) da nova �rvore
        *cresceu = 1;
        return nova;
    } else {
        if (valor > raiz->valor) {
            raiz->dir = inserir(raiz->dir, valor, cresceu);
            if (*cresceu == 1) {
                switch (raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        *cresceu = 0;
                        return rotacao(raiz);
                    case -1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                }
            }
        } else {
            raiz->esq = inserir(raiz->esq, valor, cresceu);

            if (*cresceu) {
                switch (raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *cresceu = 1;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case -1:
                        *cresceu = 0;
                        return rotacao(raiz);
                }
            }
        }
        return raiz;
    }
}

void preorder(arvore raiz) {
    if (raiz != NULL) {
        printf("[%d]", raiz->valor);
        preorder(raiz->esq);
        preorder(raiz->dir);
    }
}

void inorder(arvore raiz) {
    if (raiz != NULL) {
        inorder(raiz->esq);
        printf("[%d]", raiz->valor);
        inorder(raiz->dir);
    }
}

void posorder(arvore raiz) {
    if (raiz != NULL) {
        posorder(raiz->esq);
        posorder(raiz->dir);
        printf("[%d]", raiz->valor);
    }
}

arvore maior(arvore raiz) {
    if(raiz == NULL) {
        printf("Raiz vazia");
        return -1;
    } else {
        if(raiz->dir != NULL) {
            maior(raiz->dir);
        }
        if(raiz->dir == NULL) {
            return raiz;
        }
    }
}

arvore remover(arvore raiz, int valor) {
    if(raiz == NULL) {
        return raiz;
    } else {
        if(raiz->valor == valor) {
            //caso de um filho
            if(raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                return NULL;
            }

            //caso de um filho � esquerda
            //guardo o ponteiro da mem�ria que armazena o filho esquerdo
            //e drop na raiz em quest�o
            if(raiz->esq != NULL && raiz->dir == NULL) {
                arvore retorno = raiz->esq;
                free(raiz);
                return retorno;
            }

            //caso de um filho � direita
            if(raiz->esq == NULL && raiz->dir != NULL) {
                arvore retorno = raiz->dir;
                free(raiz);
                return retorno;
            }

            //caso de dois filhos
            if(raiz->esq != NULL && raiz->dir != NULL) {
                int maiorValorEsquerda = maior(raiz->esq)->valor;
                raiz->valor = maiorValorEsquerda;
                raiz->esq = remover(raiz->esq, maiorValorEsquerda);
                return raiz;
            }
        } else {
            if(valor > raiz->valor) {
                raiz->dir = remover(raiz->dir, valor);
            } else {
                raiz->esq = remover(raiz->esq, valor);
            }
        }
    }

}


