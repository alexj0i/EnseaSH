#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "question2.h"
#include "question3.h"
#include "question5.h"
#include "question7.h"

#define MAX_ARGS 64

/*
 * The function int executeOneCommandComplexeWithRedirection(long *execute_time)
 * Reads a command entered by the user and allows execution of commands
 * with input and/or output redirection.
 * The function parses the command line to identify files
 * used for "<" and ">" redirections.
 * The command is then executed in a child process with the redirections applied,
 * and the shell retrieves the exit status and execution time.
 */

int executeOneCommandComplexeWithRedirection(long *execute_time){

    int status;

    char bufferCommandeLine[MAX_LINE_SIZE]={0};
    char *argv[MAX_ARGS]={0};

    char *InputFile = NULL;
    char *OutputFile = NULL;

    int numberCharRead = read(STDIN_FILENO,bufferCommandeLine,MAX_LINE_SIZE);

    if (numberCharRead == 0){
        exitShell();
    }else if (numberCharRead < 0){
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
    char *token;
    int argc = 0;
    token = strtok(bufferCommandeLine, " \t");
    while (token != NULL && ArgCounter < MAX_ARGS - 1) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t");
            if (token != NULL) InputFile = token;
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t");
            if (token != NULL) OutputFile = token;
        } else {
            argv[ArgCounter++] = token;
        }
        token = strtok(NULL, " \t");
    }
    argv[ArgCounter] = NULL;

    struct timespec start = StartTime();

    if (fork() == 0) {
        if (InputFile != NULL) {
            int fd_in = open(InputFile, O_RDONLY);
            if (fd_in < 0) exit(EXIT_FAILURE);
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        if (OutputFile != NULL) {
            int fd_out = open(OutputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) exit(EXIT_FAILURE);
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        execvp(argv[0], argv);
        _exit(EXIT_FAILURE);
    }
    wait(&status);
    StopTime(start);
    *execute_time = GetLastExecutionTime();
    return status;
}
