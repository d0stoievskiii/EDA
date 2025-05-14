#include "arvbin_balanced.h"

int main() {


    TAVL* arv = NULL;
    int chvs[] = {50, 40, 30, 45, 47, 55, 56, 1, 2, 3, 49};
    for (int i = 0; i < 11; i++) {
        arv = insere(arv, chvs[i]);
    }
    print_TAVL(arv);

    TAVL* arv2 = NULL;
    int chvs2[] = {40, 30, 45, 47, 55, 56, 1, 2, 3, 49, 50};
    for (int i = 0; i < 11; i++) {
        arv2 = insere(arv2, chvs2[i]);
    }
    print_TAVL(arv2);

    printf("IGUAL(a, a) [%s]\n", (igual(arv, arv) == 1) ? "true": "false");
    printf("IGUAL(a, b) [%s]\n", (igual(arv, arv2) == 1) ? "true": "false");
    printf("VALORES_IGUAIS(a, a) [%s]\n", (valores_iguais(arv, arv) == 1) ? "true": "false");
    printf("VALORES_IGUAIS(a, b) [%s]\n", (valores_iguais(arv, arv2) == 1) ? "true": "false");

    int len;
    int* vec = tree2vec(arv, &len);
    printf("LEN(a): [%d]\n", len);
    for (int i = 0; i < len; i++) {
        printf("%d\n", *(vec + i));
    }

    print_TAVL(arv);
    arv = exclui_par(arv);
    print_TAVL(arv);


    /*
    int toremove = 0;
    while (toremove != -1) {
        scanf("%d", toremove);
        printf("remove [%d]\n", toremove);
        arv = exclui(arv, toremove);
        print_TAVL(arv);
    }
    */

    return 0;
}