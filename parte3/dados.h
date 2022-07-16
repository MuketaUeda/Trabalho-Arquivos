

/*
Trabalho 3 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4

typedef struct regDados dados_t;
typedef struct regDadosArvoreB dadosArvoreB_t;

// Unificamos as structs dos registros de dados do tipo 1 e do tipo 2 pelo fato de serem bem similares.
struct regDados
{
    int id;
    int ano;
    int quantidade;
    char *sigla; // 2 bytes
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


//acredito que esteja certo fiquei com duvidas perguntar pro monitor
struct regDadosArvoreB
{
    char tipoNo;
    int nroChaves;
    int ponteiro[MAX];
    int chave[MAX-1];
    int RRNdoNo[MAX-1];
};

dados_t *inicializa_dados();
dadosArvoreB_t *inicializa_dados_arvoreB();

int escreve_dados(dados_t *dados, FILE *fp, int tipoArquivo, int tamanhoFunc7);
void ler_dados_tipo1(FILE *fp, dados_t *dados);
int ler_dados_tipo2(FILE *fp, dados_t *dados);
void atualiza_dados_tipo1(FILE *BIN, char **nomeCamposBusca, char **valorCamposBusca, int n, int idAtualiza);

void lerArvoreB(FILE *arquivo, dadosArvoreB_t *dados);
void liberaDados(dados_t *dados);