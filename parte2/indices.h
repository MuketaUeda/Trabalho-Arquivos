#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct regIndice regIndice_t;

//Unificamos as structs dos registros de dados e cabecalho dos indices do tipo 1 e do tipo 2 pelo fato de serem bem similares.
struct regIndice{
    char status;
    int id;
    int proxRRN;
    long long int proxOffset;
    int tamanho; //Vai armazenar o numero de bytes presente
};


regIndice_t *inicia_indice();

int ler_indices(regIndice_t *indice, FILE *fp, int tipo);
void destruir_indice(regIndice_t *indice);