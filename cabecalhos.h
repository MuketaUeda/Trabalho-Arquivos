#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct regCabTipo1 cabecalhoTipo1_t;
typedef struct regCabTipo2 cabecalhoTipo2_t;

struct regCabTipo1{
    //Repare que foi somado 1 ao tamanho de cada array, por conta de /0
    //verificar se ha nescessidade de um bit a mais
    char status;
    int topo;
    char desc[41];
    char desCodigo[23];
    char desAno[20];
    char desQuantidade[25];
    char desEstado[9];
    char codNome; //'0'
    char desNome[17];
    char codMarca; //'1'
    char desMarca[19];
    char codModelo; //'2'
    char desModelo[20];
    int proxRRN; //inicia com zero
    int nroRegRemovidos; //inicia com zero
};

struct regCabTipo2{
    //struct para arquivos variavies do tipo2
    char status;
    long long int topo;
    char desc[41];
    char desCodigo[23];
    char desAno[20];
    char desQuantidade[25];
    char desEstado[9];
    char codNome; //'0'
    char desNome[17];
    char codMarca; //'1'
    char desMarca[19];
    char codModelo; //'2'
    char desModelo[20];
    long long int proxByteOffset; //inicia com zero
    int nroRegRemovidos; //inicia com zero
};


cabecalhoTipo1_t *inicia_cab_tipo1();
void escreve_cabecalho1_arquivo(cabecalhoTipo1_t *cabecalho, FILE *fp);
void ler_cab_tipo1_arquivo(FILE *fp, cabecalhoTipo1_t *cabecalho);

cabecalhoTipo2_t *inicia_cab_tipo2();
void ler_cab_tipo2_arquivo(FILE *fp, cabecalhoTipo2_t *cabecalho);
