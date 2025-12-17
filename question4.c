#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "question4.h"

#include "question5.h"


void augmentedPrompt(int status,long time_ms){
    char buffer[64] = {0};
    sprintf(buffer, "enseash [%s:%d|%ldms] %%:", WIFEXITED(status) ? EXIT : SIGNAL,
            WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status),time_ms);
    write(STDOUT_FILENO,buffer,strlen(buffer));
}
