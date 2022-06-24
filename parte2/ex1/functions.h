/*
João Pedro Duarte Nunes
12541460
*/
#include<stdio.h>
#include<stdlib.h>
#include "commands.h"

void read_line(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void dollars(FILE *problemFile, int lenght);
void fileWrite(FILE *problemFile, names_t *ind);
char* readFile(FILE *problemFile, int lenght, char *string);
void output(names_t* ind);