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

void funcionalidade1(int tipoArquivo, char *nomeCSV, char *nomeBinario)
{
    FILE *CSV = abre_CSV_leitura(nomeCSV);
    FILE *BIN = abre_bin_escrita(nomeBinario);

    switch (tipoArquivo)
    {
    case 1:
        copia_binario1(CSV, BIN);
        fclose(BIN);
        fclose(CSV);
        binarioNaTela(nomeBinario);
        break;

    case 2:

        break;
    }
}

char *my_str_tok(char *string, char *sep)
{
    static char *src = NULL;
    char *p, *ret = 0;

    if (string != NULL)
        src = string;

    if (src == NULL)
        return NULL;

    if ((p = strpbrk(src, sep)) != NULL)
    {
        *p = 0;
        ret = src;
        src = ++p;
    }
    else if (*src)
    {
        ret = src;
        src = NULL;
    }

    return ret;
}

void copia_binario1(FILE *CSV, FILE *BIN)
{
    cabecalhoTipo1_t *cabecalho = inicia_cab_tipo1();
    char *linha = NULL;
    escreve_cabecalho1_arquivo(cabecalho, BIN);
    int isEof = 0;

    // Linha1 indica o cabeçalho do CSV, que não queremos.
    char *linha1 = read_line(CSV, &isEof);
    free(linha1);

    dadosTipo1_t *dados = inicializa_dados_tipo1();
    while (isEof == 0)
    {
        linha = read_line(CSV, &isEof);

        char *token = my_str_tok(linha, ",");
        if (token != NULL)
        {
            dados->id = atoi(token);
        }
        int contador = 2;

        while (token != NULL)
        {
            token = my_str_tok(NULL, ",");
            if (contador == 2)
            {
                //printf("ano: %s\n", token);
                dados->ano = atoi(token);
            }
            if (contador == 3)
            {
               // printf("cidade: %s\n", token);
                dados->tamanhoCidade = strlen(token);
                dados->cidade = malloc(sizeof(char) * dados->tamanhoCidade + 1);
                strcpy(dados->cidade, token);
            }
            if (contador == 4)
            {
                //printf("qtd: %s\n", token);
                dados->quantidade = atoi(token);
            }
            if (contador == 5)
            {
                //printf("sigla: %s\n", token);
                strcpy(dados->sigla, token);
            }
            if (contador == 6)
            {
                //printf("marca: %s\n", token);
                dados->tamanhoMarca = strlen(token);
                dados->marca = malloc(sizeof(char) * dados->tamanhoMarca + 1);
                strcpy(dados->marca, token);
            }
            if (contador == 7)
            {
                //printf("modelo: %s\n", token);
                // printf("len: %lu", strlen(token));
                if (token != NULL)
                {
                    dados->tamanhoModelo = strlen(token);
                    dados->modelo = malloc(sizeof(char) * dados->tamanhoModelo + 1);
                    strcpy(dados->modelo, token);
                }
            }
            contador++;
        }
        escreve_dados_tipo1(dados, BIN);
    }
    free(linha);
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
    FILE *fp;

    if ((fp = fopen(nomeBin, "wb+")) == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        exit(EXIT_SUCCESS);
    }

    return fp;
}
