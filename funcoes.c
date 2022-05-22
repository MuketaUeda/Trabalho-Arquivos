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
<<<<<<< HEAD

char *read_line(FILE *stream, int *isEof)
{
    char *linha = NULL;
    int tamanhoLinha = 0;

    do
    {
        linha = realloc(linha, ++tamanhoLinha * sizeof(char));
        linha[tamanhoLinha - 1] = fgetc(stream);
    } while (linha[tamanhoLinha - 1] != EOF  && linha[tamanhoLinha - 1] != '\n');
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
        
=======
/*
char *read_line(FILE *fp, int *isEof){
    char c = 0;
    int size = 0;
    char *string = NULL;
    int i = 0;

    c = (char) fgetc(fp);

    while(c != '\n' && c != '\r' && c != EOF){
        string = (char *)realloc(string, ++size * sizeof(char));
        string[i] = c;
        i++;
        c = (char) fgetc(fp);
>>>>>>> 83ac9efa6e756ffba6e5e07e5431258c8f86d2a8
    }



    return linha;
}
*/

char* read_line(FILE *stream, int *has_EOF) {
    char c;
    unsigned long int n_chars = 0;

    char* line = NULL;

    while ((c = fgetc(stream)) == '\n' || (c == '\r'));

    if (c != EOF) ungetc(c, stream);

    do {
        c = fgetc(stream);

        if (n_chars % 50 == 0) {
            int new_size = (n_chars / 50 + 1) * 50 + 1;

            line = (char*)realloc(line, (unsigned long)new_size * sizeof(char));
        }

        n_chars++;

        if (c != '\n' && c != '\r' && c != EOF) {
            *(line + n_chars - 1) = c;

            *has_EOF = 0;
        } else {
            *(line + n_chars - 1) = '\0';

<<<<<<< HEAD

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
=======
            if (c == EOF) *has_EOF = 1;
        }
    } while (c != '\n' && c != '\r' && c != EOF);

    line = (char*)realloc(line, (unsigned long)(n_chars + 1));

    return line;
}
//imprima para impressao do binario na tela
void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
>>>>>>> 83ac9efa6e756ffba6e5e07e5431258c8f86d2a8
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

void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario)
{
    FILE *CSV = abre_CSV_leitura(nomeCSV);
    FILE *BIN = abre_bin_escrita(nomeBinario);

    switch (tipoArquivo)
    {
    case 1:
        copia_binario1(CSV, BIN, nomeBinario);

        break;

    case 2:

        break;
    }
}

char *my_str_tok(char *str, char *delims)
{
    static char  *src = NULL;
    char  *p,  *ret = 0;

    if (str != NULL)
        src = str;

    if (src == NULL || *src == '\0')    // Fix 1
        return NULL;

    ret = src;                          // Fix 2
    if ((p = strpbrk(src, delims)) != NULL)
    {
        *p  = 0;
        //ret = src;                    // Unnecessary
        src = ++p;
    }
    else
        src += strlen(src);

    return ret;
}

<<<<<<< HEAD
void copia_binario1(FILE *CSV, FILE *BIN, char *nomeBinario)
{
=======
//ERRO NO STRTOK
void copia_binario1(FILE *CSV, FILE *BIN){
>>>>>>> 83ac9efa6e756ffba6e5e07e5431258c8f86d2a8
    cabecalhoTipo1_t *cabecalho = inicia_cab_tipo1();
    escreve_cabecalho1_arquivo(cabecalho, BIN);
    int isEof = 0;

    // Linha1 indica o cabeçalho do CSV, que não queremos.
    char *linha1 = read_line(CSV, &isEof);
    free(linha1);
<<<<<<< HEAD

    // char *linha = NULL;
    while (isEof == 0)
    {
        dadosTipo1_t *dados = inicializa_dados_tipo1();
        char *linha = read_line(CSV, &isEof);
        char *token = my_str_tok(linha, ",");

        if(isEof == 1 && strlen(linha) == 0){
            free(linha);
            break;
        }

        // if(linha)
        // free(linha);
        // printf("id: %s\n", token);
        if (token != NULL)
            dados->id = atoi(token);
        int contador = 2;

        while (token != NULL)
        {
            token = my_str_tok(NULL, ",");
            if (contador == 2)
            {
                // printf("ano: %s\n", token);
                if (strlen(token) > 0)
                    dados->ano = atoi(token);
            }
            if (contador == 3)
            {
                if (token != NULL)
                {
                    //printf("cidade: %lu\n", strlen(token));
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
            {
                // printf("sigla: %s\n", token);
                strcpy(dados->sigla, token);
            }
            if (contador == 6)
            {
                if (token != NULL)
                {
                    //printf("marca: %lu\n", strlen(token));
                    dados->tamanhoMarca = strlen(token);
                    dados->marca = malloc(sizeof(char) * dados->tamanhoMarca + 1);
                    strcpy(dados->marca, token);
                    //dados->marca = token;
                }
            }
            if (contador == 7)
            {
                // printf("modelo: %s\n", token);
                if (token != NULL)
                {
                    // printf("modelo: %s\n", token);
                    // printf("len: %lu\n", strlen(token));
                    dados->tamanhoModelo = strlen(token);
                    dados->modelo = malloc(sizeof(char) * dados->tamanhoModelo + 1);
                    strcpy(dados->modelo, token);
                }
            }
=======
    
    dadosTipo1_t *dados = inicializa_dados_tipo1();
    while(isEof == 0){
		linha = read_line(CSV, &isEof);
        printf("linha:    %s\n\n\n", linha);
        
        char *token = strtok(linha, ",");
        printf("id: %s\n\n\n", token);
        dados->id = atoi(token);
        int contador = 2;

        while(token != NULL){
            token = strtok(NULL, ",");
			if(contador == 2){
                printf("ano: %s\n\n\n", token);
                if(strlen(token) > 0){
                dados->ano = atoi(token);
                }
			}
            //ERRO AQUI
			if(contador == 3){
                printf("cidade: %s\n\n\n", token);
                    dados->tamanhoCidade = strlen(token);
                    dados->cidade = malloc(sizeof(char)*dados->tamanhoCidade+1);
                    //memset(dados->cidade, 0, dados->tamanhoCidade+1);
                    strcpy(dados->cidade, token);
			}
			if(contador == 4){
                printf("quantidade: %s\n\n\n", token);
                if(strlen(token) > 0){
				    dados->quantidade = atoi(token);
                    printf("voce esta aqui2\n");
                }
                printf("voce esta aqui2\n");
			}
			if(contador == 5){
                printf("sigla: %s\n\n\n", token);
				strcpy(dados->sigla, token);
			}
			if(contador == 6){
                printf("marca: %s\n\n\n", token);
				dados->tamanhoMarca = strlen(token);
				dados->marca = malloc(sizeof(char)*dados->tamanhoMarca+1);
                memset(dados->marca, 0, dados->tamanhoMarca+1);
				strcpy(dados->marca, token);
			}
			if(contador == 7){
                printf("modelo: %s\n\n\n", token);
				dados->tamanhoModelo = strlen(token);
				dados->modelo = malloc(sizeof(char)*dados->tamanhoModelo+1);
                memset(dados->modelo, 0, dados->tamanhoModelo+1);
				strcpy(dados->modelo, token);
			}
>>>>>>> 83ac9efa6e756ffba6e5e07e5431258c8f86d2a8
            contador++;
        }
        // printf("token %s\n", token);

        escreve_dados_tipo1(dados, BIN);
        cabecalho->proxRRN = cabecalho->proxRRN + 1;
        free(dados->marca);
        free(dados->modelo);
        free(dados->cidade);
        free(dados->sigla);

        free(dados);
        free(token);
    }
    cabecalho->status = 1;
    escreve_cabecalho1_arquivo(cabecalho, BIN);

    fclose(BIN);
    fclose(CSV);
    binarioNaTela(nomeBinario);
    free(cabecalho);
    // free(linha);
}

FILE *abre_CSV_leitura(char *nomeCSV)
{
    FILE *fp = fopen(nomeCSV, "r");
    if (fp == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(EXIT_SUCCESS);
    }

    return fp;
}

FILE *abre_bin_escrita(char *nomeBin)
{
    FILE *fp = fopen(nomeBin, "wb");

    if (fp == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(EXIT_SUCCESS);
    }

    return fp;
}