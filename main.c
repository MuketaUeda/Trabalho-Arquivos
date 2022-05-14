#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){
    
    int comando;
    char* tipoArq = malloc(sizeof(char)*10);

    scanf("%d", &comando);
    scanf("%s", &tipoArq);
    

    switch(comando){

        case 1:
            char* NomeCSV = malloc(sizeof(char)*25);
            scanf("%s", &NomeCSV);
            char* NomeBinario = malloc(sizeof(char)*25);
            scanf("%s", &NomeBinario);
            //funcionalidade1(tipoArq, NomeCSV, NomeBinario);
            break;

        case 2:
            char* NomeBinario = malloc(sizeof(char)*25);
            scanf("%s", &NomeBinario);
            //funcionalidade2(tipoArq, NomeBinario);
            break;

        case 3:
            char* NomeBinario = malloc(sizeof(char)*25);
            scanf("%s", &NomeBinario);
            //funcionalidade3(tipoArq, NomeBinario);
            break;

        case 4:
            char* NomeBinario = malloc(sizeof(char)*25);
            scanf("%s", &NomeBinario);
            //funcionalidade4(tipoArq, NomeBinario);
            break;

        default:
            printf("ERRO: comando invalido");
            break;
    }

    free(tipoArq);
    free(NomeCSV);
    free(NomeBinario);

    return 0;
}