#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "question1.h"


#define WELCOME_MESSAGE "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n"
#define PROMPT_MESSAGE "enseash % "

/*
 * La fontion welcomePrompt()
 * Affiche le message d’accueil du shell lors de son lancement.
 * L’affichage est réalisé avec write afin de respecter les contraintes du projet.
*/

void welcomePrompt(){
    write(STDOUT_FILENO,WELCOME_MESSAGE,strlen(WELCOME_MESSAGE));
}

/*
 * La fonction regularPrompt()
 * Affiche le prompt simple du shell pour inviter l’utilisateur à saisir une commande.
 * En cas d’erreur lors de l’écriture sur la sortie standard, le programme est arrêté.
*/

void regularPrompt(){
    int status = write(STDOUT_FILENO,PROMPT_MESSAGE,strlen(PROMPT_MESSAGE));
    if (status == -1){
        exit(EXIT_FAILURE);
    }
}
