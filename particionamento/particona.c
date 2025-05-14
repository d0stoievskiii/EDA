#include "particionamento.h"

int main() {
    FILE* stream;
    stream = fopen("arq2.txt", "r");
    

    selecao_com_substituicao(stream, 6);
    rewind(stream);
    selecao_natural(stream, 6);

    return 0;
}