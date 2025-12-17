#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "question2.h"
#include "question3.h"
#include "question5.h"


int executeOneCommand(long *execute_time){

    int status;

    char bufferCommandeLine[MAX_LINE_SIZE]={0};

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

    struct timespec start = StartTime();

    if (fork() == 0){
        execlp(bufferCommandeLine,bufferCommandeLine ,NULL);
        exit(EXIT_FAILURE);
    }

    wait(&status);
    StopTime(start);
    *execute_time = GetLastExecutionTime();
    return status;
}
