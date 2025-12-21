#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "question3.h"

/*
 * La fonction exitCommandCheck(const char *cmd)
 * Vérifie si la commande saisie par l’utilisateur correspond à la commande "exit".
 * Cette fonction permet d’identifier une demande explicite de sortie du shell.
*/

int exitCommandCheck(const char *cmd){
    return strcmp(cmd, EXIT) == 0;
}

/*
 * La fonction void exitShell(void)
 * Termine proprement l’exécution du shell.
 * Un message de sortie est affiché avant l’arrêt du programme.
 * Cette fonction est appelée lorsque l’utilisateur tape "exit"
 * ou lorsqu’il signale la fin de la saisie avec Ctrl + D.
 */

void exitShell(void) {
    write(STDOUT_FILENO, EXIT_BYEBYE, strlen(EXIT_BYEBYE));
    exit(EXIT_SUCCESS);
}
