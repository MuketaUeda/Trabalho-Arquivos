#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
FILE* abre_CSV_leitura(char* nomeCSV);
FILE* abre_bin_escrita(char* nomeBin);
void copia_binario1(FILE *CSV, FILE *BIN, char *nomeBinario);
// char *read_line(FILE *stream, int *isEof);
//char *my_str_tok(char *str, char *delims);
//static char *my_str_tok(char *str, char const *delims);
//char **split_string(char * str, char separator, int *n_elems);
char* read_line(FILE *stream, int *has_EOF);
void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario);