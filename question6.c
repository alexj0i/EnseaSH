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
 * The function int executeOneCommandComplexe(long *execute_time)
 * Reads a command entered by the user and allows execution of commands
 * containing arguments.
 * The command line is split into multiple elements to form
 * the argument array required for execution.
 * The function then executes the command, waits for it to finish,
 * and measures its execution time.
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
