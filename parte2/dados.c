/*
Trabalho 1 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/

#include "funcoes.h"
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

// Escrita dos dados. Função unificada para arquivos do tipo 1 e do tipo 2
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
    // printf("remov %c\n", dados->removido);

    // Agora, vamos escrever o tamanho do registro
    if (tipoArquivo == 1)
        fwrite(&dados->proxRRN, sizeof(int), 1, fp);
    // printf("prx: %d\n\n", dados->proxRRN);
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
        fwrite(&cabecalho->codNomeCidade, sizeof(char), 1, fp);
        fwrite(dados->cidade, sizeof(char), dados->tamanhoCidade, fp);
    }
    if (dados->tamanhoMarca > 0)
    {
        // Primeiro, o tamanho do nome da marca, depois o código (1), depois o nome da marca
        fwrite(&dados->tamanhoMarca, sizeof(int), 1, fp);
        fwrite(&cabecalho->codMarca, sizeof(char), 1, fp);
        fwrite(dados->marca, sizeof(char), dados->tamanhoMarca, fp);
    }
    if (dados->tamanhoModelo > 0)
    {
        // Primeiro, o tamanho do nome do modelo, depois o código (0), depois o nome do modelo
        fwrite(&dados->tamanhoModelo, sizeof(int), 1, fp);
        fwrite(&cabecalho->codModelo, sizeof(char), 1, fp);
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
    free(cabecalho);
    return 0;
}

// Ler dados do arquivo. Aqui, decidimos não unificar as funções do tipo 1 e do tipo 2
// para não ficar confuso.
void ler_dados_tipo1(FILE *fp, dados_t *dados)
{
    int tamanhoRegistro = 0;

    // Primeiramente, leremos os 19 bytes dos campos de tamanho fixo:
    fread(&dados->removido, sizeof(char), 1, fp);
    tamanhoRegistro += sizeof(char);
    fread(&dados->proxRRN, sizeof(int), 1, fp);
    tamanhoRegistro += sizeof(int);
    // printf("rrn: %d\n", dados->proxRRN);
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

    /*
    Lemos enquanto tivermos lido menos de 3 informações (cidade, marca, modelo)
    ou enquanto o próximo elemento ainda for válido (código correspondente)
    ou enquanto ainda nos restarem ao menos 5 bytes (int + char) para lermos.
     */

    while (tamanhoRegistro + 5 < 97 && infosLidas < 3 && proximoValido == 1)
    {
        int tamanhoElemento = 0;
        char codigoElemento = '\0';
        fread(&tamanhoElemento, sizeof(int), 1, fp);
        tamanhoRegistro += sizeof(int);
        fread(&codigoElemento, sizeof(char), 1, fp);
        tamanhoRegistro += sizeof(char);

        // verificando se o codigoElemento é valido
        if (codigoElemento != '0')
        {
            if (codigoElemento != '1')
            {
                if (codigoElemento != '2')
                {
                    proximoValido = 0;
                    continue;
                }
            }
        }

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
        else
        {
            proximoValido = 0;
        }
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
    // printf("Tamanho total: %d\n", tamanhoTotal);
    fread(&dados->proxOffset, sizeof(long long int), 1, fp);
    tamanhoRegistro += sizeof(long long int);
    // printf("offset: %lld\n\n", dados->proxOffset);
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

    /*
    Lemos enquanto tivermos lido menos de 3 informações (cidade, marca, modelo)
    ou enquanto o próximo elemento ainda for válido (código correspondente)
    ou enquanto ainda nos restarem ao menos 5 bytes (int + char) para lermos.
     */
    while (infosLidas < 3 && tamanhoRegistro + 5 < tamanhoTotal && proximoValido == 1)
    {
        int tamanhoElemento = 0;
        char codigoElemento = '\0';
        fread(&tamanhoElemento, sizeof(int), 1, fp);
        tamanhoRegistro += sizeof(int);
        fread(&codigoElemento, sizeof(char), 1, fp);
        tamanhoRegistro += sizeof(char);

        // verificando se o codigoElemento é valido
        if (codigoElemento != '0')
        {
            if (codigoElemento != '1')
            {
                if (codigoElemento != '2')
                {
                    proximoValido = 0;
                    continue;
                }
            }
        }

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
    }

    fseek(fp, (tamanhoTotal - tamanhoRegistro), SEEK_CUR); // anda pelo arquivo para a posicao correta
    return tamanhoTotal;
}

void atualiza_dados_tipo1(FILE *BIN, char **nomeCamposAtualiza, char **valorCamposAtualiza, int n, int idAtualiza)
{
    int wtf = 0;

    // Vamos primeiro percorrer o primeiro cabeçalho. Só para chegarmos nos dados e pegarmos alguns valores
    // fseek(BIN, 0, SEEK_SET);
    cabecalho_t *cabecalho = inicia_cabecalho();
    ler_cab_arquivo(BIN, cabecalho, 1);

    dados_t *dados = inicializa_dados();

    long long int count = 0;
    int registroEncontrado = 0;
    long long int prox = 0;

    // Verificação do tipo do arquivo
    // if (tipoArquivo == 1)
    prox = cabecalho->proxRRN;
    // else if (tipoArquivo == 2)
    //   prox = cabecalho->proxByteOffset;

    int tamanhoTotal = 0;
    long long int posicao = -1;
    int c = 0;

    while (dados->id != idAtualiza)
    {
        dados = inicializa_dados();
        posicao = ftell(BIN);
        ler_dados_tipo1(BIN, dados);
    }
    //printf("ID: %d\n", );
    //imprimeDados(dados, cabecalho);

    // printf("nome: %s valor: %s\n", dados->marca,dados->sigla);
    //   imprimeDados(dados, cabecalho);
    //    printf("count %lld id %d\n", count, dados->id);
    int i = 0;
    int tamanhoCampo = 0;
    // dois loops: primeiro, para fazermos a contagem de quantos campos foram satisfeitos. Depois, para encontrarmos cada campo
    while (i < n)
    {
        // printf("oioi %d\n", n);
        fseek(BIN, posicao, SEEK_SET);
        for (int j = 0; j < 7; j++)
        {
            if (j == 0)
            {
                if (strcmp(nomeCamposAtualiza[i], "id") == 0)
                {

                    dados->id = atoi(valorCamposAtualiza[i]);
                }
            }
            if (j == 1)
            {
                if (strcmp(nomeCamposAtualiza[i], "ano") == 0)
                {
                    dados->ano = atoi(valorCamposAtualiza[i]);
                }
            }
            if (j == 2)
            {
                if (strcmp(nomeCamposAtualiza[i], "qtt") == 0)
                {
                    dados->quantidade = atoi(valorCamposAtualiza[i]);
                }
            }
            if (j == 3)
            {
                if (strcmp(nomeCamposAtualiza[i], "sigla") == 0)
                {

                    dados->sigla = valorCamposAtualiza[i];
                }
            }
            if (j == 4)
            {
                if (strcmp(nomeCamposAtualiza[i], "cidade") == 0)
                {
                    int tamanhoAtualizado = strlen(valorCamposAtualiza[i]);

                    dados->cidade = valorCamposAtualiza[i];
                    dados->tamanhoCidade = tamanhoAtualizado;
                }
            }
            if (j == 5)
            {
                if (strcmp(nomeCamposAtualiza[i], "marca") == 0)
                {
                    int tamanhoAtualizado = strlen(valorCamposAtualiza[i]);

                    dados->marca = valorCamposAtualiza[i];
                    dados->tamanhoMarca = tamanhoAtualizado;
                }
            }
            if (j == 6)
            {
                if (strcmp(nomeCamposAtualiza[i], "modelo") == 0)
                {
                    // printf("modelo: %s\n", valorCamposAtualiza[i]);
                    int tamanhoAtualizado = strlen(valorCamposAtualiza[i]);
                    dados->modelo = valorCamposAtualiza[i];
                    dados->tamanhoModelo = tamanhoAtualizado;
                }
            }
        }
        i++;
        // printf("oioi %s\n", dados->cidade);
        fseek(BIN, posicao, SEEK_SET);
        //printf("ID: %d\n", dados->id);
        //imprimeDados(dados, cabecalho);
        escreve_dados(dados, BIN, 1);
        //  fseek(BIN, posicao + 5, SEEK_SET);
        //  fread(&id, sizeof(int), 1, BIN);
    }

    // imprimeDados(dados, cabecalho);
    // liberaDados(dados);
    // free(cabecalho);
    // colocando início para pegarmos o tamanho do array depois em O(1)
    // printf("num: %d\n", numRegRemovidos);
    // printf("indices remov: %d\n",indicesRemovidos[0]);
    return;
}

// funcao de liberacao de memoria para os dados
void liberaDados(dados_t *dados)
{
    free(dados->cidade);
    free(dados->marca);
    free(dados->modelo);
    free(dados->sigla);
    free(dados);
    return;
}