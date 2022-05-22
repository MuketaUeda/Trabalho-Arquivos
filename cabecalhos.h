#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct regCabTipo1 cabecalho_t;
typedef struct regCabTipo2 cabecalhoTipo2_t;

struct regCabTipo1{
    //Repare que foi somado 1 ao tamanho de cada array, por conta de /0
    //verificar se ha nescessidade de um bit a mais
    char status;
    long long int topo;
    char desc[40];
    char desCodigo[22];
    char desAno[19];
    char desQuantidade[24];
    char desEstado[8];
    char codNome; //'0'
    char desNome[16];
    char codMarca; //'1'
    char desMarca[18];
    char codModelo; //'2'
    char desModelo[19];
    int proxRRN; //inicia com zero
    long long int proxOffset;
    int nroRegRemovidos; //inicia com zero
};

/*struct regCabTipo2{
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
};*/


cabecalho_t *inicia_cabecalho();
void escreve_cabecalho_arquivo(cabecalho_t *cabecalho, FILE *fp, int tipo);
void ler_cabecalho_arquivo(FILE *fp, cabecalho_t *cabecalho, int tipo);
void destroi_cabecalho(cabecalho_t *cabecalho);

/*cabecalhoTipo2_t *inicia_cab_tipo2();
void ler_cab_tipo2_arquivo(FILE *fp, cabecalhoTipo2_t *cabecalho);
void destroi_cabecalho2(cabecalhoTipo2_t *cabecalho);*/