/*
Trabalho 3 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dados.h"
#include "cabecalhos.h"
#include "indices.h"

//funcoes auxiliares gerais
void liberaDados(dados_t * dados);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
FILE* abre_CSV_leitura(char* nomeCSV);
FILE* abre_bin_escrita(char* nomeBin);
FILE* abre_bin_leitura(char *nomeBin);


//funcoes auxiliares T1
void imprimeDados(dados_t *dados, cabecalho_t *cabecalho);
char *read_line(FILE *stream, int *isEof);
char *my_str_tok(char *str, char *delims);
void copia_binario(FILE *CSV, FILE *BIN, char *nomeBinario, int tipoArquivo);
void readline(char* string);

//funcoes T1
void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario);
void funcionalidade2(int tipoArq, char* nomeBinario);
void funcionalidade3(int tipoArquivo, char *nomeBinario, int n);
void funcionalidade4(char *nomeBinario, int RRN);

//funcoes T2
void funcionalidade5(int tipoArquivo, char *nomeBinario, char *nomeIndice);
void funcionalidade6(int tipoArquivo, char *nomeDados, char *nomeIndice, int n);
void funcionalidade7(int tipoArquivo, char* nomeDados, char* nomeIndice, int n);
void funcionalidade8(int tipoArquivo, char* nomeDados, char* nomeIndice, int n);


//funcoes auxiliares T2
void printArray(regIndice_t *indices, int tamanho);
void Leitura(dados_t *dados);
int LeituraTipo2(dados_t *dados);
int busca_binaria_id(regIndice_t *indices, int posicaoInicial, int posicaoFinal, int chave);
int *busca(FILE *BIN, char **nomeCampos, char **valorCampos, int n, int tipoArquivo, int trabalho2, int funcionalidade);

void funcionalidade10(int tipoArquivo, char *nomeDados, char *nomeIndice, int valorID);
int buscaArvoreB(FILE *arquivo, int RRN, int chave, int *encontrado);
int ocorrenciaDaChave(dadosArvoreB_t *pagina, int chave, int *pos);



void posicao_arquivo_leitura(FILE *BIN, dados_t *dados, int RRN);
void posicao_arquivo_escrita(FILE *BIN, dados_t *dados, long long int posicao, int tipoArquivo);
void adicionaNovoIndex(FILE* arqIndice, dados_t* dados,regIndice_t *indices ,char* nomeIndice, long long int offSet, int RRN, int tipoArquivo );
void reduzNumeroRemovidos(FILE* fp, cabecalho_t *cabecalho, int aux);
void insereLixo(FILE *fp, int tamReg, int tam);