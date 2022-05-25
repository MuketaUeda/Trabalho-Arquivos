#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct regDados dados_t;


//Unificamos as structs dos registros de dados do tipo 1 e do tipo 2 pelo fato de serem bem similares.
struct regDados{
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
    /*A única diferença entre os dados do tipo 1 é que, no tipo 2, temos um long long int proxOffstet;*/
    int tamanhoAtual;
    int proxRRN;
    long long int proxOffset;
};

dados_t *inicializa_dados();
void destruir_dados_tipo1(dados_t *dados);
int escreve_dados(dados_t *dados, FILE *fp, int tipoArquivo);
void ler_dados_tipo1(FILE *fp, dados_t *dados);
//int ler_dados_tipo2(FILE* fp, dados_t *dados, long long int aux);
int ler_dados_tipo2(FILE *fp, dados_t *dados);