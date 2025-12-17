#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "question1.h"


#define WELCOME_MESSAGE "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n"
#define PROMPT_MESSAGE "enseash % "

void welcomePrompt(){

    write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE));

}

void regularPrompt(){

    int status = write(STDOUT_FILENO,PROMPT_MESSAGE,strlen(PROMPT_MESSAGE));
    if (status == -1){
        exit(EXIT_FAILURE);
    }
}
