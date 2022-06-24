/*
João Pedro Duarte Nunes
12541460
*/
#ifndef COMMANDS_H
#define COMMANDS_H

#include<stdio.h>
#include<stdlib.h>

typedef struct names{
    char firstName[51];
    char lastName[51];
    char nationality[51];
    char email[81];
    int age;
} names_t;

void commandOne(char fileName[51]);
void commandTwo(char fileName[51]);
void commandThree(char fileName[51]);
#endif