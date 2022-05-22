#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "funcoes.h"


int main(){
    int comando;
    char *tipoArq = (char *)malloc(sizeof(char)*10);
    char *NomeCSV = (char *)malloc(sizeof(char)*25);
    char *NomeBinario = (char *)malloc(sizeof(char)*25);

    scanf("%d", &comando);
    scanf("%s", tipoArq);
    
    int tipoArqInt;
    if(strcmp(tipoArq, "tipo1") == 0) tipoArqInt = 1;
    if(strcmp(tipoArq, "tipo2") == 0) tipoArqInt = 2;

    switch(comando){
        case 1:
        //pronta
            scanf("%s", NomeCSV);
            scanf("%s", NomeBinario);
            funcionalidade1(tipoArqInt, NomeCSV, NomeBinario);
            break;

        case 2: ;
            scanf("%s", NomeBinario);
            //printf("%s\n", NomeBinario);
            //funcionalidade2(tipoArqInt, NomeBinario);
            break;

        case 3:
            scanf("%s", NomeBinario);
            //printf("%s\n", NomeBinario);
            //funcionalidade3(tipoArqInt, NomeBinario);

            break;

        case 4:
            int RRN = 0;
            scanf("%s", NomeBinario);
            scanf("%d", &RRN);
            //printf("%s\n", NomeBinario);
            if(tipoArqInt == 2){
                printf("Falha no processamento do arquivo.\n");
                break;
            }
            //funcionalidade4(tipoArqInt, NomeBinario, RRN);
            break;

        default:
            printf("ERRO: comando invalido\n");
            break;
    }
    
    free(tipoArq);
    free(NomeCSV);
    free(NomeBinario);

    return 0;
}