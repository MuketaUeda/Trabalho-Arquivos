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
    dadosIndice->RRN = 0;
    dadosIndice->offSet = 0;

    return dadosIndice;
}

//funcao de leitura de indices apenas para arquivos do tipo1
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

//insere no arquivo os indices carregados previamente na RAM
void escreve_indice(regIndice_t *indice, FILE *fp, int tipo)
{
    //  Escrever no arquivo, *em ordem*, usando como base cada o numero de bytes de cada informacao

    if (indice->id)
        fwrite(&indice->id, sizeof(int), 1, fp);
    if (tipo == 1)
    {
        if (indice->RRN)
            fwrite(&indice->RRN, sizeof(int), 1, fp);
    }

    if (tipo == 2)
    {
        fwrite(&indice->offSet, sizeof(long long int), 1, fp);
    }

    return;
}

//libera os dados alocados do tipo indice
void destruir_indice(regIndice_t *indice)
{
    if (indice)
    {
        free(indice);
    }
    return;
}

//faz a leitura dos valores dentro do arquivo de indices
int ler_arquivo_indices(regIndice_t *indice, FILE *fp, int tipo)
{
    int tam = 0;
    if (tipo == 1)
    {
        fread(&indice->id, sizeof(int), 1, fp);
        tam += sizeof(int);
        fread(&indice->RRN, sizeof(int), 1, fp);
        tam += sizeof(int);
        return tam;
    }

    if (tipo == 2)
    {
        fread(&indice->id, sizeof(int), 1, fp);
        tam += sizeof(int);
        fread(&indice->offSet, sizeof(long long int), 1, fp);
        tam += sizeof(long long int);
        return tam;
    }

    return -1;
}

//remove uma struct do array de structs
int remover_elemento_array(regIndice_t *indice, int posicao, int tamanho, int tipoArquivo)
{
    for (int i = posicao; i < tamanho; i++)
    {
        indice[i].id = indice[i + 1].id;
        if (tipoArquivo == 1)
            indice[i].RRN = indice[i + 1].RRN;
        else
            indice[i].offSet = indice[i + 1].offSet;
    }
    indice = (regIndice_t *)realloc(indice, (--tamanho) * sizeof(regIndice_t));

    return tamanho;
}

//funcao utilizada para atualizar o array de struct do tipo indice, usada para tipo1 e tipo2 de arquivo
void atualiza_elemento_array(regIndice_t *indice, int posicao, int tipoArquivo, char *nomeCampo, int valorCampo)
{
    if (strcmp("id", nomeCampo) == 0)
    {
        indice[posicao].id = valorCampo;
    }
    if (strcmp("rrn", nomeCampo) == 0)
    {
        indice[posicao].RRN = valorCampo;
    }
    if (strcmp("offset", nomeCampo) == 0)
    {
        indice[posicao].offSet = valorCampo;
    }
}

/* Function to sort an array using insertion sort*/
regIndice_t *insertionSort(regIndice_t *indices, int tamanho)
{
    int i, keyId, keyProxRRN, keyProxOffset, j;
    for (i = 1; i < tamanho; i++)
    {
        keyId = indices[i].id;
        keyProxRRN = indices[i].RRN;
        keyProxOffset = indices[i].offSet;
        j = i - 1;

        //Move elementos do indeices[0..i-1], que sejam maiores que a Key
        //para uma posicao afrente da posicao atual
        while (j >= 0 && indices[j].id > keyId)
        {
            indices[j + 1] = indices[j];
            j = j - 1;
        }
        indices[j + 1].id = keyId;
        indices[j + 1].RRN = keyProxRRN;
        indices[j + 1].offSet = keyProxOffset;
    }
    return indices;
}