#include "indices.h"
 

regIndice_t *inicia_indice()
{
    // Inicializando todas as variáveis, sejam de dadosIndice tipo 1 ou tipo 2
    regIndice_t *dadosIndice = (regIndice_t *)malloc(1 * sizeof(regIndice_t));

    dadosIndice->id = -1;
    dadosIndice->proxRRN = -1;
    dadosIndice->proxOffset = -1;
    dadosIndice->tamanho = 0;

    return dadosIndice;
}

int ler_indices(regIndice_t *indice, FILE *fp, int tipo)
{

    int tamanho = 1;
    char removido; // Leremos so para nao termos que dar fseek de 1 byte
    fread(&removido, sizeof(char), 1, fp);
    if (tipo == 1)
    {
        fread(&indice->proxRRN, sizeof(int), 1, fp);
        tamanho += sizeof(int);
        fread(&indice->id, sizeof(int), 1, fp);
        tamanho += sizeof(int);
        fseek(fp, (97 - tamanho), SEEK_CUR);
        tamanho = 97 - tamanho;
    }
    if (tipo == 2)
    {
        fread(&tamanho, sizeof(int), 1, fp);
        fread(&indice->proxOffset, sizeof(long long int), 1, fp);
        tamanho += sizeof(long long int);
        fread(&indice->id, sizeof(int), 1, fp);
        tamanho += sizeof(int);
        fseek(fp, tamanho, SEEK_CUR);
    }
    return tamanho;
}

int escreve_indice(regIndice_t *indice, FILE *fp, int tipo, int tamanho)
{
    fseek(fp, tamanho, SEEK_SET);

    //  Escrever no arquivo, *em ordem*, usando como base cada o numero de bytes de cada informacao
    fwrite(&indice->status, sizeof(char), 1, fp);
    tamanho++;

    if (tipo == 1)
    {
        fwrite(&indice->proxRRN, sizeof(int), 1, fp);
        tamanho += 4;
    }

    if (tipo == 2)
    {
        fwrite(&indice->proxOffset, sizeof(long long int), 1, fp);
        tamanho += 8;
    }

    return tamanho;
}

void destruir_indice(regIndice_t *indice)
{
    if (indice)
    {
        free(indice);
    }
    return;
}
