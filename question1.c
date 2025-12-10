#include "question1.h"

#include <string.h>

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

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



//ajouter define pour exit signal etc
void augmentedPrompt(int status){
    char buffer[16] = {0};
    sprintf(buffer,"enseash [%s:%d] %%", WIFEXITED(status)?exit:signal, WIFEXITED(status) ? WEXITSTATUS(status): WTERMSIG(status) );
    write(STDOUT_FILENO,buffer,strlen(buffer));
}