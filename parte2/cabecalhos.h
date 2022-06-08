/*
Trabalho 1 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct regCabTipo1 cabecalho_t;
typedef struct regCabTipo2 cabecalhoTipo2_t;

struct regCabTipo1{
    //Repare que foi somado 1 ao tamanho de cada array, por conta de /0 no fim. 
    //Primeiramente, não adicionamos e tivemos problemas com lixo de memória.
    char status;
    long long int topo;
    char desc[41];
    char desCodigo[23];
    char desAno[20];
    char desQuantidade[25];
    char desEstado[9];
    char codNomeCidade; //'0'
    char desNomeCidade[17];
    char codMarca; //'1'
    char desMarca[19];
    char codModelo; //'2'
    char desModelo[20];
    int proxRRN; //inicia com zero
    long long int proxByteOffset;
    int nroRegRemovidos; //inicia com zero
};



cabecalho_t *inicia_cabecalho();
void escreve_cabecalho_arquivo(cabecalho_t *cabecalho, FILE *fp, int tipo);
void ler_cab_arquivo(FILE *fp, cabecalho_t *cabecalho, int tipo);