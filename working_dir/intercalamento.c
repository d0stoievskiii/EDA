#include "arvencedores.h"

int main() {
    size_t n = 5;
    char file_counter = 97;
    FILE** files = (FILE**)malloc(sizeof(FILE*)*n);
    char fname[9] = {'p', 'a', 'r', 't', '_', 's', 'n', '0', '\0'};
    for (int i = 0; i < n; i++) {
        fname[7] = file_counter;
        files[i] = fopen(fname, "r");
        printf("opened %s\n", fname);
        file_counter += 1;
    }
    PTAV arv = monta(files, n);
    printt(arv);
    ordena(files, 5, arv);
}