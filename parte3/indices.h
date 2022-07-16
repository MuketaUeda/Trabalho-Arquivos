/*
Trabalho 3 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct regIndice regIndice_t;

// Unificamos as structs dos registros de dados e cabecalho dos indices do tipo 1 e do tipo 2 pelo fato de serem bem similares.
struct regIndice
{
    int id;
    int RRN;
    long long int offSet;
};

regIndice_t *inicia_indice();

char ler_indices_dados_tipo1(regIndice_t *indice, FILE *fp);
void escreve_indice(regIndice_t *indice, FILE *fp, int tipo);
void destruir_indice(regIndice_t *indice);
int ler_arquivo_indices(regIndice_t *indice, FILE *fp, int tipo);
int remover_elemento_array(regIndice_t *indice, int posicao, int tamanho, int tipoArquivo);
void atualiza_elemento_array(regIndice_t *indice, int posicao, int tipoArquivo, char *nomeCampo, int valorCampo);
regIndice_t *insertionSort(regIndice_t *indices, int tamanho);