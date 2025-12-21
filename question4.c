#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "question4.h"
#include "question5.h"

/*
 * The function void augmentedPrompt(int status, long time_ms)
 * Constructs and displays the shell prompt after a command execution.
 * The prompt shows the result of the last command, indicating whether it
 * finished normally or was terminated by a signal, and its execution time.
 */

void augmentedPrompt(int status,long time_ms){
    char buffer[64] = {0};
    sprintf(buffer, "enseash [%s:%d|%ldms] %%:", WIFEXITED(status) ? EXIT : SIGNAL,
            WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status),time_ms);
    write(STDOUT_FILENO,buffer,strlen(buffer));
}
