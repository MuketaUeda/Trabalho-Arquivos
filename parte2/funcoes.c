/*
Trabalho 1 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
#include "funcoes.h"
#include <ctype.h>

// Funcao de leitura de strings
char *read_line(FILE *stream, int *isEof)
{
    char *linha = NULL;
    int tamanhoLinha = 0;

    do
    {
        linha = realloc(linha, ++tamanhoLinha * sizeof(char));
        linha[tamanhoLinha - 1] = fgetc(stream);
    } while (linha[tamanhoLinha - 1] != EOF && linha[tamanhoLinha - 1] != '\n');

    if (linha[tamanhoLinha - 1] == EOF)
    {
        linha[tamanhoLinha - 1] = '\0';
        *isEof = 1;
    }
    else if (linha[tamanhoLinha - 1] == '\n')
    {
        linha[tamanhoLinha - 1] = '\0';
        if (linha[tamanhoLinha - 2] == '\r')
            linha[tamanhoLinha - 2] = '\0';
    }

    return linha;
}

// print para binario na tela
void binarioNaTela(char *nomeArquivoBinario)
{ /* Você não precisa entender o código dessa função. */

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
     *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb")))
    {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *)malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for (i = 0; i < fl; i++)
    {
        cs += (unsigned long)mb[i];
    }
    printf("%lf\n", (cs / (double)100));
    free(mb);
    fclose(fs);
}

// funcao oferecida para leitura com aspas
void scan_quote_string(char *str)
{
    /*
     *	Use essa função para ler um campo string delimitado entre aspas (").
     *	Chame ela na hora que for ler tal campo. Por exemplo:
     *
     *	A entrada está da seguinte forma:
     *		nomeDoCampo "MARIA DA SILVA"
     *
     *	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
     *		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
     *		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
     *
     */
    char R;
    while ((R = getchar()) != EOF && isspace(R))
        ; // ignorar espaços, \r, \n...
    if (R == 'N' || R == 'n')
    { // campo NULO
        getchar();
        getchar();
        getchar();       // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    }
    else if (R == '\"')
    {
        if (scanf("%[^\"]", str) != 1)
        { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar(); // ignorar aspas fechando
    }
    else if (R != EOF)
    { // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
        str[0] = R;
        scanf("%s", &str[1]);
    }
    else
    { // EOF
        strcpy(str, "");
    }
}

// funcao de copia e escrita
void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario)
{
    FILE *CSV = abre_CSV_leitura(nomeCSV);
    FILE *BIN = abre_bin_escrita(nomeBinario);
    copia_binario(CSV, BIN, nomeBinario, tipoArquivo);
}

// funcao de separacao das strings do csv para strings menores
char *my_str_tok(char *string, char *delimitador)
{
    char *locVirgula, *aux;
    static char *fonte = NULL;

    if (string != NULL)
        fonte = string;

    if (fonte == NULL || *fonte == '\0')
        return NULL;

    aux = fonte;

    // strpbrk: encontra o primeiro caracter da string 1 igual a qualquer caracter da string 2
    if ((locVirgula = strpbrk(fonte, delimitador)) != NULL) // encontra o demilitador dentro da string
    {
        *locVirgula = 0;
        fonte = ++locVirgula;
    }
    else
        fonte += strlen(fonte);

    return aux;
}

// funcao de impressao do conteudo do arquivo binario
void funcionalidade2(int tipoArq, char *nomeBinario)
{

    FILE *BIN = abre_bin_leitura(nomeBinario);
    cabecalho_t *cabecalho;
    cabecalho = inicia_cabecalho();

    if (tipoArq == 1)
    {

        int aux = 0;
        ler_cab_arquivo(BIN, cabecalho, 1);
        if (cabecalho->proxRRN != 0) // verificacao de existencia do registro
        {

            while (aux < cabecalho->proxRRN) // loop responsavel por inicializar, ler, imprimir e liberar os dados
            {
                dados_t *dados = inicializa_dados();
                ler_dados_tipo1(BIN, dados);
                imprimeDados(dados, cabecalho);
                liberaDados(dados);
                aux++;
            }
        }
        else
        {
            printf("Registro inexistente\n");
            fclose(BIN);
            return;
        }
    }

    if (tipoArq == 2)
    {

        long long int aux = 190;
        ler_cab_arquivo(BIN, cabecalho, 2);

        if (cabecalho->proxByteOffset <= aux) // verificacao de existencia de registro
        {
            printf("Registro inexistente\n");
            fclose(BIN);
            return;
        }

        while (aux < cabecalho->proxByteOffset) // loop responsavel por inicializar, ler, imprimir e liberar os dados
        {
            dados_t *dados = inicializa_dados();
            aux += ler_dados_tipo2(BIN, dados);
            imprimeDados(dados, cabecalho);
            liberaDados(dados);
        }
    }
    free(cabecalho);
    fclose(BIN);
    return;
}

void funcionalidade3(int tipoArquivo, char *nomeBinario, int n)
{
    FILE *BIN = abre_bin_leitura(nomeBinario);
    char **nomeCampos = NULL;
    char **valorCampos = NULL;

    // criacao de uma matriz para armazenar as strings lidas para a busca
    nomeCampos = (char **)malloc(n * sizeof(char *));
    valorCampos = (char **)malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++)
    {
        // Alocando valores suficientes e depois armazenando o input
        nomeCampos[i] = (char *)malloc(15 * sizeof(char));
        valorCampos[i] = (char *)malloc(30 * sizeof(char));
        scanf("%s", nomeCampos[i]);
        scan_quote_string(valorCampos[i]);
    }

    // Chamando a função da busca. Nela, tratamos diferenças entre os tipos de arquivos
    busca(BIN, nomeCampos, valorCampos, n, tipoArquivo);

    for (int i = 0; i < n; i++)
    {
        free(nomeCampos[i]);
        free(valorCampos[i]);
    }

    free(nomeCampos);
    free(valorCampos);
    fclose(BIN);
    return;
}

// funcao de recuperacao de dados a partir do RRN
void funcionalidade4(char *nomeBinario, int RRN)
{

    FILE *BIN = abre_bin_leitura(nomeBinario);
    dados_t *dados;
    cabecalho_t *cabecalho;
    cabecalho = inicia_cabecalho();
    dados = inicializa_dados();
    ler_cab_arquivo(BIN, cabecalho, 1);

    if (RRN >= cabecalho->proxRRN || RRN < 0) // verifica a existencia do registro
    {
        printf("Registro inexistente.\n");
        fclose(BIN);
        exit(0);
    }
    posArq(BIN, dados, RRN); // funcao responsavel por posicionar o ponteiro corretamente no arquivo
    imprimeDados(dados, cabecalho);
    liberaDados(dados);
    free(cabecalho);
    fclose(BIN);
    return;
}

void funcionalidade5(int tipoArquivo, char *nomeBinario, char *nomeIndice)
{
    // indices = (regIndice_t *)realloc(indices, (++count) * sizeof(regIndice_t));
    regIndice_t *indices = (regIndice_t *)malloc(1 * sizeof(regIndice_t));

    FILE *arqIndice = abre_bin_escrita(nomeIndice);
    FILE *BIN = abre_bin_leitura(nomeBinario);

    cabecalho_t *cabecalho = inicia_cabecalho();
    ler_cab_arquivo(BIN, cabecalho, tipoArquivo);
    fseek(arqIndice, 0, SEEK_SET);
    fwrite(&cabecalho->status, sizeof(char), 1, arqIndice);
    long long int prox = 0;

    // int tamanhoTotal = 1;
    //  Aqui, vamos iterar sobre o arquivo binario e registrar cada informacao que precisamos
    int count = 0;

    if (tipoArquivo == 1)
    {
        count = 0;
        int rrn = 0;
        while (rrn < cabecalho->proxRRN)
        {
            indices[count].proxRRN = rrn;
            char removido = ler_indices_tipo1(&indices[count], BIN);
            if (removido == '0')
                count++;
            indices = (regIndice_t *)realloc(indices, (count + 1) * sizeof(regIndice_t));
            rrn++;
        }
    }
    if (tipoArquivo == 2)
    {
        long long int aux = 190;
        // ler_cab_arquivo(BIN, cabecalho, 2);

        if (cabecalho->proxByteOffset <= aux) // verificacao de existencia de registro
        {
            printf("Registro inexistente\n");
            fclose(BIN);
            return;
        }

        while (aux < cabecalho->proxByteOffset) // loop responsavel por inicializar, ler, imprimir e liberar os dados
        {
            dados_t *dados = inicializa_dados();
            indices[count].offSet = aux;
            aux += ler_dados_tipo2(BIN, dados);
            indices[count].id = dados->id;
            if (dados->removido == '0')
                count++;
            indices = (regIndice_t *)realloc(indices, (count + 1) * sizeof(regIndice_t));
            liberaDados(dados);
        }
    }

    // Ordenar os índices, caso não estejam ordenados
    indices = insertionSort(indices, count);

    // printArray(indices, count);

    int i = 0;
    while (i < count)
    {
        // printf("vount: %d\n", count);
        escreve_indice(&indices[i], arqIndice, tipoArquivo);
        i++;
    }

    fclose(arqIndice);
    fclose(BIN);

    binarioNaTela(nomeIndice);
    free(cabecalho);
    destruir_indice(indices);

    return;
}

void funcionalidade6(int tipoArquivo, char *nomeDados, char *nomeIndice, int numRemocoes)
{
    regIndice_t *indices = (regIndice_t *)malloc(1 * sizeof(regIndice_t));
    FILE *dados = abre_bin_leitura(nomeDados);
    FILE *indice = abre_bin_leitura(nomeIndice);
    int counter = 0;
    while (counter < numRemocoes)
    {
        char **nomeCampos = NULL;
        char **valorCampos = NULL;
        int numCampos;
        int idVerify = 0;
        scanf("%d", &numCampos);

        // criacao de uma matriz para armazenar as strings lidas para a busca
        nomeCampos = (char **)malloc(numCampos * sizeof(char *));
        valorCampos = (char **)malloc(numCampos * sizeof(char *));

        for (int i = 0; i < numCampos; i++)
        {
            // Alocando valores suficientes e depois armazenando o input
            nomeCampos[i] = (char *)malloc(15 * sizeof(char));
            valorCampos[i] = (char *)malloc(30 * sizeof(char));
            scanf("%s", nomeCampos[i]);
            if (strcmp(nomeCampos[i], "id") == 0)
                idVerify = i;

            scan_quote_string(valorCampos[i]);
        }

        if (idVerify != 0)
        {
            int tamanhoIndice = sizeof(indices) / sizeof(indices[0]);
            busca_binaria_id(indices, 0, tamanhoIndice - 1, valorCampos[idVerify]);
        }
        else if (idVerify == 0)
        {
            busca(dados, nomeCampos, valorCampos, numCampos, tipoArquivo);
        }

        for (int i = 0; i < numCampos; i++)
        {
            free(nomeCampos[i]);
            free(valorCampos[i]);
        }

        free(nomeCampos);
        free(valorCampos);
        counter++;
    }
    return;
}

void funcionalidade7(int tipoArquivo, char* nomeDados, char* nomeIndice, int n){

    FILE *fp = abre_bin_leitura(nomeDados);
    FILE *indice = abre_bin_leitura(nomeIndice);
    dados_t *dados = inicializa_dados();
    int count = 0;
    int id, ano, qtt;
    while(count < n){  
        scanf("%d %d %d", &id, &ano, &qtt);
        Leitura(dados);

        //nao mexi nessa func ainda pq to com duvida sobre a fita das pilhas e listas e como verificar os espacos e afins
        //inserirDados(dados, indice, fp, tipoArquivo);

        count++;
    }    
    //binarioNaTela(nomeDados);
    //binarioNaTela(nomeIndice);
    return;
}

void Leitura(dados_t *dados){
    char* aux;
    for(int i = 1; i < 5; i++){
        if(i == 1){
            aux = malloc(sizeof(char)*50);
            scan_quote_string(aux);
            dados->sigla = malloc(sizeof(char)*strlen(aux)+1);
            dados->sigla = aux;
        }
        if(i == 2){
            aux = malloc(sizeof(char)*50);
            scan_quote_string(aux);
            dados->cidade = malloc(sizeof(char)*strlen(aux)+1);
            dados->cidade = aux;
        }
        if(i == 3){
            aux = malloc(sizeof(char)*50);
            scan_quote_string(aux);
            dados->marca = malloc(sizeof(char)*strlen(aux)+1);
            dados->marca = aux;

        }
        if(i == 4){
            aux = malloc(sizeof(char)*50);
            scan_quote_string(aux);
            dados->modelo = malloc(sizeof(char)*strlen(aux)+1);
            dados->modelo = aux;
        }
            
    }
    free(aux);
}

//apenas copiei o conteudo da 6, porem tenho que fazer ajustes na leitura
void funcionalidade8(int tipoArquivo, char* nomeDados, char* nomeIndice, int n){

    regIndice_t *indices = (regIndice_t *)malloc(1 * sizeof(regIndice_t));
    FILE *dados = abre_bin_leitura(nomeDados);
    FILE *indice = abre_bin_leitura(nomeIndice);
    int counter = 0;

    while (counter < n)
    {
        char **nomeCampos = NULL;
        char **valorCampos = NULL;
        int numCampos;
        int idVerify = 0;
        scanf("%d", &numCampos);

        // criacao de uma matriz para armazenar as strings lidas para a busca
        nomeCampos = (char **)malloc(numCampos * sizeof(char *));
        valorCampos = (char **)malloc(numCampos * sizeof(char *));

        for (int i = 0; i < numCampos; i++)
        {
            // Alocando valores suficientes e depois armazenando o input
            nomeCampos[i] = (char *)malloc(15 * sizeof(char));
            valorCampos[i] = (char *)malloc(30 * sizeof(char));
            scanf("%s", nomeCampos[i]);
            if (strcmp(nomeCampos[i], "id") == 0)
                idVerify = i;

            scan_quote_string(valorCampos[i]);
        }

        if (idVerify != 0)
        {
            int tamanhoIndice = sizeof(indices) / sizeof(indices[0]);
            busca_binaria_id(indices, 0, tamanhoIndice - 1, valorCampos[idVerify]);
        }
        else if (idVerify == 0)
        {
            busca(dados, nomeCampos, valorCampos, numCampos, tipoArquivo);
        }

        for (int i = 0; i < numCampos; i++)
        {
            free(nomeCampos[i]);
            free(valorCampos[i]);
        }

        free(nomeCampos);
        free(valorCampos);
        counter++;
    }
    return;
}

int busca_binaria_id(regIndice_t *indices, int posicaoInicial, int posicaoFinal, int chave)
{
    while (posicaoInicial <= posicaoFinal)
    { // log n

        int centro = (int)((posicaoInicial + posicaoFinal) / 2);
        printf("valor inicial %i; valor final %i; valor central %i\n",
               indices[posicaoInicial].id, indices[posicaoFinal].id, indices[centro].id);

        if (chave == indices[centro].id)
            return centro; // valor encontrado

        if (chave < indices[centro].id) // se o n�mero existir estar� na primeira metade
            posicaoFinal = centro - 1;
        if (chave > indices[centro].id) // se o n�mero existir estar� na segunda metade
            posicaoInicial = centro + 1;
    }

    return -1; // valor n�o encontrado
}

/* Function to sort an array using insertion sort*/
regIndice_t *insertionSort(regIndice_t *indices, int tamanho)
{
    int i, keyId, keyProxRRN, keyProxOffset, j;
    for (i = 1; i < tamanho; i++)
    {
        keyId = indices[i].id;
        keyProxRRN = indices[i].proxRRN;
        keyProxOffset = indices[i].offSet;
        j = i - 1;

        /* Move elements of indices[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && indices[j].id > keyId)
        {
            indices[j + 1] = indices[j];
            j = j - 1;
        }
        indices[j + 1].id = keyId;
        indices[j + 1].proxRRN = keyProxRRN;
        indices[j + 1].offSet = keyProxOffset;
    }
    return indices;
}

// A utility function to print an array of size tamanho
void printArray(regIndice_t *indices, int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        printf("id: %d \n", indices[i].id);
        // printf("prox: %d \n", indices[i].proxRRN);
    }
    printf("\n");
}

//
void busca(FILE *BIN, char **nomeCampos, char **valorCampos, int n, int tipoArquivo)
{
    // Vamos primeiro percorrer o primeiro cabeçalho. Só para chegarmos nos dados e pegarmos alguns valores
    cabecalho_t *cabecalho = inicia_cabecalho();
    ler_cab_arquivo(BIN, cabecalho, tipoArquivo);
    dados_t *dados = NULL;

    int count = 0;
    int registroEncontrado = 0;
    long long int prox = 0;

    // Verificação do tipo do arquivo
    if (tipoArquivo == 1)
        prox = cabecalho->proxRRN;
    else if (tipoArquivo == 2)
        prox = cabecalho->proxByteOffset;

    int tamanhoTotal = 0;

    while (count < prox)
    {
        dados = inicializa_dados();
        if (tipoArquivo == 1)
            ler_dados_tipo1(BIN, dados);
        else if (tipoArquivo == 2)
            tamanhoTotal = ler_dados_tipo2(BIN, dados);

        count += tamanhoTotal;

        if (dados->removido == 1)
        {
            liberaDados(dados);
            continue;
        }

        int condicoesAtendidas = 0;
        int i = 0;

        // dois loops: primeiro, para fazermos a contagem de quantos campos foram satisfeitos. Depois, para encontrarmos cada campo
        while (i < n)
        {
            for (int j = 0; j < 7; j++)
            {
                if (j == 0)
                {
                    if (strcmp(nomeCampos[i], "id") == 0)
                    {
                        if (dados->id == atoi(valorCampos[i]))
                            condicoesAtendidas++;
                    }
                }
                if (j == 1)
                {
                    if (strcmp(nomeCampos[i], "ano") == 0)
                    {
                        if (dados->ano == atoi(valorCampos[i]))
                            condicoesAtendidas++;
                    }
                }
                if (j == 2)
                {
                    if (strcmp(nomeCampos[i], "qtt") == 0)
                    {
                        if (dados->quantidade == atoi(valorCampos[i]))
                            condicoesAtendidas++;
                    }
                }
                if (j == 3)
                {
                    if (strcmp(nomeCampos[i], "sigla") == 0)
                    {
                        if (strcmp(dados->sigla, valorCampos[i]) == 0)
                            condicoesAtendidas++;
                    }
                }
                if (j == 4)
                {
                    if (strcmp(nomeCampos[i], "cidade") == 0)
                    {
                        if (dados->cidade != NULL && strcmp(dados->cidade, valorCampos[i]) == 0)
                        {
                            condicoesAtendidas++;
                        }
                    }
                }
                if (j == 5)
                {
                    if (strcmp(nomeCampos[i], "marca") == 0)
                    {
                        if (dados->marca != NULL && strcmp(dados->marca, valorCampos[i]) == 0)
                            condicoesAtendidas++;
                    }
                }
                if (j == 6)
                {
                    if (strcmp(nomeCampos[i], "modelo") == 0)
                    {
                        if (dados->modelo != NULL && strcmp(dados->modelo, valorCampos[i]) == 0)
                            condicoesAtendidas++;
                    }
                }
            }
            i++;
        }
        if (condicoesAtendidas == n)
        {
            imprimeDados(dados, cabecalho);
            registroEncontrado = 1;
        }
        count++;
        liberaDados(dados);
    }
    if (registroEncontrado == 0)
    {
        printf("Registro inexistente\n");
    }
    free(cabecalho);
    return;
}

// funcao responsavel por copiar o csv e escrever no arquivo binario
void copia_binario(FILE *CSV, FILE *BIN, char *nomeBinario, int tipoArquivo)
{
    cabecalho_t *cabecalho = inicia_cabecalho();
    cabecalho->proxByteOffset = 0;
    escreve_cabecalho_arquivo(cabecalho, BIN, tipoArquivo);
    int isEof = 0;
    cabecalho->proxByteOffset = 190;

    // Linha1 indica o cabeçalho do CSV, que não queremos.
    char *linha1 = read_line(CSV, &isEof);
    free(linha1);

    long long int somaDados = 0;
    while (isEof == 0)
    {
        dados_t *dados = inicializa_dados();
        char *linha = read_line(CSV, &isEof);
        char *token = my_str_tok(linha, ",");

        if (isEof == 1 && strlen(linha) == 0)
        {
            free(linha);
            break;
        }

        if (token != NULL)
            dados->id = atoi(token);
        int contador = 2;

        while (token != NULL)
        {
            token = my_str_tok(NULL, ",");
            if (contador == 2)
            {
                if (strlen(token) > 0)
                    dados->ano = atoi(token);
            }
            if (contador == 3)
            {
                if (token != NULL)
                {
                    dados->tamanhoCidade = strlen(token);
                    dados->cidade = malloc(sizeof(char) * dados->tamanhoCidade + 1);
                    strcpy(dados->cidade, token);
                    dados->cidade[dados->tamanhoCidade] = '\0';
                }
            }
            if (contador == 4)
            {
                if (strlen(token) > 0)
                    dados->quantidade = atoi(token);
            }
            if (contador == 5)
                strcpy(dados->sigla, token);
            if (contador == 6)
            {
                if (token != NULL)
                {
                    dados->tamanhoMarca = strlen(token);
                    dados->marca = malloc(sizeof(char) * dados->tamanhoMarca + 1);
                    strcpy(dados->marca, token);
                    dados->marca[dados->tamanhoMarca] = '\0';
                }
            }
            if (contador == 7)
            {
                if (token != NULL)
                {
                    dados->tamanhoModelo = strlen(token);
                    dados->modelo = malloc(sizeof(char) * dados->tamanhoModelo + 1);
                    strcpy(dados->modelo, token);
                    dados->modelo[dados->tamanhoModelo] = '\0';
                }
            }
            contador++;
        }

        int tamanhoDados = 0;
        if (tipoArquivo == 1)
        {
            escreve_dados(dados, BIN, tipoArquivo);
            cabecalho->proxRRN = cabecalho->proxRRN + 1;
        }
        else if (tipoArquivo == 2)
        {
            tamanhoDados = escreve_dados(dados, BIN, tipoArquivo);
            somaDados += tamanhoDados;
            cabecalho->proxByteOffset = cabecalho->proxByteOffset + tamanhoDados;
        }
        liberaDados(dados);
        free(token);
        free(linha);
    }

    cabecalho->status = '1';
    escreve_cabecalho_arquivo(cabecalho, BIN, tipoArquivo);

    fclose(BIN);
    fclose(CSV);
    binarioNaTela(nomeBinario);
    free(cabecalho);
}

// funcao de abertura do csv para leitura
FILE *abre_CSV_leitura(char *nomeCSV)
{
    FILE *fp = fopen(nomeCSV, "r");
    if (fp == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    return fp;
}

// funcao de abertura do binario para escrita
FILE *abre_bin_escrita(char *nomeBin)
{
    FILE *fp = fopen(nomeBin, "wb");

    if (fp == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    return fp;
}

// funcao de abertura do arquivo binerio para leitura
FILE *abre_bin_leitura(char *nomeBin)
{
    FILE *fb = fopen(nomeBin, "rb+");

    if (fb == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    return fb;
}

// funcao para reposicionar o ponteiro na posicao correta
void posArq(FILE *BIN, dados_t *dados, int RRN)
{
    int aux;
    aux = 182 + (RRN * 97);

    fseek(BIN, aux, SEEK_SET);
    ler_dados_tipo1(BIN, dados);
    return;
}

// funcao de impressao dos registros
void imprimeDados(dados_t *dados, cabecalho_t *cabecalho)
{

    if (dados->removido == '1') // verificacao de removacao
    {
        return;
    }
    else
    {
        // verifica se o tamanho da string e maior q zero, caso seja printa o dado, caso nao insere 'NAO PREENCHIDO'
        if (dados->tamanhoMarca > 0)
        {
            printf("%s%s\n", cabecalho->desMarca, dados->marca);
        }
        else
        {
            printf("%sNAO PREENCHIDO\n", cabecalho->desMarca);
        }

        if (dados->tamanhoModelo > 0)
        {
            printf("%s%s\n", cabecalho->desModelo, dados->modelo);
        }
        else
        {
            printf("%sNAO PREENCHIDO\n", cabecalho->desModelo);
        }
        if (dados->ano > 0)
        {
            printf("%s%d\n", cabecalho->desAno, dados->ano);
        }
        else
        {
            printf("%sNAO PREENCHIDO\n", cabecalho->desAno);
        }

        if (dados->tamanhoCidade > 0)
        {
            printf("%s%s\n", cabecalho->desNomeCidade, dados->cidade);
        }
        else
        {
            printf("%sNAO PREENCHIDO\n", cabecalho->desNomeCidade);
        }

        if (dados->quantidade != -1)
        {
            printf("%s%d\n", cabecalho->desQuantidade, dados->quantidade);
        }
        else
        {
            printf("%sNAO PREENCHIDO\n", cabecalho->desQuantidade);
        }
        printf("\n");
    }
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