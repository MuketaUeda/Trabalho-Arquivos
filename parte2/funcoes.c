/*
Trabalho 2 - Organização de Arquivos - SCC0215
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
    busca(BIN, nomeCampos, valorCampos, n, tipoArquivo, 0, 3);

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
    posicao_arquivo_leitura(BIN, dados, RRN); // funcao responsavel por posicionar o ponteiro corretamente no arquivo
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
            char removido = ler_indices_dados_tipo1(&indices[count], BIN);
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
    FILE *arqIndice = abre_bin_leitura(nomeIndice);
    // pilha_t *pilhaIndices = cria_pilha();
    cabecalho_t *cabecalho = inicia_cabecalho();
    dados_t *dados = inicializa_dados();
    FILE *arqDados = abre_bin_leitura(nomeDados);

    ler_cab_arquivo(arqDados, cabecalho, tipoArquivo);
    long long int prox = 0;
    if (tipoArquivo == 1)
        prox = cabecalho->proxRRN;
    if (tipoArquivo == 2)
        prox = cabecalho->proxByteOffset;

    int size = 0;
    char status;

    fseek(arqIndice, 0, SEEK_END);
    int tamanho = ftell(arqIndice);
    fseek(arqIndice, 0, SEEK_SET);
    fread(&status, sizeof(char), 1, arqIndice);

    long long int counter = 1;
    int k = 0;
    while (counter < tamanho)
    {
        indices = (regIndice_t *)realloc(indices, (++size) * sizeof(regIndice_t));
        counter += ler_arquivo_indices(&indices[k], arqIndice, tipoArquivo);
        // printf("id: %d rrn: %lld\n", indices[k].id, indices[k].offSet);
        indices[k].id = indices[k].id;
        k++;
    }

    indices = insertionSort(indices, size);
    int counter2 = 0;
    int posicaoID = 0;

    char **nomeCampos = (char **)malloc(sizeof(char *));
    char **valorCampos = (char **)malloc(sizeof(char *));
    int ids[numRemocoes];

    int c = 0;
    while (counter2 < numRemocoes)
    {
        int numCampos;
        int idVerify = -1;
        scanf("%d", &numCampos);
        // printf("num: %d\n", counter2);
        //  criacao de uma matriz para armazenar as strings lidas para a busca
        nomeCampos = (char **)realloc(nomeCampos, numCampos * sizeof(char *));
        valorCampos = (char **)realloc(valorCampos, numCampos * sizeof(char *));

        for (int i = 0; i < numCampos; i++)
        {
            // Alocando valores suficientes e depois armazenando o input
            nomeCampos[i] = (char *)malloc(15 * sizeof(char));
            valorCampos[i] = (char *)malloc(30 * sizeof(char));
            scanf("%s", nomeCampos[i]);
            // scanf("%s", valorCampos[i]);
            scan_quote_string(valorCampos[i]);
            // printf("%s %d\n", nomeCampos[i], atoi(valorCampos[i]));

            if (strcmp(nomeCampos[i], "id") == 0)
            {
                idVerify = i;
            }
        }

        // 1)Procurar o ID a ser removido
        // 2)Remover elemento do array
        // 3)Adicionar seu RRN na pilha de removidos
        // 4)Buscá-lo no arquivo de dados
        // 5)Atualizar "removido" para '1' e escrever de volta no arquivo
        // 6)Reescrever o array de struct no arquivo de índices
        // arqDados = abre_bin_escrita(nomeDados);
        if (idVerify != -1 && numCampos == 1)
        {

            int idBusca = 0;
            idBusca = atoi(valorCampos[idVerify]);
            // printf("entrei, id: %d\n", idBusca);
            posicaoID = busca_binaria_id(indices, 0, (size - 1), idBusca);

            ids[counter2] = indices[posicaoID].id;
            if (posicaoID != -1)
            {
                long long int pos = -1;
                // push(pilhaIndices, indices[posicaoID].proxRRN);
                if (tipoArquivo == 1)
                {
                    pos = indices[posicaoID].proxRRN;
                    pos = 182 + (pos * 97);
                }
                if (tipoArquivo == 2)
                    pos = indices[posicaoID].offSet;
                // printf("pos: %d offset: %lld\n\n\n", posicaoID, indices[posicaoID].offSet);
                size = remover_elemento_array(indices, posicaoID, size, tipoArquivo);
                posicao_arquivo_escrita(arqDados, dados, pos, tipoArquivo);
            }
        }
        else
        {
            int *indicesRemovidos = malloc(1 * sizeof(int));
            int numIndicesRemovidos = 0;
            indicesRemovidos = busca(arqDados, nomeCampos, valorCampos, numCampos, tipoArquivo, 1, 6);
            numIndicesRemovidos = indicesRemovidos[0];
            // printf("num indices: %d\n", numIndicesRemovidos);
            // printf("num Indices: %d\n", numIndicesRemovidos);
            for (int i = 0; i < numIndicesRemovidos; i++)
            {
                posicaoID = busca_binaria_id(indices, 0, (size - 1), indicesRemovidos[i + 1]);
                // printf("indice Pos: %d indice certo: %d\n", indices[posicaoID].id, indicesRemovidos[i]);
                if (indicesRemovidos[i + 1] != 0)
                    size = remover_elemento_array(indices, posicaoID, size, tipoArquivo);
                // printf("%d\n", ++c);
            }

            idVerify = -1;
        }
        counter2++;
    }

    fclose(arqIndice);
    arqIndice = abre_bin_escrita(nomeIndice);
    fwrite(&cabecalho->status, sizeof(char), 1, arqIndice);
    int i = 0;

    while (i < size)
    {
        // printf("id: %d offset: %lld\n", indices[i].id, indices[i].offSet);
        escreve_indice(&indices[i], arqIndice, tipoArquivo);
        i++;
    }

    fclose(arqDados);
    fclose(arqIndice);
    binarioNaTela(nomeDados);
    binarioNaTela(nomeIndice);

    return;
}


void funcionalidade7(int tipoArquivo, char *nomeDados, char *nomeIndice, int n)
{

    FILE *fp = abre_bin_leitura(nomeDados);
    FILE *arqIndice = abre_bin_leitura(nomeIndice);
    cabecalho_t *cabecalho = inicia_cabecalho();
    regIndice_t *indices = (regIndice_t *)malloc(sizeof(regIndice_t));
    int count = 0;

    if (tipoArquivo == 1)
    {
        int topo = 0;
        long long int proxRRN = 0;
        long long int aux = 0;

        //recebendo o topo da pilha de removidos
        ler_cab_arquivo(fp, cabecalho, 1);
        fseek(fp, 1, SEEK_SET);
        topo = cabecalho->topo;

        while (count < n)
        {
            indices = (regIndice_t *)realloc(indices, sizeof(regIndice_t));
            dados_t *dados = inicializa_dados();

            //funcao de leitura para os novos registros
            Leitura(dados);

            //se o topo for -1 escreve no fim dos arquivos de dados e index
            if (topo == -1)
            {
                indices->id = dados->id;
                indices->proxRRN = cabecalho->proxRRN;

                fseek(fp, 0, SEEK_END);
                escreve_dados(dados, fp, tipoArquivo, -1);

                fseek(arqIndice, 0, SEEK_END);
                escreve_indice(indices, arqIndice, tipoArquivo);
                cabecalho->proxRRN++;
            }
            //caso contrario acha posicao onde deve ser inserido e reordena o arquivo de index
            else
            {
                aux = 182 + (97 * topo); //achando a posicao correta do ponteiro
                fseek(fp, aux, SEEK_SET);
                fread(&dados->removido, sizeof(char), 1, fp);

                //se o dado era removido passa a nao ser mais pois eh inserido um novo registro valido
                if (dados->removido == '1')
                {
                    dados->removido = '0';
                }
                fread(&proxRRN, sizeof(int), 1, fp); //recebendo proxrrn
                fseek(fp, aux, SEEK_SET);
                escreve_dados(dados, fp, tipoArquivo, -1);

                //adiciona e reordena o novo indice recebido
                adicionaNovoIndex(arqIndice, dados, indices , nomeIndice, 0, topo, tipoArquivo);

                //atualiza o numero de removidos
                reduzNumeroRemovidos(fp, cabecalho, 178);
            }
            topo = proxRRN; //reposicionando o topo da pilha
            count++;
        }

        //atualiza status
        cabecalho->status = '1';
        if (topo > 0)
        {
            cabecalho->topo = topo; //atualiza topo caso haja mais removidos
        }
        escreve_cabecalho_arquivo(cabecalho, fp, 1);
    }

    if (tipoArquivo == 2)
    {
        long long int topotipo2 = 0;
        long long int byteOffSet = 0;
        int tamReg = 0;

        //recebe o topo da lista ordenada encadeada
        ler_cab_arquivo(fp, cabecalho, 2);
        topotipo2 = cabecalho->topo;

        //recebe o tamanho do registro ao qual queremos "substituir"
        fseek(fp, topotipo2 + 1, SEEK_SET);
        fread(&tamReg, sizeof(int), 1, fp);
        tamReg += 5; // char removido + int tamanho

        while (count < n)
        {
            int tam = 0;
            indices = (regIndice_t *)realloc(indices, sizeof(regIndice_t));
            dados_t *dados = inicializa_dados();

            //recebe o tamanho do registro lido do input
            tam = LeituraTipo2(dados);

            //se topo for igual a -1 ou o tamanho do input for maior que o tamanho disponivel eh inserido no final
            if (topotipo2 == -1 || tam > tamReg)
            {
                indices->id = dados->id;
                indices->offSet = cabecalho->proxByteOffset;
                fseek(fp, 0, SEEK_END);
                escreve_dados(dados, fp, tipoArquivo, -1);

                fseek(arqIndice, 0, SEEK_END);
                escreve_indice(indices, arqIndice, tipoArquivo);
                cabecalho->proxByteOffset = ftell(fp);
            }
            //caso contrario insere no offset lido e prenche o resto do espaco com lixo
            else 
            {
                fseek(fp, topotipo2, SEEK_SET); //reposicionando o ponteiro
                fread(&dados->removido, sizeof(char), 1, fp);
                fread(&tamReg, sizeof(int), 1, fp);
        
                if (dados->removido == '1')
                {
                    dados->removido = '0';
                }
                fread(&byteOffSet, sizeof(int), 1, fp); //recebendo o offset da prox posicao removida
                fseek(fp, topotipo2, SEEK_SET);
                escreve_dados(dados, fp, 2, tamReg);

                // Somamos 5 para considerar sizeof(int) + sizeof(char)
                tamReg += 5;
                insereLixo(fp, tamReg, tam); //preenche espaco sobrando no registro

                adicionaNovoIndex(arqIndice, dados, indices , nomeIndice, topotipo2, 0 , tipoArquivo );

                reduzNumeroRemovidos(fp, cabecalho, 186);
                topotipo2 = byteOffSet; //atualiza topo
            }
            count++;
        }
        
        //muda status
        cabecalho->status = '1';
        if (topotipo2 > 0)
        {   
            cabecalho->topo = topotipo2; //atualiza o topo caso haja mais removidos
        }
        escreve_cabecalho_arquivo(cabecalho, fp, 2);
    }

    fclose(fp);
    fclose(arqIndice);
    binarioNaTela(nomeDados);
    binarioNaTela(nomeIndice);
    return;
}

void funcionalidade8(int tipoArquivo, char *nomeDados, char *nomeIndice, int numAtualizacoes)
{
    regIndice_t *indices = (regIndice_t *)malloc(1 * sizeof(regIndice_t));
    FILE *arqIndice = abre_bin_leitura(nomeIndice);
    cabecalho_t *cabecalho = inicia_cabecalho();
    dados_t *dados = inicializa_dados();
    FILE *arqDados = abre_bin_leitura(nomeDados);

    ler_cab_arquivo(arqDados, cabecalho, tipoArquivo);
    long long int prox = 0;
    if (tipoArquivo == 1)
        prox = cabecalho->proxRRN;
    if (tipoArquivo == 2)
        prox = cabecalho->proxByteOffset;

    int size = 0;
    char status;

    fseek(arqIndice, 0, SEEK_END);
    int tamanho = ftell(arqIndice);
    fseek(arqIndice, 0, SEEK_SET);
    fread(&status, sizeof(char), 1, arqIndice);

    long long int counter = 1;
    int k = 0;
    while (counter < tamanho)
    {
        indices = (regIndice_t *)realloc(indices, (++size) * sizeof(regIndice_t));
        counter += ler_arquivo_indices(&indices[k], arqIndice, tipoArquivo);
        // printf("id: %d rrn: %lld\n", indices[k].id, indices[k].offSet);
        indices[k].id = indices[k].id;
        k++;
    }

    indices = insertionSort(indices, size);
    int counter2 = 0;
    int posicaoID = 0;

    char **nomeCamposBusca = (char **)malloc(sizeof(char *));
    char **valorCamposBusca = (char **)malloc(sizeof(char *));
    char **nomeCamposAtualiza = (char **)malloc(sizeof(char *));
    char **valorCamposAtualiza = (char **)malloc(sizeof(char *));
    int ids[numAtualizacoes];

    int c = 0;
    while (counter2 < numAtualizacoes)
    {
        int numCamposBusca;
        int idVerify = -1;
        scanf("%d", &numCamposBusca);
        // printf("num: %d\n", counter2);
        //  criacao de uma matriz para armazenar as strings lidas para a busca
        nomeCamposBusca = (char **)realloc(nomeCamposBusca, numCamposBusca * sizeof(char *));
        valorCamposBusca = (char **)realloc(valorCamposBusca, numCamposBusca * sizeof(char *));

        for (int i = 0; i < numCamposBusca; i++)
        {
            // Alocando valores suficientes e depois armazenando o input
            nomeCamposBusca[i] = (char *)malloc(15 * sizeof(char));
            valorCamposBusca[i] = (char *)malloc(30 * sizeof(char));
            scanf("%s", nomeCamposBusca[i]);
            scan_quote_string(valorCamposBusca[i]);

            // printf("%s %d\n", nomeCamposBusca[i], atoi(valorCamposBusca[i]));

            if (strcmp(nomeCamposBusca[i], "id") == 0)
            {
                idVerify = i;
            }
        }
        int numCamposAtualiza;
        scanf("%d", &numCamposAtualiza);
        nomeCamposAtualiza = (char **)realloc(nomeCamposAtualiza, numCamposAtualiza * sizeof(char *));
        valorCamposAtualiza = (char **)realloc(valorCamposAtualiza, numCamposAtualiza * sizeof(char *));
        for (int i = 0; i < numCamposAtualiza; i++)
        {
            // Alocando valores suficientes e depois armazenando o input
            nomeCamposAtualiza[i] = (char *)malloc(15 * sizeof(char));
            valorCamposAtualiza[i] = (char *)malloc(30 * sizeof(char));

            scanf("%s", nomeCamposAtualiza[i]);
            scan_quote_string(valorCamposAtualiza[i]);
            if (strcmp("NULO", valorCamposAtualiza[i]) == 0)
                valorCamposAtualiza[i] = NULL;
            // printf("%s %s\n", nomeCamposAtualiza[i], valorCamposAtualiza[i]);
        }

        if (idVerify != -1 && numCamposBusca == 1)
        {

            int idBusca = 0;
            idBusca = atoi(valorCamposBusca[idVerify]);
            posicaoID = busca_binaria_id(indices, 0, (size - 1), idBusca);
            // printf("valor: \n");

            ids[counter2] = indices[posicaoID].id;
            if (posicaoID != -1)
            {
                long long int pos = -1;
                // push(pilhaIndices, indices[posicaoID].proxRRN);
                if (tipoArquivo == 1)
                {
                    pos = indices[posicaoID].proxRRN;
                    pos = 182 + (pos * 97);
                }
                if (tipoArquivo == 2)
                    pos = indices[posicaoID].offSet;

                for (int i = 0; i < numCamposAtualiza; i++)
                {
                    if (strcmp("id", nomeCamposAtualiza[i]) == 0)
                    {
                        atualiza_elemento_array(indices, posicaoID, tipoArquivo, nomeCamposAtualiza[i], atoi(valorCamposAtualiza[i]));
                    }
                    if (strcmp("rrn", nomeCamposAtualiza[i]) == 0)
                    {
                        atualiza_elemento_array(indices, posicaoID, tipoArquivo, nomeCamposAtualiza[i], atoi(valorCamposAtualiza[i]));
                    }
                    if (strcmp("offset", nomeCamposAtualiza[i]) == 0)
                    {
                        atualiza_elemento_array(indices, posicaoID, tipoArquivo, nomeCamposAtualiza[i], atoi(valorCamposAtualiza[i]));
                    }
                }
                // printf("pos: %d offset: %d\n\n\n", posicaoID, atoi(valorCamposBusca[idVerify]));

                // posicao_arquivo_escrita(arqDados, dados, pos, tipoArquivo);
                atualiza_dados_tipo1(arqDados, nomeCamposAtualiza, valorCamposAtualiza, numCamposAtualiza, atoi(valorCamposBusca[idVerify]));
            }
        }
        else
        {
            // printf("fui\n");
            int *indicesAtualizacao = malloc(1 * sizeof(int));
            int numIndicesAtualizados = 0;
            indicesAtualizacao = busca(arqDados, nomeCamposBusca, valorCamposBusca, numCamposBusca, tipoArquivo, 1, 8);
            numIndicesAtualizados = indicesAtualizacao[0];
            // printf("num indices: %d\n", numIndicesAtualizados);
            //  printf("num Indices: %d\n", numIndicesAtualizados);
            //  printf("campos: %s\n", nomeCamposAtualiza[0]);
            for (int i = 0; i < numIndicesAtualizados; i++)
            {
                // printf("num: %d i: %d\n", numIndicesAtualizados, i);
                posicaoID = busca_binaria_id(indices, 0, (size - 1), indicesAtualizacao[i + 1]);
                // printf("indice Pos: %d indice certo: %d\n", indices[posicaoID].id, indicesAtualizacao[i]);
                // printf("Num ca mpos: %d %d\n", indicesAtualizacao[i + 1], numIndicesAtualizados);
                atualiza_dados_tipo1(arqDados, nomeCamposAtualiza, valorCamposAtualiza, numCamposAtualiza, indicesAtualizacao[i + 1]);
                if (indicesAtualizacao[i + 1] != 0)
                {
                    for (int j = 0; j < numCamposAtualiza; j++)
                    {
                        // printf("numCampos: %d\n", numCamposAtualiza);
                        atualiza_elemento_array(indices, posicaoID, tipoArquivo, nomeCamposAtualiza[j], atoi(valorCamposAtualiza[j]));
                    }
                }
                //  printf("%d\n", ++c);
            }

            idVerify = -1;
        }

        indices = insertionSort(indices, size);

        counter2++;
    }

    fclose(arqIndice);
    arqIndice = abre_bin_escrita(nomeIndice);
    fwrite(&cabecalho->status, sizeof(char), 1, arqIndice);
    int i = 0;

    while (i < size)
    {
        // printf("id: %d offset: %lld\n", indices[i].id, indices[i].offSet);
        escreve_indice(&indices[i], arqIndice, tipoArquivo);
        i++;
    }

    fclose(arqDados);
    fclose(arqIndice);
    binarioNaTela(nomeDados);
    binarioNaTela(nomeIndice);

    return;
}

int busca_binaria_id(regIndice_t *indices, int posicaoInicial, int posicaoFinal, int chave)
{
    while (posicaoInicial <= posicaoFinal)
    {

        int centro = (int)((posicaoInicial + posicaoFinal) / 2);
        if (chave == indices[centro].id)
        {
            return centro; // valor encontrado
        }

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
int *busca(FILE *BIN, char **nomeCampos, char **valorCampos, int n, int tipoArquivo, int trabalho2, int funcionalidade)
{
    int wtf = 0;

    // Vamos primeiro percorrer o primeiro cabeçalho. Só para chegarmos nos dados e pegarmos alguns valores
    // fseek(BIN, 0, SEEK_SET);
    cabecalho_t *cabecalho = inicia_cabecalho();
    ler_cab_arquivo(BIN, cabecalho, tipoArquivo);

    dados_t *dados = NULL;

    int *indicesOperacao = malloc(2 * sizeof(int));
    int numRegOperacao = 1;

    long long int count = 0;
    int registroEncontrado = 0;
    long long int prox = 0;

    // Verificação do tipo do arquivo
    if (tipoArquivo == 1)
        prox = cabecalho->proxRRN;
    else if (tipoArquivo == 2)
        prox = cabecalho->proxByteOffset;

    int tamanhoTotal = 0;
    long long int posicao = -1;
    int c = 0;
    while (count < prox)
    {
        dados = inicializa_dados();
        posicao = ftell(BIN);
        // printf("posicao: %lld\n", posicao);
        if (tipoArquivo == 1)
            ler_dados_tipo1(BIN, dados);
        else if (tipoArquivo == 2)
            tamanhoTotal = ler_dados_tipo2(BIN, dados);
        count += tamanhoTotal;

        /*if (dados->id == -1)
        {
            break;
        }*/
        // printf("count %lld id %d\n", count, dados->id);
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
                        {
                            // printf("id: %d inp: %d n %d\n", dados->id, dados->ano, n);
                            condicoesAtendidas++;
                        }
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
                        {
                            condicoesAtendidas++;
                            // printf(": %d\n", ++wtf);
                        }
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
        // printf("condicoes %d n %d\n", condicoesAtendidas, n);
        if (condicoesAtendidas == n)
        {
            if (trabalho2 == 0)
                imprimeDados(dados, cabecalho);
            registroEncontrado = 1;
        }
        if (trabalho2 == 1 && registroEncontrado == 1)
        {
            indicesOperacao = (int *)realloc(indicesOperacao, (++numRegOperacao) * sizeof(int));
            long long int pos = 0;
            dados->removido = '1';
            if (tipoArquivo == 1)
                pos = dados->proxRRN;
            if (tipoArquivo == 2)
                pos = dados->proxOffset;

            // printf("oi\n");
            // printf("count: %lld, prox: %lld\n", count, prox);
            if (funcionalidade == 6)
                posicao_arquivo_escrita(BIN, dados, posicao, tipoArquivo);
            indicesOperacao[numRegOperacao - 1] = dados->id;
            ++c;
            registroEncontrado = 0;
        }
        if (tipoArquivo == 1)
            count++;

        liberaDados(dados);
    }
    if (registroEncontrado == 0 && trabalho2 == 0)
    {
        printf("Registro inexistente\n");
    }
    free(cabecalho);
    // colocando início para pegarmos o tamanho do array depois em O(1)
    // printf("num: %d\n", numRegOperacao);
    indicesOperacao[0] = numRegOperacao - 1;
    // printf("indices remov: %d\n",indicesOperacao[0]);
    return indicesOperacao;
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
            escreve_dados(dados, BIN, tipoArquivo, -1);
            cabecalho->proxRRN = cabecalho->proxRRN + 1;
        }
        else if (tipoArquivo == 2)
        {
            tamanhoDados = escreve_dados(dados, BIN, tipoArquivo, -1);
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

//Leitura para arquivos de tipo1 na func7, aloca strings de entrada
//tambem verifica se sao nulas
void Leitura(dados_t *dados)
{
    char *aux;
    int aux2;
    char *id = malloc(sizeof(char) * 10);
    char *ano = malloc(sizeof(char) * 10);
    char *qtt = malloc(sizeof(char) * 10);

    scanf("%s %s %s", id, ano, qtt);
  
    //verifica se a entrada na eh nula
    if (strcmp(id, "NULO") != 0)
    {
        dados->id = atoi(id);
    }
    if (strcmp(ano, "NULO") != 0)
    {
        dados->ano = atoi(ano);
    }
    if (strcmp(qtt, "NULO") != 0)
    {
        dados->quantidade = atoi(qtt);
    }

    for (int i = 1; i < 5; i++)
    {
        aux = malloc(sizeof(char) * 50);
        if (i == 1)
        {
            scan_quote_string(aux);
            dados->sigla = malloc(sizeof(char) * strlen(aux) + 1);
            strcpy(dados->sigla, aux);
            aux2 = strlen(aux);
            dados->sigla[aux2] = '\0';
        }

        if (i == 2)
        {
            scan_quote_string(aux);
            dados->cidade = malloc(sizeof(char) * strlen(aux) + 1);
            strcpy(dados->cidade, aux);
            aux2 = strlen(aux);
            dados->cidade[aux2] = '\0';
        }

        if (i == 3)
        {
            scan_quote_string(aux);
            dados->marca = malloc(sizeof(char) * strlen(aux) + 1);
            strcpy(dados->marca, aux);
            aux2 = strlen(aux);
            dados->marca[aux2] = '\0';
        }
        if (i == 4)
        {
            scan_quote_string(aux);
            dados->modelo = malloc(sizeof(char) * strlen(aux) + 1);
            strcpy(dados->modelo, aux);
            aux2 = strlen(aux);
            dados->modelo[aux2] = '\0';
        }
        free(aux);
    }
    free(id);
    free(ano);
    free(qtt);
    return;
}

//funcao de leitura para arquivos do tipo2 na func7, criado separadamente pois 
//conta o tamanho da entrada e rentora um int
int LeituraTipo2(dados_t *dados)
{
    //pensar
    int tamAtual = 0;
    char *aux;
    int aux2;
    char *id = malloc(sizeof(char) * 10);
    char *ano = malloc(sizeof(char) * 10);
    char *qtt = malloc(sizeof(char) * 10);

    scanf("%s %s %s", id, ano, qtt);


    //verificacao se a entrada nao eh nula
    if (strcmp(id, "NULO") != 0)
    {
        dados->id = atoi(id);
    }
    
    if (strcmp(ano, "NULO") != 0)
    {
        dados->ano = atoi(ano);
    }

    if (strcmp(qtt, "NULO") != 0)
    {
        dados->quantidade = atoi(qtt);
    }
    tamAtual += sizeof(int) * 3; //adicionando o equivalente a 3 ints, id, ano e qtt

    for (int i = 1; i < 5; i++)
    {
        aux = malloc(sizeof(char) * 50);

        if (i == 1)
        {
            scan_quote_string(aux);
            if (strlen(aux) > 0)
            {
                dados->sigla = malloc(sizeof(char) * strlen(aux) + 1);
                strcpy(dados->sigla, aux);
                aux2 = strlen(aux);
                dados->sigla[aux2] = '\0';
            }
            tamAtual += (sizeof(char) * 2); // espaco ocupado pela sigla
        }

        if (i == 2)
        {
            scan_quote_string(aux);
            if (strlen(aux) > 0)
            {
                dados->cidade = malloc(sizeof(char) * (strlen(aux) + 1));
                strcpy(dados->cidade, aux);
                aux2 = strlen(dados->cidade);
                dados->cidade[aux2] = '\0';
                tamAtual += (sizeof(char) * aux2); // espaco ocupado pela string
                tamAtual += sizeof(int);           // tamanho do campo
                tamAtual += sizeof(char);          // codigo
            }
        }

        if (i == 3)
        {
            scan_quote_string(aux);
            if (strlen(aux) > 0)
            {
                dados->marca = malloc(sizeof(char) * strlen(aux) + 1);
                strcpy(dados->marca, aux);
                aux2 = strlen(aux);
                dados->marca[aux2] = '\0';
                tamAtual += (sizeof(char) * aux2); 
                tamAtual += sizeof(int);           
                tamAtual += sizeof(char);          
            }
        }
        if (i == 4)
        {
            scan_quote_string(aux);
            if (strlen(aux) > 0)
            {
                dados->modelo = malloc(sizeof(char) * strlen(aux) + 1);
                strcpy(dados->modelo, aux);
                aux2 = strlen(aux);
                dados->modelo[aux2] = '\0';
                tamAtual += (sizeof(char) * aux2); 
                tamAtual += sizeof(int);          
                tamAtual += sizeof(char);         
            }
        }
        free(aux);
    }

    //proxOffset + removido + tamanhoAtual
    tamAtual += 13;

    free(id);
    free(ano);
    free(qtt);
    return tamAtual;
}

//funcao responsavel por ler o arq de indice adicionar a um array de struct e inserir novos indices ao array e reordenar
void adicionaNovoIndex(FILE* arqIndice, dados_t* dados,regIndice_t *indices ,char* nomeIndice, long long int topotipo2, int topotipo1, int tipoArquivo ){

    int size = 0;
    long long int counter = 1;
    int k = 0;
    char status = '0';

    //recebendo tamanho total do arquivo
    fseek(arqIndice, 0, SEEK_END);
    int tamanho = ftell(arqIndice);
    fseek(arqIndice, 0, SEEK_SET);
    fread(&status, sizeof(char), 1, arqIndice);

    /*
    Ler todo o arquivo de índices
    Adicionar o novo índice na struct
    ordenar
    escrever de volta
    */
    while (counter < tamanho)
    {
        indices = (regIndice_t *)realloc(indices, (++size) * sizeof(regIndice_t));
        counter += ler_arquivo_indices(&indices[k], arqIndice, tipoArquivo);
        indices[k].id = indices[k].id;
        k++;
    }
    indices = (regIndice_t *)realloc(indices, (++size) * sizeof(regIndice_t));
    indices[k].id = dados->id;
    if(tipoArquivo == 1){
        indices[k].proxRRN = topotipo1;
    }
    if(tipoArquivo == 2){
        indices[k].offSet = topotipo2;
    }
    indices[k].id = indices[k].id;

    indices = insertionSort(indices, size);
    fseek(arqIndice, 0, SEEK_END);
    escreve_indice(indices, arqIndice, tipoArquivo);

    fclose(arqIndice);
    arqIndice = abre_bin_escrita(nomeIndice);

    status = '1';
    fwrite(&status, sizeof(char), 1, arqIndice);

    int i = 0;
    while (i < size)
    {
        escreve_indice(&indices[i], arqIndice, tipoArquivo);
        i++;
    }
    return;
}

//funcao responsavel por inserir lixo no arq binario
void insereLixo(FILE *fp, int tamReg, int tam){
    char *lixo = (char *)malloc((tamReg - tam) * sizeof(char));
    for (int i = 0; i < (tamReg - tam); i++)
    {
        lixo[i] = '$';
    }
    fwrite(lixo, sizeof(char), (tamReg - tam), fp);
    free(lixo);
}

//func responsavel por ler numero de removidos, modificar e reescrever
void reduzNumeroRemovidos(FILE* fp, cabecalho_t *cabecalho, int aux){

    fseek(fp, aux, SEEK_SET);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp);
    cabecalho->nroRegRemovidos--;
    fseek(fp, aux, SEEK_SET);
    fwrite(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp);

    return;
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
    FILE *fp = fopen(nomeBin, "wb+");

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
void posicao_arquivo_leitura(FILE *BIN, dados_t *dados, int RRN)
{
    int aux;
    aux = 182 + (RRN * 97);

    fseek(BIN, aux, SEEK_SET);
    ler_dados_tipo1(BIN, dados);
    return;
}

void posicao_arquivo_escrita(FILE *BIN, dados_t *dados, long long int posicao, int tipoArquivo)
{
    // Armazenar a posição de agora para voltarmos a ela depois e continuarmos buscando
    long long int posicaoInicial = ftell(BIN);
    long long int aux;
    long long int topoOffset;
    char removido = '1';
    // printf("entrei %lld\n", posicao);
    /*
    Lógica da pilha:
    Se o topo não era -1, quer dizer que há outros registros removidos.
    Assim, devemos:
    1)Atualizar o topo
    2)Ir até o novo topo e colocar o "proxRRN" como sendo o topo antigo
    */
    if (tipoArquivo == 1)
    {
        int topo = -1;
        int posRRN = -1;

        fseek(BIN, 1, SEEK_SET);

        fread(&topo, sizeof(int), 1, BIN);
        fseek(BIN, 1, SEEK_SET);
        posRRN = (posicao - 182) / 97;
        fwrite(&posRRN, sizeof(int), 1, BIN);
        // printf("topo que escrevi: %d\n", posRRN);

        if (topo != -1)
        {
            fseek(BIN, posicao, SEEK_SET);
            fwrite(&removido, sizeof(char), 1, BIN);
            fwrite(&topo, sizeof(int), 1, BIN);
        }
        else
        {
            fseek(BIN, posicao, SEEK_SET);
            fwrite(&removido, sizeof(char), 1, BIN);
        }
        fseek(BIN, 178, SEEK_SET);
        int numRegRemovidos = 0;
        fread(&numRegRemovidos, sizeof(int), 1, BIN);
        numRegRemovidos++;
        fseek(BIN, 178, SEEK_SET);
        fwrite(&numRegRemovidos, sizeof(int), 1, BIN);
    }

    /*
    Lógica da lista:
    - Se o topo for -1, atualizamos ele com nosso novo registro removido.
    - Se não for -1, começamos a rodar a lista de removidos, seguindo seus offsets,
    para descobrir se o tamanho do nosso registro a ser removido é maior. Colocamos ele
    como removido antes do que for imediatamente menor e depois do que for imediatamente
    maior. Agora, temos que mudar algumas coisas: O proxOffset do que acabamos de inserir
    será o offset do removido imediatamente menor que esse. Já o anterior (o removido
    imediatamente maior) terá como proxOffset o novo que acabamos de inserir como removido.
    */

    if (tipoArquivo == 2)
    {
        // printf("posicao: %lld\n", posicao);
        long long int topo = 0;
        // int tamanhoAnterior = 0;
        int tamanho = 0;
        int proxTamanho = 0;
        // int tamanhoAtual = 0;
        // Valores de referência: o que quero inserir agora na lista de removidos
        int keySize = 0;
        long long int keyPosition = posicao;

        long long int temp = 0;
        char removido = '1';
        long long int posAnterior = -1, proxPos = -1;

        fseek(BIN, 1, SEEK_SET);

        fread(&topo, sizeof(long long int), 1, BIN);

        // Variável temporária para servir de parâmetro no meu traversal
        temp = topo;
        // printf("topo: %lld\n", topo);

        fseek(BIN, posicao, SEEK_SET);
        fwrite(&removido, 1, sizeof(char), BIN);
        // printf("removido %c\n", removido);
        //  Pegando o tamanho do registro a ser removido
        fread(&keySize, 1, sizeof(int), BIN);
        keySize += 5;
        if (topo == -1)
        {
            fseek(BIN, 1, SEEK_SET);
            fwrite(&posicao, sizeof(long long int), 1, BIN);
        }
        else
        {
            fseek(BIN, temp + 1, SEEK_SET);
            fread(&tamanho, 1, sizeof(int), BIN);
            tamanho += 5;
            fseek(BIN, 1, SEEK_SET);
            fread(&topo, 1, sizeof(long long int), BIN);

            if (keySize >= tamanho)
            {
                // printf("keysize: %d tamanho %d pos %lld\n", keySize, tamanho, posicao);
                //  topo vira a key position
                fseek(BIN, 1, SEEK_SET);
                fwrite(&temp, sizeof(long long int), 1, BIN);
                fseek(BIN, keyPosition + 5, SEEK_SET);
                // proxima posiçao vira a posiçao do antigo topo
                fwrite(&keyPosition, sizeof(long long int), 1, BIN);
                // printf("posicao: %lld \ntopo: %lld\ntemp: %lld \nkeySize %d\ntamanho %d\n\n\n", keyPosition, topo, temp, keySize, tamanho);
                //  printf("tamanho %d, keysize: %d\n\n", keySize, tamanho);
            }

            fseek(BIN, temp + 1, SEEK_SET);
            fread(&tamanho, 1, sizeof(int), BIN);
            tamanho += 5;
            fread(&proxPos, 1, sizeof(long long int), BIN);
            if (proxPos != -1)
            {
                fseek(BIN, proxPos + 1, SEEK_SET);
                fread(&proxTamanho, 1, sizeof(int), BIN);
                proxTamanho += 5;
            }

            while (proxPos != -1 && proxTamanho > keySize)
            {
                temp = proxPos;
                fseek(BIN, temp + 1, SEEK_SET);
                fread(&tamanho, 1, sizeof(int), BIN);
                tamanho += 5;
                fread(&proxPos, 1, sizeof(long long int), BIN);
                if (proxPos != -1)
                {
                    fseek(BIN, proxPos + 1, SEEK_SET);
                    fread(&proxTamanho, 1, sizeof(int), BIN);
                    proxTamanho += 5;
                }
            }
            // ao sairmos da condição, escrevemos
            fseek(BIN, keyPosition + 5, SEEK_SET);
            fwrite(&proxPos, 1, sizeof(long long int), BIN);
            fseek(BIN, temp + 5, SEEK_SET);
            fwrite(&keyPosition, 1, sizeof(long long int), BIN);
        }

        fseek(BIN, 186, SEEK_SET);
        int numRegRemovidos = 0;
        fread(&numRegRemovidos, sizeof(int), 1, BIN);
        numRegRemovidos++;
        fseek(BIN, 186, SEEK_SET);
        fwrite(&numRegRemovidos, sizeof(int), 1, BIN);
        // printf("num remov: %d\n", numRegRemovidos);
        //  printf("num removidos: %d\n", numRegRemovidos);
    }
    fseek(BIN, posicaoInicial, SEEK_SET);

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
