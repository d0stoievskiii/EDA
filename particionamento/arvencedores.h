#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct arv_de_vencedores {
    struct arv_de_vencedores* esq, *dir, *vencedor;
    int val;
    int part;
} TAV, *PTAV;

PTAV cria_folha(int val, int part) {
    PTAV ret = (PTAV)malloc(sizeof(TAV));
    ret->val = val;
    ret->esq = NULL;
    ret->dir = NULL;
    ret->vencedor = NULL;
    ret->part = part;
    return ret;
}

PTAV cria(PTAV esq, PTAV dir) {
    PTAV ret = (PTAV)malloc(sizeof(TAV));
    ret->esq = esq;
    ret->dir = dir;
    ret->part = -1;
    if (esq && dir) {
        ret->vencedor = esq->val < dir->val ? esq : dir;
        ret->val = ret->vencedor->val;
    } else if (esq && !dir) {
        ret->vencedor = esq;
        ret->val = esq->val;
    } else if (!esq && dir) {
        ret->vencedor = dir;
        ret->val = dir->val;
    } else {
        //? exit bad input
    }
    return ret;
}

void print_aux(PTAV no, int nivel) {
    if (!no) {
        for (int i = 0; i < nivel; i++) printf("\t");
        printf("N\n");
        return;
    }
    print_aux(no->esq, nivel+1);
    for (int i = 0; i < nivel; i++) printf("\t");
    printf("%d\n", no->val);
    print_aux(no->dir, nivel+1);
}

void printt(PTAV no) {
    print_aux(no, 0);
    printf("===============================\n");
}


PTAV monta(FILE** file_vec, size_t n_particoes) {
    PTAV* folhas = (PTAV*)(malloc(sizeof(PTAV)*n_particoes));

    int num, j, k, nodes;
    for (int i = 0; i < n_particoes; i += 1) {
        fscanf(file_vec[i], "%d ", &num);
        folhas[i] = cria_folha(num, i);
    }


    nodes = n_particoes;
    while (nodes != 1) {
        k = 0;
        for (j= 1; j < nodes; j += 2) {
            folhas[k] = cria(folhas[j-1], folhas[j]);
            k += 1;
        }
        if (j == nodes) {
            //numero impar de particoes
            folhas[k] = cria(folhas[nodes-1], NULL);
        }
        nodes = (nodes%2) ? (int)(nodes/2)+1 : (int)(nodes/2);
    }
    
    return folhas[0];
}


PTAV update(PTAV a, int val, FILE** files) {
    if (a && a->val == val) {
        int replacement;
        a->esq = update(a->esq, val, files);
        a->dir = update(a->dir, val, files);
        if (!a->esq && !a->dir) {
            //folha
            if (!feof(files[a->part])) {
                fscanf(files[a->part], "%d ", &a->val);
            } else {
                a->val = INT_MAX;
            }
        } else {
            if (a->esq && a->dir) {
                a->vencedor = a->esq->val < a->dir->val ? a->esq : a->dir;
            } else {
                a->vencedor = a->esq ? a->esq : a->dir;
            }
            a->val = a->vencedor->val;
        }
    }
    return a;
}

void ordena(FILE** file_vec, size_t n_particoes, PTAV a) {
    FILE* out = fopen("out.txt", "w");
    while(a->val != INT_MAX) {
        fprintf(out, "%d ", a->val);
        a = update(a, a->val, file_vec);
        printt(a);
    }
}





