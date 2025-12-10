#include "question2.h"

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int executeOneCommand(){

    char bufferCommandeLine[MAX_LINE_SIZE]={0};

    int numberCharRead = read(STDIN_FILENO,bufferCommandeLine,MAX_LINE_SIZE);

    int status;

    bufferCommandeLine[numberCharRead-1] = 0;


    if (fork() == 0){
        execlp(bufferCommandeLine,bufferCommandeLine ,NULL);
        exit(EXIT_FAILURE);
    }

    wait(&status);

    return status;
}
