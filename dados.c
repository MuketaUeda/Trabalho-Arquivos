#include "dados.h"


typedef struct regDados1{
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
    int prox;
};

typedef struct regDados2{
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
    long long int prox;
};

dadosTipo1_t *inicializa_dados_tipo1(){
    
    dadosTipo1_t *dados = malloc(1 * sizeof(dadosTipo1_t));

    dados->id = -1;
    dados->ano = -1;
    dados->quantidade = -1;
    dados->sigla = (dadosTipo1_t *)malloc(3 * sizeof(char));
    dados->sigla[2] = "\0";
    dados->marca = NULL;
    dados->modelo = NULL;
    dados->cidade = NULL;
    dados->quantidade = -1;
    dados->prox = -1;
    dados->removido = "0";
    
    return dados;
}

dadosTipo2_t *inicializa_dados_tipo2(){
    
    dadosTipo2_t *dados = malloc(1 * sizeof(dadosTipo2_t));

    dados->id = -1;
    dados->ano = -1;
    dados->quantidade = -1;
    dados->sigla = (dadosTipo2_t *)malloc(3 * sizeof(char));
    dados->sigla[2] = "\0";
    dados->marca = NULL;
    dados->modelo = NULL;
    dados->cidade = NULL;
    dados->quantidade = -1;
    dados->prox = -1;
    dados->removido = "0";
    
    return dados;
}

void destruir_dados_tipo1(dadosTipo1_t *dados){
    free(dados->marca);
    free(dados->modelo);
    free(dados->cidade);
    free(dados->sigla);


    free(dados);
    return;
}

void destruir_dados_tipo2(dadosTipo2_t *dados){
    free(dados->marca);
    free(dados->modelo);
    free(dados->cidade);
    free(dados->sigla);


    free(dados);
    return;
}

void escreve_dados_tipo1(dadosTipo1_t *dados, FILE *fp){

    fwrite(&dados->id, sizeof(int), 1, fp);
    fwrite(&dados->ano, sizeof(int), 1, fp);
    fwrite(&dados->quantidade,sizeof(int), 1, fp);
    fwrite(&dados->sigla, sizeof(char), 2, fp);
    fwrite(&dados->cidade, sizeof(char), dados->tamanhoCidade, fp);
    fwrite(&dados->marca, sizeof(char), dados->tamanhoMarca, fp);
    fwrite(&dados->modelo, sizeof(char), dados->tamanhoModelo, fp);
    fwrite(&dados->removido, sizeof(char), 1, fp);
    fwrite(&dados->prox, sizeof(int), 1, fp);
    
    return;
}
/*
//Ler dados do arquivo
void ler_dados_tipo1(FILE *fp, dadosTipo1_t *dados){

	fread(&dados->id, sizeof(char), 1, fp);
    fread(&dados->ano, sizeof(int), 1, fp);
    fread(&dados->quantidade, sizeof(int), 1, fp);
	fread(&dados->sigla, sizeof(char), 2, fp);
    fread(&dados->tamanhoCidade, sizeof(int), 1, fp);
    dados->cidade = malloc(sizeof(char)*dados->tamanhoCidade+1);
    fread(&dados->cidade, sizeof(char), dados->tamanhoCidade, fp);
    fread(&dados->tamanhoMarca, sizeof(int), 1, fp);
    dados->marca = malloc(sizeof(char)*dados->tamanhoMarca+1);
    fread(&dados->marca, sizeof(char), dados->tamanhoMarca, fp);
    fread(&dados->tamanhoModelo, sizeof(int), 1, fp);
    dados->modelo = malloc(sizeof(char)*dados->tamanhoModelo+1);
    fread(&dados->modelo, sizeof(char), dados->tamanhoModelo, fp);
    
	return;
}
int ler_dados_tipo2(FILE *fp, dadosTipo2_t *dados){
    int tamanhoTotal = 0;
    int tamanhoRegistro = 0;


    fread(&dados->removido, sizeof(char), 1, fp);
    fread(&tamanhoTotal, sizeof(int), 1, fp);
    fread(&dados->prox, sizeof(long long int), 1, fp);
    fread(&dados->id, sizeof(int), 1 , fp);
    fread(&dados->ano, sizeof(int), 1, fp);
    fread(&dados->quantidade, sizeof(int), 1, fp);
    fread(dados->sigla, sizeof(char), 2, fp);
    
    tamanhoRegistro += 27;  //Somando os bytes dos campos de tamanho fixo

    //Agora, vamos aos campos de tamanho variável:
    





    return final;
}
*/