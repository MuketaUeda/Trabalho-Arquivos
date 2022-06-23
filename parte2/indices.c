/*
Trabalho 2 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
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

char ler_indices_dados_tipo1(regIndice_t *indice, FILE *fp)
{
    int tamanho = 0;
    char removido; // Leremos para verificar se o registro foi removido ou nao. Retornamos para fazermos essa verificacao
    int proxRRN;
    fread(&removido, sizeof(char), 1, fp);
    tamanho += sizeof(char);

    fread(&proxRRN, sizeof(int), 1, fp);

    tamanho += sizeof(int);
    fread(&indice->id, sizeof(int), 1, fp);
    tamanho += sizeof(int);

    fseek(fp, (97 - tamanho), SEEK_CUR);
    return removido;
}

void escreve_indice(regIndice_t *indice, FILE *fp, int tipo)
{
    //  Escrever no arquivo, *em ordem*, usando como base cada o numero de bytes de cada informacao

    if (indice->id)
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

int ler_arquivo_indices(regIndice_t *indice, FILE *fp, int tipo)
{
    int tam = 0;
    if (tipo == 1)
    {
        fread(&indice->id, sizeof(int), 1, fp);
        // printf("id: %d\n", indice->id);
        tam += sizeof(int);
        fread(&indice->proxRRN, sizeof(int), 1, fp);
        tam += sizeof(int);
        return tam;
    }

    if (tipo == 2)
    {
        fread(&indice->id, sizeof(int), 1, fp);
        tam += sizeof(int);
        fread(&indice->offSet, sizeof(long long int), 1, fp);
        tam += sizeof(long long int);
        // fseek(fp, 12, SEEK_CUR);
        return tam;
    }

    return -1;
}

int remover_elemento_array(regIndice_t *indice, int posicao, int tamanho, int tipoArquivo)
{
    for (int i = posicao; i < tamanho; i++)
    {
        indice[i].id = indice[i + 1].id;
        if(tipoArquivo == 1)
            indice[i].proxRRN = indice[i + 1].proxRRN;
        else
            indice[i].offSet = indice[i + 1].offSet;
    }
    indice = (regIndice_t *)realloc(indice, (--tamanho) * sizeof(regIndice_t));

    return tamanho;
}