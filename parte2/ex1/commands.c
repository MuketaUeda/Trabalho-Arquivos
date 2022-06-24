/*
João Pedro Duarte Nunes
12541460
*/
#include "commands.h"
#include "functions.h"
#include<string.h>

void commandOne(char fileName[51]) {
    names_t ind;

    FILE *problemFile = fopen(fileName, "wb");
    if (problemFile == NULL) {
        printf("Falha no processamento do arquivo\n");
        exit(0);
    }

    //Número de registros
    int numReg;
    scanf("%d ", &numReg);
    int i = 0;
    while (i < numReg) {
        read_line(ind.firstName);
        read_line(ind.lastName);
        read_line(ind.email);
        read_line(ind.nationality);
        scanf("%d", &ind.age);
        fileWrite(problemFile, &ind);
        i++;
    }
    fclose(problemFile);
    binarioNaTela(fileName);
}

void commandTwo(char fileName[51]) {
    names_t ind;
    FILE *problemFile = fopen(fileName, "rb");
    if (problemFile == NULL) {
        printf("Falha no processamento do arquivo\n");
        exit(0);
    }

    char names[51];
    char email[81];
    char p;
    while (fread(&p, sizeof(char), 1, problemFile) != 0) {
        fseek(problemFile, -1, 1);

        strcpy(ind.firstName, readFile(problemFile, 51, names));
        strcpy(ind.lastName, readFile(problemFile, 51, names));
        strcpy(ind.email, readFile(problemFile, 81, email));
        strcpy(ind.nationality, readFile(problemFile, 51, names));
        fread(&ind.age, sizeof(int), 1, problemFile);
        output(&ind);
    }
    fclose(problemFile);
}

void commandThree(char fileName[51]) {
    const int offSet = (3 * 51) + 81 + sizeof(int);

    FILE *problemFile = fopen(fileName, "rb");
    if (problemFile == NULL) {
        printf("Falha no processamento do arquivo\n");
        exit(0);
    }

    int rrn;

    scanf("%i", &rrn);

    if (fseek(problemFile, rrn * offSet, 0) != 0) {
        printf("Não foi possível ler o arquivo\n");
        exit(0);
    }

    names_t person;
    char names[51], email[81];
    strcpy(person.firstName, readFile(problemFile, 51, names));
    strcpy(person.lastName, readFile(problemFile, 51, names));
    strcpy(person.email, readFile(problemFile, 81, email));
    strcpy(person.nationality, readFile(problemFile, 51, names));
    fread(&person.age, sizeof(int), 1, problemFile);
    output(&person);
}