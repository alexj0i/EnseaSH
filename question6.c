#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "question2.h"
#include "question3.h"
#include "question5.h"
#include "question6.h"

#define MAX_ARGS 64

/*
 * La fonction int executeOneCommandComplexe(long *execute_time)
 * Lit une commande saisie par l’utilisateur et permet l’exécution de commandes
 * contenant des arguments.
 * La ligne de commande est découpée en plusieurs éléments afin de former
 * le tableau d’arguments nécessaire à l’exécution du programme.
 * La fonction exécute ensuite la commande, attend sa fin et mesure son temps d’exécution.
*/


int executeOneCommandComplexe(long *execute_time){

    int status;

    char bufferCommandeLine[MAX_LINE_SIZE]={0};
    char *argv[MAX_ARGS]={0};

    int numberCharRead = read(STDIN_FILENO,bufferCommandeLine,MAX_LINE_SIZE);

    if (numberCharRead == 0){
        exitShell();
    } else if (numberCharRead < 0){
        return 0;
    }

    bufferCommandeLine[numberCharRead-1] = '\0';

    if (strlen(bufferCommandeLine) == 0){
        return 0;
    }

    if (exitCommandCheck(bufferCommandeLine)){
        exitShell();
    }

    int ArgCounter = 0;
    char *token = strtok(bufferCommandeLine," ");

    while (token != NULL)
    {
        argv[ArgCounter++] = token;
        token = strtok(NULL," ");
    }
    argv[ArgCounter]=NULL;

    struct timespec start = StartTime();

    if (fork() == 0){
        execvp(argv[0],argv);
        exit(EXIT_FAILURE);
    }

    wait(&status);
    StopTime(start);
    *execute_time = GetLastExecutionTime();
    return status;
}
