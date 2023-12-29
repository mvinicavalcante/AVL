#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
    arvore minhaArvore = NULL;
    int cresceu;

    minhaArvore = inserir(minhaArvore, 7, &cresceu);
    minhaArvore = inserir(minhaArvore, 5, &cresceu);
    minhaArvore = inserir(minhaArvore, 3, &cresceu);

    printf("Preorder: ");
    preorder(minhaArvore);
    printf("\n");

    printf("Inorder: ");
    inorder(minhaArvore);
    printf("\n");

    printf("Posorder: ");
    posorder(minhaArvore);
    printf("\n");

    minhaArvore = remover(minhaArvore, 5);

    printf("Preorder - pos remocao: ");
    preorder(minhaArvore);
    printf("\n");

    return 0;
}
