#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void selecao_com_substituicao(FILE* f, int m) {
    int* vec = (int*)malloc(sizeof(int)*m);
    int* congelados = (int*)malloc(sizeof(int)*m);

    char file_counter = 97;
    char ret[8] = {'p', 'a', 'r', 't', '_', 's', '0', '\0'};
    ret[6] = file_counter;
    FILE* out = fopen(ret,"w");

    for (int i = 0; i < m; i++) {
        fscanf(f, "%d ", (vec + i));
        congelados[i] = 0;
    }

    int menor, index, counter = 0;
    while(!feof(f)) {
        menor = INT_MAX;
        index = -1;

        if (counter == m) {
            //all frozen
            fclose(out);
            file_counter += 1;
            ret[6] = file_counter;
            out = fopen(ret, "w");
            for (int i = 0; i < m; i++) {
                congelados[i] = 0;
            }
            counter = 0;
        }

        for (int i = 0; i < m; i++) {
            if (vec[i] < menor && (!congelados[i])) {
                menor = vec[i];
                index = i;
            }
        }

        fprintf(out, "%d ", menor);
        fscanf(f, "%d ", (vec + index));

        if (vec[index] < menor) {
            //congela
            counter += 1;
            congelados[index] = 1;
        }
    }
    //finish curr part
    int faltando = 0;
    while(faltando < m - counter) {
        menor = INT_MAX;
        index = -1;
        for (int i = 0; i < m; i++) {
            if ((!congelados[i]) && menor > vec[i]) {
                menor = vec[i];
                index = i;
            }
        }
        fprintf(out, "%d ", menor);
        vec[index] = INT_MAX;
        faltando += 1;
    }
    fclose(out);
    out = NULL;
    if (counter) {
        file_counter += 1;
        ret[6] = file_counter;
        out = fopen(ret, "w");
    }
    while (counter) {
        menor = INT_MAX;
        index = -1;
        for (int i = 0; i < m; i++) {
            if ((congelados[i]) && menor > vec[i]) {
                menor = vec[i];
                index = i;
            }
        }
        fprintf(out, "%d ", menor);
        vec[index] = INT_MAX;
        counter -= 1;
    }
    if (out) {
        fclose(out);
    }
}


void selecao_natural(FILE* f, int m) {
    int* vec = (int*)malloc(sizeof(int)*m);
    FILE* out, *reservatorio;

    char file_counter = 97;
    char ret[9] = {'p', 'a', 'r', 't', '_', 's', 'n', '0', '\0'};
    ret[7] = file_counter;
    out = fopen(ret,"w");
    reservatorio = fopen("reservatorio", "w+");

    for (int i = 0; i < m; i++) {
        fscanf(f, "%d ", (vec+i));
    }

    int menor, index, counter = 0;
    //main loop ate o final do arquivo
    while (!feof(f)) {
        menor = INT_MAX;
        index = -1;

        for (int i = 0; i < m; i++) {
            if (menor > vec[i]) {
                menor = vec[i];
                index = i;
            }
        }

        fprintf(out, "%d ", menor);
        fscanf(f, "%d ", (vec + index));
        while (vec[index] < menor && counter < m && !feof(f)) {
            //vai pro reservatorio
            fprintf(reservatorio, "%d ", vec[index]);
            counter += 1;
            if (counter == m) {
                vec[index] = INT_MAX;
                break;
            }
            fscanf(f, "%d ", (vec + index));
        }
        
        if (counter == m) {
            for (int i = 0; i < m; i++) {
                menor = INT_MAX;
                index = -1;
                for (int j = 0; j < m; j++) {
                    if (vec[j] < menor) {
                        menor = vec[j];
                        index = j;
                    }
                }
                if (index != -1) {
                    fprintf(out, "%d ", menor);
                    vec[index] = INT_MAX;
                }
            }
            fclose(out);
            
            rewind(reservatorio);
            for (int i = 0; i < m; i++) {
                fscanf(reservatorio, "%d ", (vec + i));
            }
            rewind(reservatorio);

            file_counter += 1;
            ret[7] = file_counter;
            out = fopen(ret, "w");
            counter = 0;
        }

    }
    //esvazia o vetor
    for (int i = 0; i < m; i++) {
        menor = INT_MAX;
        index = -1;
        for (int j = 0; j < m; j++) {
            if (vec[j] < menor) {
                menor = vec[j];
                index = j;
            }
        }
        if (index != -1) {
            fprintf(out, "%d ", menor);
            vec[index] = INT_MAX;
        }
    }
    fclose(out);
    file_counter += 1;
    ret[7] = file_counter;
    out = fopen(ret, "w");
    rewind(reservatorio);
    //termina a ultima particao com o que sobrar no reservatorio
    for (int i = 0; i < counter; i++) {
        fscanf(reservatorio, "%d ", (vec + i));
    }
    int c = counter;
    while (counter) {
        menor = INT_MAX;
        index = -1;
        for (int i = 0; i < c; i++) {
            if(menor > vec[i]) {
                menor = vec[i];
                index = i;
            }
        }
        fprintf(out, "%d ", menor);
        vec[index] = INT_MAX;
        counter -= 1;
    }
    fclose(out);
    fclose(reservatorio);
}