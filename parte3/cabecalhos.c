/*
Trabalho 3 - Organização de Arquivos - SCC0215
Gabriel Tavares Brayn Rosati - 11355831
João Pedro Duarte Nunes - 12542460
*/
#include "cabecalhos.h"

// Funcoes unificadas para os cabeçalhos do tipo 1 e do tipo 2----------------------------------------------------------
cabecalho_t *inicia_cabecalho()
{
    cabecalho_t *cabecalho = (cabecalho_t *)malloc(1 * sizeof(cabecalho_t));
    cabecalho->status = '0';
    cabecalho->topo = -1;
    strcpy(cabecalho->desc, "LISTAGEM DA FROTA DOS VEICULOS NO BRASIL");
    strcpy(cabecalho->desCodigo, "CODIGO IDENTIFICADOR: ");
    strcpy(cabecalho->desAno, "ANO DE FABRICACAO: ");
    strcpy(cabecalho->desQuantidade, "QUANTIDADE DE VEICULOS: ");
    strcpy(cabecalho->desEstado, "ESTADO: ");
    cabecalho->codNomeCidade = '0';
    strcpy(cabecalho->desNomeCidade, "NOME DA CIDADE: ");
    cabecalho->codMarca = '1';
    strcpy(cabecalho->desMarca, "MARCA DO VEICULO: ");
    cabecalho->codModelo = '2';
    strcpy(cabecalho->desModelo, "MODELO DO VEICULO: ");
    cabecalho->proxRRN = 0;
    cabecalho->proxByteOffset = 0;
    cabecalho->nroRegRemovidos = 0;

    return cabecalho;
}

cabecalhoArvoreB_t *inicia_cabecalhoArvoreB()
{
    cabecalhoArvoreB_t *cabecalhoB = (cabecalhoArvoreB_t *)malloc(1 * sizeof(cabecalhoArvoreB_t));
    cabecalhoB->status = '0';
    cabecalhoB->noRaiz = -1;
    cabecalhoB->proxRRN = 0;
    cabecalhoB->nroNos = 0;

    return cabecalhoB;
};

// funcao de escrita de cabecalho no arq binario
// Unificada para os tipo 1 e tipo 2, pois as diferenças entre ambos são bem pequenas
void escreve_cabecalho_arquivo(cabecalho_t *cabecalho, FILE *fp, int tipo)
{
    fseek(fp, 0, SEEK_SET);

    //  Escrever no arquivo, *em ordem*, usando como base cada o numero de bytes de cada informacao
    fwrite(&cabecalho->status, sizeof(char), 1, fp);
    if (tipo == 1)
        fwrite(&cabecalho->topo, sizeof(int), 1, fp);
    if (tipo == 2)
        fwrite(&cabecalho->topo, sizeof(long long int), 1, fp);

    fwrite(cabecalho->desc, sizeof(char), 40, fp);
    fwrite(cabecalho->desCodigo, sizeof(char), 22, fp);
    fwrite(cabecalho->desAno, sizeof(char), 19, fp);
    fwrite(cabecalho->desQuantidade, sizeof(char), 24, fp);
    fwrite(cabecalho->desEstado, sizeof(char), 8, fp);
    fwrite(&cabecalho->codNomeCidade, sizeof(char), 1, fp);
    fwrite(cabecalho->desNomeCidade, sizeof(char), 16, fp);
    fwrite(&cabecalho->codMarca, sizeof(char), 1, fp);
    fwrite(cabecalho->desMarca, sizeof(char), 18, fp);
    fwrite(&cabecalho->codModelo, sizeof(char), 1, fp);
    fwrite(cabecalho->desModelo, sizeof(char), 19, fp);

    if (tipo == 1)
        fwrite(&cabecalho->proxRRN, sizeof(int), 1, fp);
    if (tipo == 2)
        fwrite(&cabecalho->proxByteOffset, sizeof(long long int), 1, fp);

    fwrite(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp);

    return;
}

// Funções para o tipo 1 e 2 foram unificadas
// Ler informações referentes ao cabeçalho de um arquivo
void ler_cab_arquivo(FILE *fp, cabecalho_t *cabecalho, int tipo)
{
    fseek(fp, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, fp);
    if (tipo == 1)
    {
        fread(&cabecalho->topo, sizeof(int), 1, fp);

        // Pula 169 bytes, referentes aos códigos e descrições
        fseek(fp, 169, SEEK_CUR);
        fread(&cabecalho->proxRRN, sizeof(int), 1, fp);
    }
    else if (tipo == 2)
    {
        fread(&cabecalho->topo, sizeof(long long int), 1, fp);
        //printf("topo cab: %lld\n", cabecalho->topo);

        // Pula 169 bytes, referentes aos códigos e descrições
        fseek(fp, 169, SEEK_CUR);
        fread(&cabecalho->proxByteOffset, sizeof(long long int), 1, fp);
    }

    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp);

    if (cabecalho->status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(fp);
        exit(0);
    }

    return;
}

//funcao de leitura do cabecalho da avB
void lerCabecalhoArvoreB(FILE *arquivo, cabecalhoArvoreB_t *cabecalho){
	fread(&cabecalho->status, sizeof(char), 1, arquivo);
	fread(&cabecalho->noRaiz, sizeof(int), 1, arquivo);
	fread(&cabecalho->proxRRN, sizeof(int), 1, arquivo);
    fread(&cabecalho->nroNos, sizeof(int), 1, arquivo);

    fseek(arquivo, 45, SEEK_SET);

	if(cabecalho->status == '0')
	{ //Se o arquivo estiver corrompido, informa e para a execução
		printf("Falha no processamento do arquivo.");
		exit(0);
	}
}

//escreve o cabecalho da arvoreB e do lixo especificado
void escreverCabecalhoArvoreB(FILE *arquivo, cabecalhoArvoreB_t cabecalho, int tipo){
	fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
	fwrite(&cabecalho.noRaiz, sizeof(int), 1, arquivo);
	fwrite(&cabecalho.proxRRN, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.nroNos, sizeof(int), 1, arquivo);
	
    int qttLixo;
    if(tipo == 1){
        qttLixo = 32;
    }
    if(tipo ==2){
        qttLixo = 44;
    }
    char *lixo = (char *)malloc(qttLixo * sizeof(char));
    for (int i = 0; i < qttLixo; i++)
    {
        lixo[i] = '$';
    }
    fwrite(lixo, sizeof(char), qttLixo, arquivo);
    free(lixo);

}