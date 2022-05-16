#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct regDados1 dadosTipo1_t;

struct regDados1{
    int id;
    int ano;
    int quantidade;
    char *sigla; //2 bytes
    char *cidade;
    char *marca;
    char *modelo;
    int tamanhoModelo;
    int tamanhoMarca;
    int tamanhoCidade;
    char removido;
    int prox;
};

dadosTipo1_t *inicializa_dados_tipo1();
void destruir_dados_tipo1(dadosTipo1_t *dados);
void escreve_dados_tipo1(dadosTipo1_t *dados, FILE *fp);
int ler_dados_tipo1(FILE *fp, dadosTipo1_t *dados);

typedef struct regDados2 dadosTipo2_t;
dadosTipo2_t *inicializa_dados_tipo2();
void destruir_dados_tipo2(dadosTipo2_t *dados);
int ler_dados_tipo2(FILE *fp, dadosTipo1_t *dados);

struct regDados2{
    int id;
    int ano;
    int quantidade;
    char *sigla; //2 bytes
    char *cidade;
    char *marca;
    char *modelo;
    int tamanhoModelo;
    int tamanhoMarca;
    int tamanhoCidade;
    char removido;
    long long int prox;
};