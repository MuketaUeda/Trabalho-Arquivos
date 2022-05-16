#include "dados.h"
#include "cabecalhos.h"

dadosTipo1_t *inicializa_dados_tipo1()
{

    dadosTipo1_t *dados = malloc(1 * sizeof(dadosTipo1_t));

    dados->id = -1;
    dados->ano = -1;
    dados->quantidade = -1;
    dados->sigla = (char *)malloc(3 * sizeof(char));
    dados->sigla[2] = '\0';
    dados->marca = NULL;
    dados->modelo = NULL;
    dados->cidade = NULL;
    dados->quantidade = -1;
    dados->prox = -1;
    dados->removido = '0';

    return dados;
}

dadosTipo2_t *inicializa_dados_tipo2()
{

    dadosTipo2_t *dados = malloc(1 * sizeof(dadosTipo2_t));

    dados->id = -1;
    dados->ano = -1;
    dados->quantidade = -1;
    dados->sigla = (char *)malloc(3 * sizeof(char));
    dados->sigla[2] = '\0';
    dados->marca = NULL;
    dados->modelo = NULL;
    dados->cidade = NULL;
    dados->quantidade = -1;
    dados->prox = -1;
    dados->removido = '0';

    return dados;
}

void destruir_dados_tipo1(dadosTipo1_t *dados)
{
    free(dados->marca);
    free(dados->modelo);
    free(dados->cidade);
    free(dados->sigla);

    free(dados);
    return;
}

void destruir_dados_tipo2(dadosTipo2_t *dados)
{
    free(dados->marca);
    free(dados->modelo);
    free(dados->cidade);
    free(dados->sigla);

    free(dados);
    return;
}

void escreve_dados_tipo1(dadosTipo1_t *dados, FILE *fp)
{
    cabecalhoTipo1_t *cabecalho = inicia_cab_tipo1();
    int tamanhoAtual = 0;

    fwrite(&dados->id, sizeof(int), 1, fp);
    tamanhoAtual += sizeof(int);

    fwrite(&dados->ano, sizeof(int), 1, fp);
    tamanhoAtual += sizeof(int);

    fwrite(&dados->quantidade, sizeof(int), 1, fp);
    tamanhoAtual += sizeof(int);

    if (strlen(dados->sigla) > 0)
    {
        fwrite(&dados->sigla, sizeof(char), 2, fp);
    }else
    {
        dados->sigla[0] = '$';
        dados->sigla[1] = '$';
        fwrite(dados->sigla, sizeof(char), 2, fp);
    }
    tamanhoAtual += 2 * sizeof(char);

    if (dados->tamanhoCidade > 0){
        //Primeiro, o tamanho do nome da cidade, depois o código (0), depois o nome da cidade em si
        fwrite(&dados->tamanhoCidade, sizeof(int), 1, fp);
        tamanhoAtual += sizeof(int);
        //Adicionando código da cidade = 0
        fwrite(&cabecalho->codNome, sizeof(char), 1, fp);
        tamanhoAtual += sizeof(char);
        fwrite(&dados->cidade, sizeof(char), dados->tamanhoCidade, fp);
        tamanhoAtual += dados->tamanhoCidade * sizeof(char);
    }
    if(dados->tamanhoMarca > 0){
        //Primeiro, o tamanho do nome da marca, depois o código (1), depois o nome da marca em si
        fwrite(&dados->tamanhoMarca, sizeof(int), 1, fp);
        tamanhoAtual += sizeof(int);
        fwrite(&cabecalho->codMarca, sizeof(char), 1, fp);
        tamanhoAtual += sizeof(char);
        fwrite(&dados->marca, sizeof(char), dados->tamanhoMarca, fp);
        tamanhoAtual += dados->tamanhoMarca * sizeof(char);
    }
    if(dados->tamanhoMarca > 0){
        //Primeiro, o tamanho do nome do modelo, depois o código (0), depois o nome do modelo em si
        fwrite(&dados->tamanhoModelo, sizeof(int), 1, fp);
        tamanhoAtual += sizeof(int);
        fwrite(&cabecalho->codModelo, sizeof(char), 1, fp);
        tamanhoAtual += sizeof(char);
        fwrite(&dados->modelo, sizeof(char), dados->tamanhoModelo, fp);
        tamanhoAtual += dados->tamanhoModelo * sizeof(char);
    }

    for (int i = 0; i < (97 - tamanhoAtual); i++)
    {
        char lixo = '$';
        fwrite(&lixo, sizeof(char), 1, fp);
    }

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