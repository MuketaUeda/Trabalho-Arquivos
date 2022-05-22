#include "dados.h"
#include "cabecalhos.h"

dados_t *inicializa_dados()
{
    //Inicializando todas as variáveis, sejam de dados tipo 1 ou tipo 2
    dados_t *dados = malloc(1 * sizeof(dados_t));

    dados->id = -1;
    dados->ano = -1;
    dados->quantidade = -1;
    dados->sigla = (char *)malloc(3 * sizeof(char));
    dados->sigla[2] = '\0';
    dados->tamanhoCidade = 0;
    dados->tamanhoModelo = 0;
    dados->tamanhoMarca = 0;
    dados->marca = NULL;
    dados->modelo = NULL;
    dados->cidade = NULL;
    dados->proxRRN = -1;
    dados->removido = '0';
    dados->proxOffset = -1;
    dados->tamanhoAtual = 0;
    return dados;
}

void destruir_dados_tipo1(dados_t *dados)
{
    free(dados->marca);
    free(dados->modelo);
    free(dados->cidade);
    free(dados->sigla);

    free(dados);
    return;
}

//Função de escrita para os dados do tipo 1. Apesar da relativa semelhança com a função de escrita dos dados tipo 2, preferimos separar
//as funções para fins de organização.
/*
void escreve_dados_tipo1(dados_t *dados, FILE *fp)
{
    //vamos aproveitar as variáveis dos códigos da cidade, marca e modelo, do cabeçalho
    cabecalho_t *cabecalho = inicia_cabecalho();
    dados->tamanhoAtual = 0;

    fwrite(&dados->removido, sizeof(char), 1, fp);
    dados->tamanhoAtual += sizeof(char);

    fwrite(&dados->proxRRN, sizeof(int), 1, fp);
    dados->tamanhoAtual += sizeof(int);

    fwrite(&dados->id, sizeof(int), 1, fp);
    dados->tamanhoAtual += sizeof(int);

    fwrite(&dados->ano, sizeof(int), 1, fp);
    dados->tamanhoAtual += sizeof(int);

    fwrite(&dados->quantidade, sizeof(int), 1, fp);
    dados->tamanhoAtual += sizeof(int);

    if (strlen(dados->sigla) > 0)
    {
        fwrite(dados->sigla, sizeof(char), 2, fp);
    }
    else
    {
        char lixo[3] = "$$";
        fwrite(lixo, sizeof(char), 2, fp);
    }
    dados->tamanhoAtual += 2 * sizeof(char);

    if(dados->cidade != NULL && strcmp(dados->cidade, "\0") != 0)
        dados->tamanhoCidade = strlen(dados->cidade);
    if (dados->tamanhoCidade > 0)
    {
        // Primeiro, o tamanho do nome da cidade, depois o código (0), depois o nome da cidade em si
        fwrite(&dados->tamanhoCidade, sizeof(int), 1, fp);
        dados->tamanhoAtual += sizeof(int);
        // Adicionando código da cidade = 0
        //char codCidade = '0';
        fwrite(&cabecalho->codNome, sizeof(char), 1, fp);
        dados->tamanhoAtual += sizeof(char);
        fwrite(dados->cidade, sizeof(char), dados->tamanhoCidade, fp);
        dados->tamanhoAtual += dados->tamanhoCidade;
    }

    if(dados->marca != NULL && strcmp(dados->marca, "\0") != 0)
        dados->tamanhoMarca = strlen(dados->marca);
    if (dados->tamanhoMarca > 0)
    {
        // Primeiro, o tamanho do nome da marca, depois o código (1), depois o nome da marca em si
        fwrite(&dados->tamanhoMarca, sizeof(int), 1, fp);
        dados->tamanhoAtual += sizeof(int);
        //char codMarca = '1';
        fwrite(&cabecalho->codMarca, sizeof(char), 1, fp);
        dados->tamanhoAtual += sizeof(char);
        fwrite(dados->marca, sizeof(char), dados->tamanhoMarca, fp);
        dados->tamanhoAtual += dados->tamanhoMarca;
        //printf("entrei %d\n\n", i);
    }
    if(dados->modelo != NULL&& strcmp(dados->modelo, "\0") != 0)
        dados->tamanhoModelo = strlen(dados->modelo);
    if (dados->tamanhoModelo > 0)
    {
        // Primeiro, o tamanho do nome do modelo, depois o código (0), depois o nome do modelo em si
        fwrite(&dados->tamanhoModelo, sizeof(int), 1, fp);
        dados->tamanhoAtual += sizeof(int);
        //char codModelo = '2';
        fwrite(&cabecalho->codModelo, sizeof(char), 1, fp);
        dados->tamanhoAtual += sizeof(char);
        fwrite(dados->modelo, sizeof(char), dados->tamanhoModelo, fp);
        // printf("tamanho modelo: %d\n", dados->tamanhoModelo);
        dados->tamanhoModelo = strlen(dados->modelo);
        dados->tamanhoAtual += dados->tamanhoModelo;
    }

    char *lixo = (char *)malloc(97 - dados->tamanhoAtual);
    for (int i = 0; i < (97 - dados->tamanhoAtual); i++)
    {
        lixo[i] = '$';
    }
    fwrite(lixo, sizeof(char), 97 - dados->tamanhoAtual, fp);
    free(lixo);
    return;
}
*/
//Escrita dos dados do tipo 2
/*
int escreve_dados_tipo2(dados_t *dados, FILE *fp)
{
    //vamos aproveitar as variáveis dos códigos da cidade, marca e modelo, do cabeçalho
    cabecalho_t *cabecalho = inicia_cabecalho();
    
    //Aqui, como temos que escrever o tamanho do registro no arquivo antes de escrever outros elementos, vamos fazer a contagem antes:
    
    dados->tamanhoAtual = 0;
    dados->tamanhoAtual += 22;

    if(dados->cidade != NULL && strcmp(dados->cidade, "\0") != 0)
        dados->tamanhoCidade = strlen(dados->cidade);
    if (dados->tamanhoCidade > 0)
    {
        // Primeiro, o tamanho do nome da cidade, depois o código (0), depois o nome da cidade em si
        dados->tamanhoAtual += sizeof(int);
        dados->tamanhoAtual += sizeof(char);
        dados->tamanhoAtual += dados->tamanhoCidade * sizeof(char);
    }

    if(dados->marca != NULL && strcmp(dados->marca, "\0") != 0)
        dados->tamanhoMarca = strlen(dados->marca);
    if (dados->tamanhoMarca > 0)
    {
        // Primeiro, o tamanho do nome da marca, depois o código (1), depois o nome da marca em si
        dados->tamanhoAtual += sizeof(int);
        dados->tamanhoAtual += sizeof(char);
        dados->tamanhoAtual += dados->tamanhoMarca * sizeof(char);
    }
    if(dados->modelo != NULL&& strcmp(dados->modelo, "\0") != 0)
        dados->tamanhoModelo = strlen(dados->modelo);
    if (dados->tamanhoModelo > 0)
    {
        // Primeiro, o tamanho do nome do modelo, depois o código (2), depois o nome do modelo em si
        dados->tamanhoAtual += sizeof(int);
        dados->tamanhoAtual += sizeof(char);
        dados->tamanhoAtual += dados->tamanhoModelo * sizeof(char);
    }

    fwrite(&dados->removido, sizeof(char), 1, fp);

    //Agora, vamos escrever o tamanho do registro
    fwrite(&dados->tamanhoAtual, sizeof(int), 1, fp);

    fwrite(&dados->proxOffset, sizeof(long long int), 1, fp);

    fwrite(&dados->id, sizeof(int), 1, fp);

    fwrite(&dados->ano, sizeof(int), 1, fp);

    fwrite(&dados->quantidade, sizeof(int), 1, fp);

    if (strlen(dados->sigla) > 0)
    {
        fwrite(dados->sigla, sizeof(char), 2, fp);
    }
    else
    {
        dados->sigla[0] = '$';
        dados->sigla[1] = '$';
        fwrite(dados->sigla, sizeof(char), 2, fp);
    }
    if (dados->tamanhoCidade > 0)
    {
        // Primeiro, o tamanho do nome da cidade, depois o código (0), depois o nome da cidade
        fwrite(&dados->tamanhoCidade, sizeof(int), 1, fp);
        // Adicionando código da cidade = 0
        char codCidade = '0';
        fwrite(&codCidade, sizeof(char), 1, fp);
        fwrite(dados->cidade, sizeof(char), dados->tamanhoCidade, fp);
    }
    if (dados->tamanhoMarca > 0)
    {
        // Primeiro, o tamanho do nome da marca, depois o código (1), depois o nome da marca
        fwrite(&dados->tamanhoMarca, sizeof(int), 1, fp);
        char codMarca = '1';
        fwrite(&codMarca, sizeof(char), 1, fp);
        fwrite(dados->marca, sizeof(char), dados->tamanhoMarca, fp);
        //printf("entrei %d\n\n", i);
    }
    if (dados->tamanhoModelo > 0)
    {
        // Primeiro, o tamanho do nome do modelo, depois o código (0), depois o nome do modelo
        fwrite(&dados->tamanhoModelo, sizeof(int), 1, fp);
        char codModelo = '2';
        fwrite(&codModelo, sizeof(char), 1, fp);
        fwrite(dados->modelo, sizeof(char), dados->tamanhoModelo, fp);
        // printf("tamanho modelo: %d\n", dados->tamanhoModelo);
        dados->tamanhoModelo = strlen(dados->modelo);
    }

    //Dessa vez, como nosso registro é de tamanho variável, não vamos preencher com lixo
    //adicionando 5 bytes: 1 referente ao "removido" (char) e os outros referente ao dados->tamanhoAtual (int);
    dados->tamanhoAtual += 5;
    return dados->tamanhoAtual;
}
*/
// Escrita dos dados do tipo 2
int escreve_dados(dados_t *dados, FILE *fp, int tipoArquivo)
{
    // vamos aproveitar as variáveis dos códigos da cidade, marca e modelo, do cabeçalho
    cabecalho_t *cabecalho = inicia_cabecalho();
    /*
    Aqui, como temos que escrever o tamanho do registro no arquivo antes de escrever outros elementos, vamos fazer a contagem antes:
    */
    dados->tamanhoAtual = 0;
    if (tipoArquivo == 2)
        dados->tamanhoAtual += 22;
    if (tipoArquivo == 1)
        dados->tamanhoAtual += 19;

    if (dados->cidade != NULL && strcmp(dados->cidade, "\0") != 0)
        dados->tamanhoCidade = strlen(dados->cidade);
    if (dados->tamanhoCidade > 0)
    {
        // Primeiro, o tamanho do nome da cidade, depois o código (0), depois o nome da cidade em si
        dados->tamanhoAtual += sizeof(int);
        dados->tamanhoAtual += sizeof(char);
        dados->tamanhoAtual += dados->tamanhoCidade * sizeof(char);
    }

    if (dados->marca != NULL && strcmp(dados->marca, "\0") != 0)
        dados->tamanhoMarca = strlen(dados->marca);
    if (dados->tamanhoMarca > 0)
    {
        // Primeiro, o tamanho do nome da marca, depois o código (1), depois o nome da marca em si
        dados->tamanhoAtual += sizeof(int);
        dados->tamanhoAtual += sizeof(char);
        dados->tamanhoAtual += dados->tamanhoMarca * sizeof(char);
    }
    if (dados->modelo != NULL && strcmp(dados->modelo, "\0") != 0)
        dados->tamanhoModelo = strlen(dados->modelo);
    if (dados->tamanhoModelo > 0)
    {
        // Primeiro, o tamanho do nome do modelo, depois o código (2), depois o nome do modelo em si
        dados->tamanhoAtual += sizeof(int);
        dados->tamanhoAtual += sizeof(char);
        dados->tamanhoAtual += dados->tamanhoModelo * sizeof(char);
    }

    fwrite(&dados->removido, sizeof(char), 1, fp);

    // Agora, vamos escrever o tamanho do registro
    if(tipoArquivo == 1)
        fwrite(&dados->proxRRN, sizeof(int), 1, fp);
    if (tipoArquivo == 2)
    {
        fwrite(&dados->tamanhoAtual, sizeof(int), 1, fp);
        fwrite(&dados->proxOffset, sizeof(long long int), 1, fp);
    }

    fwrite(&dados->id, sizeof(int), 1, fp);

    fwrite(&dados->ano, sizeof(int), 1, fp);

    fwrite(&dados->quantidade, sizeof(int), 1, fp);

    if (strlen(dados->sigla) > 0)
    {
        fwrite(dados->sigla, sizeof(char), 2, fp);
    }
    else
    {
        dados->sigla[0] = '$';
        dados->sigla[1] = '$';
        fwrite(dados->sigla, sizeof(char), 2, fp);
    }
    if (dados->tamanhoCidade > 0)
    {
        // Primeiro, o tamanho do nome da cidade, depois o código (0), depois o nome da cidade
        fwrite(&dados->tamanhoCidade, sizeof(int), 1, fp);
        // Adicionando código da cidade = 0
        char codCidade = '0';
        fwrite(&codCidade, sizeof(char), 1, fp);
        fwrite(dados->cidade, sizeof(char), dados->tamanhoCidade, fp);
    }
    if (dados->tamanhoMarca > 0)
    {
        // Primeiro, o tamanho do nome da marca, depois o código (1), depois o nome da marca
        fwrite(&dados->tamanhoMarca, sizeof(int), 1, fp);
        char codMarca = '1';
        fwrite(&codMarca, sizeof(char), 1, fp);
        fwrite(dados->marca, sizeof(char), dados->tamanhoMarca, fp);
        // printf("entrei %d\n\n", i);
    }
    if (dados->tamanhoModelo > 0)
    {
        // Primeiro, o tamanho do nome do modelo, depois o código (0), depois o nome do modelo
        fwrite(&dados->tamanhoModelo, sizeof(int), 1, fp);
        char codModelo = '2';
        fwrite(&codModelo, sizeof(char), 1, fp);
        fwrite(dados->modelo, sizeof(char), dados->tamanhoModelo, fp);
        // printf("tamanho modelo: %d\n", dados->tamanhoModelo);
        dados->tamanhoModelo = strlen(dados->modelo);
    }

    if (tipoArquivo == 1)
    {
        char *lixo = (char *)malloc(97 - dados->tamanhoAtual);
        for (int i = 0; i < (97 - dados->tamanhoAtual); i++)
        {
            lixo[i] = '$';
        }
        fwrite(lixo, sizeof(char), 97 - dados->tamanhoAtual, fp);
        free(lixo);
        return 0;
    }
    else if (tipoArquivo == 2)
    {
        // Dessa vez, como nosso registro é de tamanho variável, não vamos preencher com lixo
        // adicionando 5 bytes: 1 referente ao "removido" (char) e os outros referente ao dados->tamanhoAtual (int);
        dados->tamanhoAtual += 5;
        return dados->tamanhoAtual;
    }
    return 0;
}


/*
//Ler dados do arquivo
void ler_dados_tipo1(FILE *fp, dados_t *dados){

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
    fread(&dados->proxRRN, sizeof(long long int), 1, fp);
    fread(&dados->id, sizeof(int), 1 , fp);
    fread(&dados->ano, sizeof(int), 1, fp);
    fread(&dados->quantidade, sizeof(int), 1, fp);
    fread(dados->sigla, sizeof(char), 2, fp);

    tamanhoRegistro += 27;  //Somando os bytes dos campos de tamanho fixo

    //Agora, vamos aos campos de tamanho variável:






    return final;
}

*/