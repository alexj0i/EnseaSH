#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "question3.h"


int exitCommandCheck(const char *cmd){
    return strcmp(cmd, EXIT) == 0;
}

void exitShell(void) {
    write(STDOUT_FILENO, EXIT_BYEBYE, strlen(EXIT_BYEBYE));
    exit(EXIT_SUCCESS);
}
