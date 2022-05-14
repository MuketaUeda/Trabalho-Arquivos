#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct regCabTipo1 cabecalhoTipo1_t;
typedef struct regCabTipo2 cabecalhoTipo2_t;

cabecalhoTipo1_t *criar_cab_tipo1();
void escreve_cabecalho1_arquivo(cabecalhoTipo1_t *cabecalho, FILE *fp);
void ler_cab_tipo1_arquivo(FILE *fp, cabecalhoTipo1_t *cabecalho);

cabecalhoTipo2_t *criar_cab_tipo2();
void ler_cab_tipo2_arquivo(FILE *fp, cabecalhoTipo2_t *cabecalho);
