#include "funcoes.h"
#include "cabecalhos.h"
#include "dados.h"

// funcao de leitura dinamica
/*void readline(char* string){
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r');

    string[i]  = '\0';
}*/

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

// imprima para impressao do binario na tela
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

// void scan_quote_string(char *str) {
//
//	/*
//	*	Use essa função para ler um campo string delimitado entre aspas (").
//	*	Chame ela na hora que for ler tal campo. Por exemplo:
//	*
//	*	A entrada está da seguinte forma:
//	*		nomeDoCampo "MARIA DA SILVA"
//	*
//	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
//	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
//	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
//	*
//	*/
//
//	char R;
//
//	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...
//
//	if(R == 'N' || R == 'n') { // campo NULO
//		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
//		strcpy(str, ""); // copia string vazia
//	} else if(R == '\"') {
//		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
//			strcpy(str, "");
//		}
//		getchar(); // ignorar aspas fechando
//	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
//		str[0] = R;
//		scanf("%s", &str[1]);
//	} else { // EOF
//		strcpy(str, "");
//	}
// }
//

void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario){
    FILE *CSV = abre_CSV_leitura(nomeCSV);
    FILE *BIN = abre_bin_escrita(nomeBinario);
    copia_binario(CSV, BIN, nomeBinario, tipoArquivo);
}

char *my_str_tok(char *str, char *delims){
    static char *src = NULL;
    char *p, *ret = 0;

    if (str != NULL)
        src = str;

    if (src == NULL || *src == '\0') // Fix 1
        return NULL;

    ret = src; // Fix 2
    if ((p = strpbrk(src, delims)) != NULL)
    {
        *p = 0;
        // ret = src;                    // Unnecessary
        src = ++p;
    }
    else
        src += strlen(src);

    return ret;
}

void funcionalidade2(int tipoArq, char* nomeBinario){

    FILE* BIN = abre_bin_leitura(nomeBinario);
    cabecalho_t *cabecalho;
    dados_t *dados;
    cabecalho = inicia_cabecalho();

    if(tipoArq == 1){

        int aux = 0;
        ler_cab_arquivo(BIN, cabecalho, 1);
        if(cabecalho->proxRRN != 0){
            while(aux > cabecalho->proxRRN){
                dados = inicializa_dados();
                ler_dados_tipo1(BIN, dados);
                imprimeDados(dados, cabecalho);

                free(dados->marca);
                free(dados->modelo);
                free(dados->cidade);
                free(dados->sigla);
                //free(dados);
                aux++;
            }
        }else{
            printf("Registro inexistente\n");
            fclose(BIN);
            return;
        }
    }

    if(tipoArq == 2){

        long long int aux = 190;
        ler_cab_arquivo(BIN, cabecalho, 2);

        if(cabecalho->proxByteOffset <= aux){
            printf("Registro inexistente\n");
            fclose(BIN);
            return;
        }

        while(aux < cabecalho->proxByteOffset){
            dados = inicializa_dados();
            aux = ler_dados_tipo2(BIN, dados, aux);
            imprimeDados(dados, cabecalho);
            free(dados->marca);
            free(dados->modelo);
            free(dados->cidade);
            free(dados->sigla);
            //free(dados);
        }
    }
    free(cabecalho);
    fclose(BIN);
    return;
}

void funcionalidade4(char *nomeBinario, int RRN){

    FILE* BIN = abre_bin_leitura(nomeBinario);
    dados_t *dados;
    cabecalho_t *cabecalho;
    cabecalho = inicia_cabecalho();
    dados = inicializa_dados();
    ler_cab_arquivo(BIN, cabecalho, 1);

    if(RRN >= cabecalho->proxRRN || RRN < 0){
        printf("Registro inexistente.\n");
        fclose(BIN);
        return;
    }
    posArq(BIN, dados, RRN);
    imprimeDados(dados, cabecalho);
    fclose(BIN);
    return;
}


void copia_binario(FILE *CSV, FILE *BIN, char *nomeBinario, int tipoArquivo){
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
                }
            }
            if (contador == 4)
            {
                // printf("qtt: %s\n", token);
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
                }
            }
            if (contador == 7)
            {
                if (token != NULL)
                {
                    dados->tamanhoModelo = strlen(token);
                    dados->modelo = malloc(sizeof(char) * dados->tamanhoModelo + 1);
                    strcpy(dados->modelo, token);
                }
            }
            contador++;
        }

        int tamanhoDados = 0;
        if (tipoArquivo == 1)
        {
            escreve_dados(dados, BIN, tipoArquivo);
            cabecalho->proxRRN = cabecalho->proxRRN + 1;
        }else if(tipoArquivo == 2){
            tamanhoDados = escreve_dados(dados, BIN, tipoArquivo);
            somaDados += tamanhoDados;
            cabecalho->proxByteOffset = cabecalho->proxByteOffset + tamanhoDados;
        }
        free(dados->marca);
        free(dados->modelo);
        free(dados->cidade);
        free(dados->sigla);

        free(dados);
        free(token);
    }

    cabecalho->status = '1';
    escreve_cabecalho_arquivo(cabecalho, BIN, tipoArquivo);

    fclose(BIN);
    fclose(CSV);
    binarioNaTela(nomeBinario);
    free(cabecalho);
    // free(linha);
}

FILE *abre_CSV_leitura(char *nomeCSV){
    FILE *fp = fopen(nomeCSV, "r");
    if (fp == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(EXIT_SUCCESS);
    }

    return fp;
}

FILE *abre_bin_escrita(char *nomeBin){
    FILE *fp = fopen(nomeBin, "wb");

    if (fp == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(EXIT_SUCCESS);
    }

    return fp;
}

FILE* abre_bin_leitura(char *nomeBin){
    FILE *fb;

    if ((fb = fopen(nomeBin, "rb+")) == NULL){
        printf("Falha no processamento do arquivo.\n");
        exit(EXIT_SUCCESS);
    }

    return fb;
}

void posArq(FILE *BIN, dados_t *dados, int RRN){

    long long int aux;
    aux = 182 + (RRN*97);

    fseek(BIN, aux, SEEK_SET);
    ler_dados_tipo1(BIN, dados);
    return;
}

void imprimeDados(dados_t *dados, cabecalho_t *cabecalho){


    if(dados->removido == '1'){
        return;
    }else{
        if(dados->tamanhoMarca > 0){
            printf("%s: %s\n", cabecalho->desMarca, dados->marca);
        }else{
            printf("%s: NAO PREENCHIDO\n", cabecalho->desMarca);
        }

        if(dados->tamanhoModelo > 0){
            printf("%s: %s\n", cabecalho->desModelo, dados->modelo);
        }else{
            printf("%s: NAO PREENCHIDO\n", cabecalho->desModelo);
        }

        if(dados->ano > 0){
            printf("%s: %s\n", cabecalho->desAno, dados->ano);
        }else{
            printf("%s: NAO PREENCHIDO\n", cabecalho->desAno);
        }

        if(dados->tamanhoCidade > 0){
            printf("%s: %s\n", cabecalho->desNomeCidade, dados->cidade);
        }else{
            printf("%s: NAO PREENCHIDO\n", cabecalho->desNomeCidade);
        }

        if(dados->quantidade != -1){
            printf("%s: %s\n", cabecalho->desQuantidade, dados->quantidade);
        }else{
            printf("%s: NAO PREENCHIDO\n", cabecalho->desQuantidade);
        }
        printf("\n");
    }
    return;
}
