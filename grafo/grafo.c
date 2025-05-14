#include "grafo.h"


int main() {
    PTG i = NULL, ii = NULL;

    i = cria(1, NULL, NULL);
    i = insere_no(i, 2);
    i = insere_no(i, 3);
    i = insere_no(i, 4);
    i = insere_viz(i, 1, 2);
    i = insere_viz(i, 2, 3);
    i = insere_viz(i, 2, 4);
    i = insere_viz(i, 3, 4);
    i = insere_viz(i, 4, 1);
    //printg(i);
    //printf("=========================\n\n");

    ii = cria(1, NULL, NULL);
    ii = insere_no(ii, 2);
    ii = insere_no(ii, 3);
    ii = insere_no(ii, 7);
    ii = insere_no(ii, 5);
    ii = insere_no(ii, 4);
    ii = insere_no(ii, 6);
    ii = insere_viz(ii, 1, 2);
    ii = insere_viz(ii, 1, 3);
    ii = insere_viz(ii, 1, 7);
    ii = insere_bothways(ii, 5, 2);
    ii = insere_bothways(ii, 5, 3);
    ii = insere_bothways(ii, 5, 7);
    ii = insere_bothways(ii, 5, 4);
    ii = insere_viz(ii, 4, 6);
    ii = insere_viz(ii, 6, 1);
    printg(ii);
    printf("=========================\n");


    
    printf("Retira [3]\n");
    ii = retira_g(ii, 3);
    printg(ii);
    printf("=========================\n");

    printf("Retira [5]\n");
    ii = retira_g(ii, 5);
    printg(ii);
    printf("=========================\n");

    printf("Retira [1]\n");
    ii = retira_g(ii, 1);
    printg(ii);
    printf("=========================\n");


    printf("Retira [6]\n");
    ii = retira_g(ii, 6);
    printg(ii);
    printf("=========================\n");

    printf("Retira [7]\n");
    ii = retira_g(ii, 7);
    printg(ii);
    printf("=========================\n");

    printf("Retira [2]\n");
    ii = retira_g(ii, 2);
    printg(ii);
    printf("=========================\n");
    

    printf("Retira [4]\n");
    ii = retira_g(ii, 4);
    printg(ii);
    printf("=========================\n");

    return 0;
}