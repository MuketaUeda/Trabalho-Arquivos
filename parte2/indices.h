#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct regIndice regIndice_t;
typedef struct pilhaIndices pilhaIndices_t;
typedef struct listaIndices listaIndices_t;



//Unificamos as structs dos registros de dados e cabecalho dos indices do tipo 1 e do tipo 2 pelo fato de serem bem similares.
struct regIndice{
    int id;
    int proxRRN;
    long long int offSet;
    int tamanho; //Vai armazenar o numero de bytes presente
};

struct pilhaIndices{
    int id;
    int RRN;
    long long int offSet;
    
};


regIndice_t *inicia_indice();

char ler_indices_tipo1(regIndice_t *indice, FILE *fp);
void escreve_indice(regIndice_t *indice, FILE *fp, int tipo);
void destruir_indice(regIndice_t *indice);
void LeIndices(regIndice_t *indice, FILE *fp, int tipo);