#include <stdlib.h>
#include <stdio.h>


int maior_int(int a, int b) {
    return a > b ? a : b;
}
#define MAX(a,b) maior_int(a,b)

typedef struct NoA {
    int chave;
    struct NoA* esq, *dir;
} TNoA, *PTNoA;

PTNoA cria(int chave, TNoA* esq, TNoA* dir) {
    TNoA* ret;
    ret = (TNoA*)malloc(sizeof(TNoA));
    if (!ret) {
        return NULL;
    }
    ret->esq = esq;
    ret->dir = dir;
    ret->chave = chave;
    return ret;
}

void deleta(TNoA* arv) {
    if (!arv) {
        return;
    }
    deleta(arv->esq);
    deleta(arv->dir);
    free(arv);
}

PTNoA insere(TNoA* no, int chave) {
    if (!no) {
        return cria(chave, NULL, NULL);
    }

    if (chave < no->chave) {
        no->esq = insere(no->esq, chave);
    } else if (chave > no->chave) {
        no->dir = insere(no->dir, chave);
    }
    return no;    
}

PTNoA busca(TNoA* no, int chave) {
    if (!no) {
        return NULL;
    }

    if (chave < no->chave) {
        return busca(no->esq, chave);
    } else if (chave > no->chave) {
        return busca(no->dir, chave);
    }
    return no;
}

PTNoA remove_(TNoA* no, int chave) {
    
    if (!no) {
        return NULL;
    }

    if (chave < no->chave) {
        no->esq = remove_(no->esq, chave);
    } else if (chave > no->chave) {
        no->dir = remove_(no->dir, chave);
    } else {
        TNoA* temp;
        //caso folha
        if (!no->esq && !no->dir) {
            free(no);
            return NULL;
        } else if (no->esq && !no->dir) {
            temp = no->esq;
            free(no);
            return temp;
        } else if (!no->esq && no->dir) {
            temp = no->dir;
            free(no);
            return temp;
        } else {
            //caso 2 subarvores
            //elemento mais a direita do elemento a esquerda
            TNoA* sub = no->esq;
            while(sub->dir) {
                sub = sub->dir;
            }
            printf("sub is %d\n", sub->chave);
            no->chave = sub->chave;
            sub->chave = chave;
            no->esq = remove_(no->esq, chave);
        }
    }
    return no;
}

void print_aux(TNoA* no, int nivel) {
    if (!no) {
        for (int i = 0; i < nivel; i++) printf("\t");
        printf("N\n");
        return;
    }
    print_aux(no->esq, nivel+1);
    for (int i = 0; i < nivel; i++) printf("\t");
    printf("%d\n", no->chave);
    print_aux(no->dir, nivel+1);
}

void printt(TNoA* no) {
    print_aux(no, 0);
    printf("===============================\n");
}

PTNoA copia(TNoA* arv) {
    if (!arv) {
        return NULL;
    }
    return cria(arv->chave, copia(arv->esq), copia(arv->dir));
}

PTNoA copia_invertida(TNoA* arv) {
    if (!arv) {
        return NULL;
    }
    return cria(arv->chave, copia_invertida(arv->dir), copia_invertida(arv->esq));
}

void inverte(TNoA* arv) {
    PTNoA temp;
    if (!arv) {
        return;
    }
    inverte(arv->esq);
    inverte(arv->dir);
    temp = arv->esq;
    arv->esq = arv->dir;
    arv->dir = temp;
}

int n(TNoA* no) {
    if (!no) {
        return 0;
    }
    return n(no->esq) + n(no->dir) + 1;
}

int n_folhas(TNoA* no) {
    if (!no) {
        return 0;
    }
    if (!no->esq && !no->dir) {
        return 1;
    }
    return n_folhas(no->esq) + n_folhas(no->dir);
}

int n_interno(TNoA* no) {
    if (!no || !no->esq && !no->dir) {
        return 0;
    }
    return n_interno(no->esq) + n_interno(no->dir) +1;
}

int h(TNoA* no) {
    if (!no) {
        return -1;
    }
    return MAX(h(no->esq), h(no->dir)) +1;
}

PTNoA maior(TNoA* no) {
    if (!no) {
        return NULL;
    }

    TNoA* dir = maior(no->dir);
    if (!dir) {
        return no;
    } else {
        return dir;
    }
}

PTNoA maior2(TNoA* no) {
    if (!no) {
        return NULL;
    }
    TNoA* esq = maior2(no->esq);
    TNoA* dir = maior2(no->dir);
    if (!esq && !dir) {
        return no;
    } else if (!esq && dir) {
        return dir->chave > no->chave ? dir : no;
    } else if (esq && !dir) {
        return esq->chave > no->chave ? esq : no;
    } else {
        TNoA* ret = esq->chave > dir->chave ? esq : dir;
        return ret->chave > no->chave ? ret : no;
    }
}

PTNoA menor(TNoA* no) {
    if (!no) {
        return NULL;
    }
    TNoA* esq = menor(no->esq);
    TNoA* dir = menor(no->dir);
    if ((esq && esq->chave < no->chave) || (dir && dir->chave < no->chave)) {
        if (!esq) return dir;
        if (!dir) return esq;
        return esq->chave < dir->chave ? esq : dir;
    }
    return no;
}
