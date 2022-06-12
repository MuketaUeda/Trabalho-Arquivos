#include "indices.h"

regIndice_t *inicia_indice()
{
    // Inicializando todas as variáveis, sejam de dadosIndice tipo 1 ou tipo 2
    regIndice_t *dadosIndice = (regIndice_t *)malloc(1 * sizeof(regIndice_t));

    dadosIndice->id = -1;
    dadosIndice->proxRRN = 0;
    dadosIndice->offSet = 0;
    dadosIndice->tamanho = 0;

    return dadosIndice;
}

void ler_indices_tipo1(regIndice_t *indice, FILE *fp)
{
    int tamanho = 0;
    char removido; // Leremos so para nao termos que dar fseek de 1 byte
    int proxRRN;
    fread(&removido, sizeof(char), 1, fp);
    tamanho += sizeof(char);

    fread(&proxRRN, sizeof(int), 1, fp);
    // printf("RRN: %d\n", indice.proxRRN);

    tamanho += sizeof(int);
    fread(&indice->id, sizeof(int), 1, fp);
    // printf("id: %d\n", indice->id);
    tamanho += sizeof(int);

    fseek(fp, (97 - tamanho), SEEK_CUR);
}
int ler_indices_tipo2(regIndice_t *indice, FILE *fp)
{
    int tamanhoTotal = 0;
    int tamanhoRegistro = 0;
    char removido; // Leremos so para nao termos que dar fseek de 1 byte
    long long int proxByteOffset;

    fread(&removido, sizeof(char), 1, fp);
    tamanhoRegistro += sizeof(char);

    fread(&tamanhoTotal, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    printf("tamanho total: %d\n", tamanhoTotal);
    fread(&proxByteOffset, sizeof(long long int), 1, fp);
    tamanhoRegistro += sizeof(long long int);

    fread(&indice->id, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    

    fseek(fp, (tamanhoTotal - tamanhoRegistro), SEEK_CUR);
    return tamanhoTotal;
}

void escreve_indice(regIndice_t *indice, FILE *fp, int tipo)
{
    //  Escrever no arquivo, *em ordem*, usando como base cada o numero de bytes de cada informacao

    if(indice->id)
        fwrite(&indice->id, sizeof(int), 1, fp);
    if (tipo == 1)
    {
        if (indice->proxRRN)
            fwrite(&indice->proxRRN, sizeof(int), 1, fp);
    }

    if (tipo == 2)
    {
        fwrite(&indice->offSet, sizeof(long long int), 1, fp);
    }

    return;
}

void destruir_indice(regIndice_t *indice)
{
    if (indice)
    {
        free(indice);
    }
    return;
}
