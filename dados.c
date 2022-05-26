#include "dados.h"
#include "cabecalhos.h"
#include <string.h>

dados_t *inicializa_dados()
{
    // Inicializando todas as variáveis, sejam de dados tipo 1 ou tipo 2
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

// Escrita dos dados
int escreve_dados(dados_t *dados, FILE *fp, int tipoArquivo)
{
    // vamos aproveitar as variáveis dos códigos da cidade, marca e modelo, do cabeçalho
    cabecalho_t *cabecalho = inicia_cabecalho();
    /*
    Aqui, como temos que escrever o tamanho do registro no arquivo antes de escrever outros elementos, vamos fazer a contagem antes:
    */
    dados->tamanhoAtual = 0;
    if (tipoArquivo == 2) dados->tamanhoAtual += 22;
    if (tipoArquivo == 1) dados->tamanhoAtual += 19;

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
    if (tipoArquivo == 1)
        fwrite(&dados->proxRRN, sizeof(int), 1, fp);
    if (tipoArquivo == 2)
    {
        fwrite(&dados->tamanhoAtual, sizeof(int), 1, fp);
        fwrite(&dados->proxOffset, sizeof(long long int), 1, fp);
    }

    fwrite(&dados->id, sizeof(int), 1, fp);

    fwrite(&dados->ano, sizeof(int), 1, fp);

    fwrite(&dados->quantidade, sizeof(int), 1, fp);

    if (strlen(dados->sigla) > 0) fwrite(dados->sigla, sizeof(char), 2, fp);
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

// Ler dados do arquivo
void ler_dados_tipo1(FILE *fp, dados_t *dados)
{
    int tamanhoRegistro = 0;

    // Primeiramente, leremos os 19 bytes dos campos de tamanho fixo:
    fread(&dados->removido, sizeof(char), 1, fp);
    tamanhoRegistro += sizeof(char);
    fread(&dados->proxRRN, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    fread(&dados->id, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    fread(&dados->ano, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    fread(&dados->quantidade, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    fread(dados->sigla, sizeof(char), 2, fp);
    tamanhoRegistro += 2 * sizeof(char);

    // Agora, de tamanho variável:
    int proximoValido = 1;
    int infosLidas = 0;
    char *elemento = NULL;

    while (tamanhoRegistro + 5 < 97 && infosLidas < 3 && proximoValido == 1)
    {
        int tamanhoElemento = 0;
        char codigoElemento = '\0';
        fread(&tamanhoElemento, sizeof(int), 1, fp);
        tamanhoRegistro += sizeof(int);
        fread(&codigoElemento, sizeof(char), 1, fp);
        tamanhoRegistro += sizeof(char);

        infosLidas++;
        elemento = (char *)malloc(tamanhoElemento + 1 * sizeof(char)); // alocando o elemento 'coringa' isso e pode ser cidade, marca ou modelo
        fread(elemento, sizeof(char), tamanhoElemento, fp);
        elemento[tamanhoElemento] = '\0';
        tamanhoRegistro += tamanhoElemento;

        if (codigoElemento == '0') // verifica o codigo lido
        {
            // se o tamanho do elemento for maior que zero, significa que existe informacao para aquele codigo e assim e passado para o campo correto
            if (tamanhoElemento > 0)
            {
                dados->tamanhoCidade = tamanhoElemento;
                dados->cidade = (char *)malloc(dados->tamanhoCidade + 1 * sizeof(char));
                dados->cidade = elemento;
                dados->cidade[tamanhoElemento] = '\0';
            }
        }
        else if (codigoElemento == '1')
        {
            if (tamanhoElemento > 0)
            {
                dados->tamanhoMarca = tamanhoElemento;
                dados->marca = (char *)malloc(dados->tamanhoMarca + 1 * sizeof(char));
                dados->marca = elemento;
                dados->marca[tamanhoElemento] = '\0';
            }
        }
        else if (codigoElemento == '2')
        {
            if (tamanhoElemento > 0)
            {
                dados->tamanhoModelo = tamanhoElemento;
                dados->modelo = (char *)malloc(dados->tamanhoModelo + 1 * sizeof(char));
                dados->modelo = elemento;
                dados->modelo[tamanhoElemento] = '\0';
            }
        }
        else proximoValido = 0;
    }
    fseek(fp, (97 - tamanhoRegistro), SEEK_CUR); // anda pelo arquivo para a posicao correta
    return;
}

int ler_dados_tipo2(FILE *fp, dados_t *dados)
{
    int tamanhoRegistro = 0;
    int tamanhoTotal = 0;

    // Primeiramente, leremos os 27 bytes dos campos de tamanho fixo:
    fread(&dados->removido, sizeof(char), 1, fp);
    tamanhoRegistro += sizeof(char);
    fread(&tamanhoTotal, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    fread(&dados->proxOffset, sizeof(long long int), 1, fp);
    tamanhoRegistro += sizeof(long long int);

    fread(&dados->id, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    fread(&dados->ano, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    fread(&dados->quantidade, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    fread(dados->sigla, sizeof(char), 2, fp);
    tamanhoRegistro += 2 * sizeof(char);

    tamanhoTotal += 5;
    // Agora, de tamanho variável:
    int proximoValido = 1;
    int infosLidas = 0;

    while (tamanhoRegistro + 5 < tamanhoTotal && infosLidas < 3 && proximoValido == 1)
    {
        int tamanhoElemento = 0;
        char codigoElemento = '\0';
        fread(&tamanhoElemento, sizeof(int), 1, fp);
        tamanhoRegistro += sizeof(int);
        fread(&codigoElemento, sizeof(char), 1, fp);
        tamanhoRegistro += sizeof(char);

        infosLidas++;
        char *elemento = (char *)malloc(tamanhoElemento + 1 * sizeof(char)); // alocando o elemento 'coringa' isso e pode ser cidade, marca ou modelo
        elemento[tamanhoElemento] = '\0';
        fread(elemento, sizeof(char), tamanhoElemento, fp);
        tamanhoRegistro += tamanhoElemento;
        if (codigoElemento == '0')
        {
            // se o tamanho do elemento for maior que zero, significa que existe informacao para aquele codigo e assim e passado para o campo correto
            if (tamanhoElemento > 0)
            {
                dados->tamanhoCidade = tamanhoElemento;
                dados->cidade = (char *)malloc(dados->tamanhoCidade + 1 * sizeof(char));
                dados->cidade = elemento;
                dados->cidade[tamanhoElemento] = '\0';
            }
        }
        else if (codigoElemento == '1')
        {
            if (tamanhoElemento > 0)
            {
                dados->tamanhoMarca = tamanhoElemento;
                dados->marca = (char *)malloc(dados->tamanhoMarca + 1 * sizeof(char));
                dados->marca = elemento;
                dados->marca[tamanhoElemento] = '\0';
            }
        }
        else if (codigoElemento == '2')
        {
            if (tamanhoElemento > 0)
            {
                dados->tamanhoModelo = tamanhoElemento;
                dados->modelo = (char *)malloc(dados->tamanhoModelo + 1 * sizeof(char));
                dados->modelo = elemento;
                dados->modelo[tamanhoElemento] = '\0';
            }
        }
        else proximoValido = 0;
    }

    fseek(fp, (tamanhoTotal - tamanhoRegistro), SEEK_CUR); // anda pelo arquivo para a posicao correta
    return tamanhoTotal;
}