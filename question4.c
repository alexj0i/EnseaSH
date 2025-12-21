#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "question4.h"

#include "question5.h"

/*
 * La fonction void augmentedPrompt(int status,long time_ms)
 * Construit et affiche le prompt du shell après l’exécution d’une commande.
 * Le prompt permet à l’utilisateur de connaître le résultat de la dernière commande,
 * en indiquant si elle s’est terminée correctement ou suite à un signal,
 * ainsi que le temps mis pour son exécution.
*/

void augmentedPrompt(int status,long time_ms){
    char buffer[64] = {0};
    sprintf(buffer, "enseash [%s:%d|%ldms] %%:", WIFEXITED(status) ? EXIT : SIGNAL,
            WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status),time_ms);
    write(STDOUT_FILENO,buffer,strlen(buffer));
}
