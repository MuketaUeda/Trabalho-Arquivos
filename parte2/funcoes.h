/*
Trabalho 1 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dados.h"
#include "cabecalhos.h"
#include "indices.h"
//#include "pilha.h"

void readline(char* string);
void liberaDados(dados_t * dados);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
FILE* abre_CSV_leitura(char* nomeCSV);
FILE* abre_bin_escrita(char* nomeBin);
FILE* abre_bin_leitura(char *nomeBin);
void copia_binario(FILE *CSV, FILE *BIN, char *nomeBinario, int tipoArquivo);

void posicao_arquivo_leitura(FILE *BIN, dados_t *dados, int RRN);
void posicao_arquivo_escrita(FILE *BIN, dados_t *dados, long long int posicao, int tipoArquivo);

void imprimeDados(dados_t *dados, cabecalho_t *cabecalho);
char *read_line(FILE *stream, int *isEof);
char *my_str_tok(char *str, char *delims);
void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario);
void funcionalidade2(int tipoArq, char* nomeBinario);
void funcionalidade3(int tipoArquivo, char *nomeBinario, int n);
void funcionalidade4(char *nomeBinario, int RRN);

void funcionalidade5(int tipoArquivo, char *nomeBinario, char *nomeIndice);
regIndice_t *insertionSort(regIndice_t *indices, int tamanho);
void printArray(regIndice_t *indices, int tamanho);

void funcionalidade6(int tipoArquivo, char *nomeDados, char *nomeIndice, int n);

void funcionalidade7(int tipoArquivo, char* nomeDados, char* nomeIndice, int n);

void Leitura(dados_t *dados);

void funcionalidade8(int tipoArquivo, char* nomeDados, char* nomeIndice, int n);
int busca_binaria_id(regIndice_t *indices, int posicaoInicial, int posicaoFinal, int chave);

int *busca(FILE *BIN, char **nomeCampos, char **valorCampos, int n, int tipoArquivo, int trabalho2, int funcionalidade);