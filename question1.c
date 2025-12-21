#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "question1.h"


#define WELCOME_MESSAGE "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n"
#define PROMPT_MESSAGE "enseash % "

/*
 * The function welcomePrompt()
 * Displays the shell welcome message when it starts.
 * The output is done using write() to comply with project constraints.
*/

void welcomePrompt(){
    write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE));
}

/*
 * The function regularPrompt()
 * Displays the simple shell prompt to invite the user to enter a command.
 * If an error occurs while writing to the standard output, the program exits.
 */

void regularPrompt(){
    int status = write(STDOUT_FILENO,PROMPT_MESSAGE,strlen(PROMPT_MESSAGE));
    if (status == -1){
        exit(EXIT_FAILURE);
    }
}
