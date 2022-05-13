#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct regCabecalho{
    char status;
    int topo;
    char desc[40];
    char desCodigo[22];
    char desAno[19];
    char desQuantidade[24];
    char desEstado[8];
    char codNome = '0';//"0"
    char desNome[16];
    char codMarca = '1'; //"1"
    char desMarca[18];
    char codModelo = '2'; //"2"
    char desModelo[19];
    int proxRRN; //inicia com zero
    int nroRegRemovidos; //inicia com zero
}cabecalhoVeiculo;


typedef struct regDados{
    int id;
    int ano;
    int quantidade;
    char sigla[2];
    char *cidade;
    char *marca;
    char *modelo;
    int tamanhoModelo;
    int tamanhoMarca;
    int tamanhoCidade;
    char removido;
    int prox;
}dadosVeiculso



