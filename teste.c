#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    arvore minhaArvore = NULL;
    int cresceu;

    minhaArvore = inserir(minhaArvore, 3, &cresceu);
    minhaArvore = inserir(minhaArvore, 5, &cresceu);
    minhaArvore = inserir(minhaArvore, 7, &cresceu);

    printf("Preorder: ");
    preorder(minhaArvore);
    printf("\n");

    printf("Inorder: ");
    inorder(minhaArvore);
    printf("\n");

    printf("Posorder: ");
    posorder(minhaArvore);
    printf("\n");

    return 0;
}
