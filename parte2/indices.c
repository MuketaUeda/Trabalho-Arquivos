#include "indices.h"

regIndice_t *inicia_indice()
{
    // Inicializando todas as variáveis, sejam de dadosIndice tipo 1 ou tipo 2
    regIndice_t *dadosIndice = (regIndice_t *)malloc(1 * sizeof(regIndice_t));

    dadosIndice->id = -1;
    dadosIndice->proxRRN = 0;
    dadosIndice->offSet = 0;

    return dadosIndice;
}

char ler_indices_tipo1(regIndice_t *indice, FILE *fp)
{
    int tamanho = 0;
    char removido; // Leremos para verificar se o registro foi removido ou nao. Retornamos para fazermos essa verificacao
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
    return removido;
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

void LeIndices(regIndice_t *indice, FILE *fp, int tipo){
    int tam = 0;
    if(tipo == 1){
            fread(&indice->id,sizeof(int), 1, fp);
            tam += sizeof(int);
            fread(&indice->proxRRN, sizeof(int), 1, fp);
            tam += sizeof(int);
            //fseek(fp, 0, SEEK_CUR);
    }

    if(tipo == 2){
        fread(&indice->id, sizeof(int), 1, fp);
        tam += sizeof(int);
        fread(&indice->offSet, sizeof(long long int), 1, fp);
        tam += sizeof(long long int);
        //fseek(fp, 0, SEEK_CUR);
    }
    return;
}