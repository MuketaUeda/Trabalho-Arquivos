#include "cabecalhos.h"


//Funcoes para os arquivos Tipo1------------------------------------------------------------------
cabecalhoTipo1_t *inicia_cab_tipo1(){
    cabecalhoTipo1_t *cabecalho = (cabecalhoTipo1_t *)malloc(1 * sizeof(cabecalhoTipo1_t));
    cabecalho->status = '0';
    cabecalho->topo = -1;
    memcpy(cabecalho->desc, "LISTAGEM DA FROTA DOS VEICULOS NO BRASIL", 40);
    memcpy(cabecalho->desCodigo, "CODIGO IDENTIFICADOR: ", 22);
    memcpy(cabecalho->desAno, "ANO DE FABRICACAO: ", 19);
    memcpy(cabecalho->desQuantidade, "QUANTIDADE DE VEICULOS: ", 24);
    memcpy(cabecalho->desEstado, "ESTADO: ", 8);
    cabecalho->codNome = '0';
    memcpy(cabecalho->desNome, "NOME DA CIDADE: ", 16);
    cabecalho->codMarca = '1';
    memcpy(cabecalho->desMarca, "MARCA DO VEICULO: ", 18);
    cabecalho->codModelo = '2';
    memcpy(cabecalho->desModelo, "MODELO DO VEICULO: ", 19);
    cabecalho->proxRRN = 0;
    cabecalho->nroRegRemovidos = 0;


    return cabecalho;
}

void escreve_cabecalho1_arquivo(cabecalhoTipo1_t *cabecalho, FILE *fp){
    fseek(fp, 0, SEEK_SET);
    char st = '0';
    //Escrever no arquivo, *em ordem*, usando como base cada o numero de bytes de cada informacao
    fwrite(&st, sizeof(char), 1, fp);
    fwrite(&cabecalho->status, sizeof(char),1, fp);
    fwrite(&cabecalho->topo, sizeof(int),1, fp);
    fwrite(cabecalho->desc, sizeof(char), 40, fp);
    fwrite(cabecalho->desCodigo, sizeof(char), 22, fp);
    fwrite(cabecalho->desAno, sizeof(char), 19, fp);
    fwrite(cabecalho->desQuantidade, sizeof(char), 24, fp);
    fwrite(cabecalho->desEstado, sizeof(char), 8, fp);
    fwrite(&cabecalho->codNome, sizeof(char), 1, fp);
    fwrite(cabecalho->desNome, sizeof(char), 16, fp);
    fwrite(&cabecalho->codMarca, sizeof(char), 1, fp);
    fwrite(cabecalho->desMarca, sizeof(char), 18, fp);
    fwrite(&cabecalho->codModelo, sizeof(char), 1, fp);
    fwrite(cabecalho->desModelo, sizeof(char), 19, fp);
    fwrite(&cabecalho->proxRRN, sizeof(int), 1, fp);
    fwrite(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp);

    return;
}

//Ler informações referentes ao cabeçalho 1 de um arquivo
void ler_cab_tipo1_arquivo(FILE *fp, cabecalhoTipo1_t *cabecalho){
    fseek(fp, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, fp);
    fread(&cabecalho->topo, sizeof(int), 1, fp);

    //Pula 169 bytes, referentes aos códigos e descrições
    fseek(fp, 169, SEEK_CUR);
    fread(&cabecalho->proxRRN, sizeof(int), 1, fp);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp);

    return;
}


//Funcoes para os arquivos de Tipo2-----------------------------------------------------------
cabecalhoTipo2_t *inicia_cab_tipo2(){
    cabecalhoTipo2_t *cabecalho = (cabecalhoTipo2_t *)malloc(1 * sizeof(cabecalhoTipo2_t));
    cabecalho->status = '0';
    cabecalho->topo = -1;
    memcpy(cabecalho->desc, "LISTAGEM DA FROTA DOS VEICULOS NO BRASIL", 41);
    memcpy(cabecalho->desCodigo, "CODIGO IDENTIFICADOR: ", 23);
    memcpy(cabecalho->desAno, "ANO DE FABRICACAO: ", 20);
    memcpy(cabecalho->desQuantidade, "QUANTIDADE DE VEICULOS: ", 25);
    memcpy(cabecalho->desEstado, "ESTADO: ", 9);
    cabecalho->codNome = '0';
    memcpy(cabecalho->desNome, "NOME DA CIDADE: ", 17);
    cabecalho->codMarca = '1';
    memcpy(cabecalho->desMarca, "MARCA DO VEICULO: ", 19);
    cabecalho->codModelo = '2';
    memcpy(cabecalho->desModelo, "MODELO DO VEICULO: ", 20);
    cabecalho->proxByteOffset = 0;
    cabecalho->nroRegRemovidos = 0;


    return cabecalho;
}

void escreve_cabecalhoTipo2_arquivo(cabecalhoTipo2_t *cabecalho, FILE *fp){
    fseek(fp, 0, SEEK_SET);
    //Escrever no arquivo, *em ordem*, usando como base cada o numero de bytes de cada informacao

    fwrite(&cabecalho->status, sizeof(char), 1, fp);
    fwrite(&cabecalho->topo, sizeof(long long int),1, fp);
    fwrite(&cabecalho->desc, sizeof(char), 40, fp);
    fwrite(&cabecalho->desCodigo, sizeof(char), 22, fp);
    fwrite(&cabecalho->desAno, sizeof(char), 19, fp);
    fwrite(&cabecalho->desQuantidade, sizeof(char), 24, fp);
    fwrite(&cabecalho->desEstado, sizeof(char), 8, fp);
    fwrite(&cabecalho->codNome, sizeof(char), 1, fp);
    fwrite(&cabecalho->desNome, sizeof(char), 16, fp);
    fwrite(&cabecalho->codMarca, sizeof(char), 1, fp);
    fwrite(&cabecalho->desMarca, sizeof(char), 18, fp);
    fwrite(&cabecalho->codModelo, sizeof(char), 1, fp);
    fwrite(&cabecalho->desModelo, sizeof(char), 17, fp);
    fwrite(&cabecalho->proxByteOffset, sizeof(long long int), 1, fp);
    fwrite(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp);

    return;
}

//Ler informações referentes ao cabeçalho 1 de um arquivo
void ler_cab_tipo2_arquivo(FILE *fp, cabecalhoTipo2_t *cabecalho){
    fseek(fp, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, fp);
    fread(&cabecalho->topo, sizeof(char), 1, fp);

    //Pula 169 bytes, referentes aos códigos e descrições
    fseek(fp, 169, SEEK_CUR);
    fread(&cabecalho->proxByteOffset, sizeof(char), 1, fp);
    fread(&cabecalho->nroRegRemovidos, sizeof(char), 1, fp);

    return;
}

void destroi_cabecalho1(cabecalhoTipo1_t *cabecalho){
    if(cabecalho)
        free(cabecalho);
}
void destroi_cabecalho2(cabecalhoTipo2_t *cabecalho){
    if(cabecalho)
        free(cabecalho);
}