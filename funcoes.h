#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
FILE* abre_CSV_leitura(char* nomeCSV);
FILE* abre_bin_escrita(char* nomeBin);
FILE* abre_bin_leitura(char *nomeBin);
void copia_binario(FILE *CSV, FILE *BIN, char *nomeBinario, int tipoArquivo);
void imprimeDados(dados_t *dados, cabecalho_t *cabecalho);
char *read_line(FILE *stream, int *isEof);
char *my_str_tok(char *str, char *delims);
void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario);
void funcionalidade2(int tipoArq, char* nomeBinario);