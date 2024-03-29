/*
Trabalho 3 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main()
{
    //declaracaoo de variaveis
    int comando;
    char *tipoArq = (char *)malloc(sizeof(char) * 10);
    char *NomeCSV = (char *)malloc(sizeof(char) * 25);
    char *NomeBinario = NULL;
    NomeBinario = (char *)malloc(sizeof(char) * 25);
    char *NomeIndice = (char *)malloc(sizeof(char) * 25);
    int RRN = 0;
    int n = 0;
    int valorID = 0;
    char id[3];

    scanf("%d", &comando);
    scanf("%s", tipoArq);

    //tranformando o tipo de arquivo para um variavel int
    int tipoArqInt = 0;
    if (strcmp(tipoArq, "tipo1") == 0)
        tipoArqInt = 1;
    if (strcmp(tipoArq, "tipo2") == 0)
        tipoArqInt = 2;

    switch (comando)
    {
    //Funcao para copia do csv e escrita no binario, alem do printa binario
    case 1:
        scanf("%s", NomeCSV);
        scanf("%s", NomeBinario);
        funcionalidade1(tipoArqInt, NomeCSV, NomeBinario);
        break;

    //Funcao de print do arq binario
    case 2:
        scanf("%s", NomeBinario);
        funcionalidade2(tipoArqInt, NomeBinario);
        break;

    //Funcao de busca
    case 3:
        scanf("%s", NomeBinario);
        scanf("%d", &n);
        funcionalidade3(tipoArqInt, NomeBinario, n);
        break;

    //Funcao de "busca" por RRN
    case 4:
        scanf("%s", NomeBinario);
        scanf("%d", &RRN);
        
        if (tipoArqInt == 2)//como aceita apenas arquivos do tipo 1, existe essa verificacao
        {
            printf("Falha no processamento do arquivo.\n");
            break;
        }
        funcionalidade4(NomeBinario, RRN);
        break;

    //Funcao "Cria indices"
    case 5:
        scanf("%s", NomeBinario);
        scanf("%s", NomeIndice);
        funcionalidade5(tipoArqInt, NomeBinario, NomeIndice);
        break;

    //Funcao de busca e remocao
    case 6:
        scanf("%s", NomeBinario);
        scanf("%s", NomeIndice);
        scanf("%d", &n);
        funcionalidade6(tipoArqInt, NomeBinario, NomeIndice, n);
        break;

    //Funcao de insercao
    case 7:
        scanf("%s", NomeBinario);
        scanf("%s", NomeIndice);
        scanf("%d", &n);
        funcionalidade7(tipoArqInt, NomeBinario, NomeIndice, n);
        break;

    //Funcao de atualizacao
    case 8:
        scanf("%s", NomeBinario);
        scanf("%s", NomeIndice);
        scanf("%d", &n);
        funcionalidade8(tipoArqInt, NomeBinario, NomeIndice, n);
        break;

    case 9:
        scanf("%s", NomeBinario);
        scanf("%s", NomeIndice);
        //funcionalidade9(tipoArqInt, NomeBinario, NomeIndice);
        break;

    case 10:
        scanf("%s", NomeBinario);
        scanf("%s", NomeIndice);
        scanf("%s", id);
        scanf("%d", &valorID);
        funcionalidade10(tipoArqInt, NomeBinario, NomeIndice, valorID);
        break;

    case 11:
        scanf("%s", NomeBinario);
        scanf("%s", NomeIndice);
        scanf("%d", &n);
        //funcionalidade11(tipoArqInt, NomeBinario, NomeIndice, n);
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