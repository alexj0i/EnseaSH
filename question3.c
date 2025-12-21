#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "question3.h"

/*
 * The function exitCommandCheck(const char *cmd)
 * Checks if the user-entered command matches the "exit" command.
 * This function allows identifying an explicit request to exit the shell.
 */

int exitCommandCheck(const char *cmd){
    return strcmp(cmd, EXIT) == 0;
}

/*
 * The function void exitShell(void)
 * Properly terminates the shell execution.
 * A goodbye message is displayed before the program exits.
 * This function is called when the user types "exit"
 * or signals end-of-input with Ctrl + D.
 */

void exitShell(void) {
    write(STDOUT_FILENO, EXIT_BYEBYE, strlen(EXIT_BYEBYE));
    exit(EXIT_SUCCESS);
}
