/*
João Pedro Duarte Nunes
12541460
*/
#include "functions.h"
#include "commands.h"
#include <string.h>
/*
As duas primeiras funções foram fornecidas no run.codes
*/

void read_line(char* string){
    char c = 0;
    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r' && c != EOF);

    string[i]  = '\0';
}

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
}


// Substituir o lixo de memória por $
void dollars(FILE *problemFile, int length) {
    char *garbage = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++)
        garbage[i] = '$';
    
    fwrite(garbage, sizeof(char), length, problemFile);
    free(garbage);
}


// Escrever no arquivo, em ordem
void fileWrite(FILE *problemFile, names_t *ind) {

    //Aqui, escrevemos no arquivo e preenchemos o lixo com $$$.
    fwrite(ind->firstName, sizeof(char), (strlen(ind->firstName) + 1), problemFile);
    dollars(problemFile, 51 - (strlen(ind->firstName) + 1));

    fwrite(ind->lastName, sizeof(char), (strlen(ind->lastName) + 1), problemFile);
    dollars(problemFile, 51 - (strlen(ind->lastName) + 1));

    fwrite(ind->email, sizeof(char), (strlen(ind->email) + 1), problemFile);
    dollars(problemFile, 81 - (strlen(ind->email) + 1));

    fwrite(ind->nationality, sizeof(char), (strlen(ind->nationality) + 1), problemFile);
    dollars(problemFile, 51 - (strlen(ind->nationality) + 1)); 

    fwrite(&ind->age, sizeof(int), 1, problemFile);
}


char* readFile(FILE *problemFile, int length, char *string) {
    int param = fread(string, sizeof(char), length, problemFile);

    if(param == 0) {
        printf("Não foi possível ler um campo do registro\n");
        exit(0);
    }
    return string;
}

//Imprimir as informações
void output(names_t* ind) {
    printf("Firstname: %s\n", ind->firstName);
    printf("Lastname: %s\n", ind->lastName);
    printf("Email: %s\n", ind->email);
    printf("Nationality: %s\n", ind->nationality);
    printf("Age: %d\n\n", ind->age);
}