#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
FILE* abre_CSV_leitura(char* nomeCSV);
FILE* abre_bin_escrita(char* nomeBin);
void copia_binario1(FILE *CSV, FILE *BIN);
char *read_line(FILE *stream, int *isEof);
char *my_str_tok(char *string, char *sep);
//char* read_line(FILE *stream, int *has_EOF);
void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario);