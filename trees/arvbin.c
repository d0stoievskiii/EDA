#include "arvbin.h"


int main() {
    TNoA* arv = cria(200, NULL, NULL);
    insere(arv, 100);
    insere(arv, 300);
    insere(arv, 80);
    insere(arv, 150);
    insere(arv, 250);
    insere(arv, 400);
    insere(arv, 70);
    insere(arv, 120);
    insere(arv, 220);
    insere(arv, 270);
    insere(arv, 350);
    insere(arv, 500);
    insere(arv, 65);
    insere(arv, 79);
    insere(arv, 110);
    insere(arv, 130);
    insere(arv, 260);

    printt(arv);

    remove_(arv, 100);
    printt(arv);

    remove_(arv, 150);
    printt(arv);

    remove_(arv, 80);
    printt(arv);

    remove_(arv, 270);
    printt(arv);

    remove_(arv, 400);
    printt(arv);

    remove_(arv, 200);
    printt(arv);

    return 0;
}