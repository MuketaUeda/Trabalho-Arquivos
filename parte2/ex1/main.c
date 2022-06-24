/*
João Pedro Duarte Nunes
12541460
*/

#include "commands.h"
#include "functions.h"

int main()
{
    int command;
    scanf("%d ", &command);
    char file_name[51];
    read_line(file_name);

    if (command == 1)
        commandOne(file_name);
    else if (command == 2)
        commandTwo(file_name);
    else if (command == 3)
        commandThree(file_name);
    else
        printf("Invalid\n");

    return 0;
}