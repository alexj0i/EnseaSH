/*
 * TP de Synthèse - ENSEA in the Shell
 * Auteurs : Alexian PREVOST, Iprahim TURGUT
 * Date   : 17/12/2025
 *
 * Description :
 *   Micro-shell ENSEASH permettant l’exécution de commandes UNIX,
 *   avec affichage du code de retour ou du signal, du temps d’exécution,
 *   et gestion des redirections d’entrée et sortie.
*/

#include <stdlib.h>

#include "question1.h"
#include "question2.h"
#include "question4.h"
#include "question5.h"
#include "question6.h"
#include "question7.h"


int main(void){
    int status ;
    long execute_time = 0;

    welcomePrompt();
    regularPrompt();
    while (1){
        augmentedPrompt(status,GetLastExecutionTime());
        status = executeOneCommandComplexeWithRedirection(&execute_time);
    }
    return EXIT_SUCCESS;
}
