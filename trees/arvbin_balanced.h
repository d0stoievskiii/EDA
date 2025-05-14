#include <stdlib.h>
#include <stdio.h>

#define MAX(a,b) a > b ? a : b

typedef struct balanced_arvbin {
    int chave;
    struct balanced_arvbin *esq, *dir;
    int fn;

} TABB_AVL, TAVL, *PTAVL;

int M(int a, int b) {
    return a > b ? a : b;
}

int h(PTAVL a) {
    if (!a) {
        return -1;
    }

    return M(h(a->esq), h(a->dir)) +1;
}

int FN(PTAVL esq, PTAVL dir) {
    return h(dir) - h(esq);
}

PTAVL cria(int chave, PTAVL esq, PTAVL dir) {
    TAVL* ret;
    ret = (TAVL*)malloc(sizeof(TAVL));
    if (!ret) {
        return NULL;
    }
    ret->chave = chave;
    ret->esq = esq;
    ret->dir = dir;
    ret->fn = FN(esq, dir);

    return ret;
}

PTAVL copia(PTAVL a) {
    if (!a) {
        return NULL;
    }
    return cria(a->chave, copia(a->esq), copia(a->dir));
}

PTAVL espelho(PTAVL a) {
    if (!a) {
        return NULL;
    }
    return cria(a->chave, espelho(a->dir), espelho(a->esq));
}

PTAVL RSD(PTAVL a) {
    PTAVL b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    return b;
}

PTAVL RSE(PTAVL a) {
    PTAVL b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    return b;
}

PTAVL RED(PTAVL a) {
    a->esq = RSE(a->esq);
    return RSD(a);
}

PTAVL RDE(PTAVL a) {
    a->dir = RSD(a->dir);
    return RSE(a);
}

PTAVL insere(PTAVL a, int chave) {
    if (!a) {
        return cria(chave, NULL, NULL);
    }

    if (chave < a->chave) {
        //a->fn -= 1;
        a->esq = insere(a->esq, chave);
    } else if (chave > a->chave) {
        //a->fn += 1;
        a->dir = insere(a->dir, chave);
    } else {
        //double insert is problematic, we need to undo the fn alterations
        return a;
    }
    a->fn = FN(a->esq, a->dir);
    printf("FN %d [%d] (%d - %d)\n", a->chave, a->fn, h(a->dir), h(a->esq));

    if (a->fn == 2) {
        if (a->dir->fn >= 0) {
            printf("RSE %d!\n", a->chave);
            return RSE(a);
        } else {
            printf("RDE %d!\n", a->chave);
            return RDE(a);
        }
    } else if (a->fn == -2) {
        if (a->esq->fn <= 0) {
            printf("RSD %d!\n", a->chave);
            return RSD(a);
        } else {
            printf("RED %d!\n", a->chave);
            return RED(a);
        }
    } else {
        return a;
    }
}

PTAVL exclui(PTAVL a, int chave) {
    if (!a) {
        return NULL;
    }

    if (chave < a->chave) {
        a->esq = exclui(a->esq, chave);
    } else if (chave > a->chave) {
        a->dir = exclui(a->dir, chave);
    } else {
        PTAVL temp;
        if (!a->esq && !a->dir) {
            free(a);
            return NULL;
        } else if (a->esq && !a->dir) {
            temp = a->esq;
            free(a);
            return temp;
        } else if (!a->esq && a->dir) {
            temp = a->dir;
            free(a);
            return temp;
        } else {
            temp = a->esq;
            while(temp->dir) {
                temp = temp->dir;
            }
            a->chave = temp->chave;
            temp->chave = chave;
            a->esq = exclui(a->esq, chave);
        }
    }
    a->fn = FN(a->esq, a->dir);
    if (a->fn == 2) {
        if (a->dir->fn >= 0) {
            a = RSE(a);
        } else {
            a = RDE(a);
        }
    } else if (a->fn == -2) {
        if (a->esq->fn <= 0) {
            a = RSD(a);
        } else {
            a = RED(a);
        }
    }
    return a;
}

PTAVL exclui_par(PTAVL a) {
    if (!a) {
        return NULL;
    }
    printf("%d\n", a->chave);
    a->esq = exclui_par(a->esq);
    a->dir = exclui_par(a->dir);

    if (!(a->chave%2)) {
        printf("found par: [%d]\n", a->chave);
        PTAVL temp;
        int chave = a->chave;
        if (!a->esq && a->dir) {
            printf("a\n", a->chave);
            free(a);
            printf("b\n", a->chave);
            return NULL;
        } else if (a->esq && !a->dir) {
            temp = a->esq;
            free(a);
            return temp;
        } else if (!a->esq && a->dir) {
            temp = a->dir;
            free(a);
            return temp;
        } else {
            temp = a->esq;
            while (temp->dir) {
                temp = temp->dir;
            }
            a->chave = temp->chave;
            temp->chave = chave;
            a->esq = exclui_par(a->esq);
        }
    }

    a->fn = FN(a->esq, a->dir);
    if (a->fn == 2) {
        if (a->dir->fn >= 0) {
            a = RSE(a);
        } else {
            a = RDE(a);
        }
        a->fn = FN(a->esq, a->dir);
    } else if (a->fn == -2) {
        if (a->esq->fn <= 0) {
            a = RSD(a);
        } else {
            a = RED(a);
        }
        a->fn = FN(a->esq, a->dir);
    }
    return a;
}
int igual(PTAVL a, PTAVL b) {
    if (!a || !b) {
        return (!a && !b);
    }
    int esq = igual(a->esq, b->esq);
    int dir = igual(a->dir, b->dir);

    return (a->chave == b->chave) && esq && dir;
}

PTAVL busca(PTAVL a, int chave) {
    if (!a) {
        return NULL;
    }

    if (chave < a->chave) {
        return busca(a->esq, chave);
    } else if (chave > a->chave) {
        return busca(a->dir, chave);
    } else {
        return a;
    }
}

int valores_iguais(PTAVL a, PTAVL b) {
    if (!a) {
        return 1;
    }
    int esq = valores_iguais(a->esq, b);
    int dir = valores_iguais(a->dir, b);

    return (busca(b, a->chave) != NULL) && esq && dir;
}

int n(PTAVL a) {
    if (!a) {
        return 0;
    }
    int esq = n(a->esq);
    int dir = n(a->dir);
    return 1 + esq + dir;
}

void t2vec_aux(PTAVL a, int *v) {
    static int index = 0;
    if (!a) {
        return;
    }
    v[index] = a->chave;
    index += 1;
    t2vec_aux(a->esq, v);
    t2vec_aux(a->dir, v);
}

int* tree2vec(PTAVL a, int *len) {
    *len = n(a);
    if (!*len) {
        return NULL;
    }
    int* ret = (int*)malloc(sizeof(int)*(*len));
    t2vec_aux(a, ret);
    
    return ret;
}

void print_aux(PTAVL a, int nivel) {
    if (!a) {
        for (int j= 0; j < nivel; j++) printf("\t");
        printf("N\n");
        return;
    }
    print_aux(a->esq, nivel +1);
    for (int i= 0; i < nivel; i++) printf("\t");
    printf("%d\n", a->chave);
    print_aux(a->dir, nivel+1);
}

void print_TAVL(PTAVL a) {
    print_aux(a, 0);
    printf("===============================\n");
}