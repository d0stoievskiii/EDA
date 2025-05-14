#include <stdlib.h>
#include <stdio.h>

typedef struct v {
    int id;
    struct v* prox;
} viz, *pviz;

typedef struct g {
    int id;
    struct g *prox;
    viz* prim;
} TG, *PTG;

pviz cria_viz(int id, pviz prox) {
    pviz ret = (pviz)malloc(sizeof(viz));
    ret->id = id;
    ret->prox = prox;

    return ret;
}

PTG cria(int id, PTG prox, pviz primeiro) {
    PTG ret = (PTG)malloc(sizeof(TG));
    ret->id = id;
    ret->prim = primeiro;
    ret->prox = prox;

    return ret;
}

void cleanup_aux(pviz viz) {
    if (viz) {
        cleanup_aux(viz->prox);
        free(viz);
    }
}

void cleanup(PTG g) {
    if (g) {
        cleanup_aux(g->prim);
        cleanup(g->prox);
        free(g);
    }
}

PTG busca(PTG g, int id) {
    if (!g) {
        return NULL;
    }
    if (g->id == id) {
        return g;
    }
    return busca(g->prox, id);
}

pviz busca_viz(PTG g, int id) {
    if (!g) {
        return NULL;
    }

    pviz ret = g->prim;

    while (ret) {
        if (ret->id == id) break;
        ret = ret->prox;
    }
    return ret;
}

PTG insere_no(PTG g, int id) {
    PTG novo = cria(id, NULL, NULL);
    PTG aux = g;
    while(aux->prox) {
        aux = aux->prox;
    }
    aux->prox = novo;
    return g;
}

PTG insere_viz(PTG g, int id, int idviz) {
    PTG no = busca(g, id);
    PTG no2 = busca(g, idviz);
    if (no && no2) {
        pviz insert = cria_viz(idviz, NULL);
        pviz last = no->prim;
        if (!last) {
            no->prim = insert;
            return g;
        }
        while(last->prox) {
            last = last->prox;
        }
        last->prox = insert;
    }
    return g;
}

PTG insere_bothways(PTG g, int id1, int id2) {
    g = insere_viz(g, id1, id2);
    g = insere_viz(g, id2, id1);
    return g;
}

PTG retira_viz(PTG g, int id1, int id2) {
    if (!g) {
        return NULL;
    }

    if (g->id == id1) {
        pviz prim = g->prim, ante = NULL;
        while(prim && prim->id != id2) {
            //printf("(%d)\n", prim->id);
            ante = prim;
            prim = prim->prox;
        }
        if (prim) {
            if (ante) {
                ante->prox = prim->prox;
            } else {
                g->prim = prim->prox;
            }
            free(prim);
        }
    }
    return g;
}

PTG retira_g(PTG g, int id) {
    if (g) {
        PTG aux;
        if (g->id != id) {
            g = retira_viz(g, g->id, id);
            g->prox = retira_g(g->prox, id);
        } else {
            printf("c\n");
            cleanup_aux(g->prim);
            g->prim = NULL;
            aux = g;
            g = retira_g(aux->prox, id);
            free(aux);
        }
    }
    return g;
}

void printg(PTG g) {
    if (g) {
        printf("[%d] ", g->id);
        pviz viz = g->prim;
        while(viz) {
            printf("-> (%d)", viz->id);
            viz = viz->prox;
        }
        printf("\n");
        printg(g->prox);
    }
}

