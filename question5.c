#include <time.h>
#include <unistd.h>
#include <stdio.h>

#include "question5.h"

#define SEC_TO_MS 1000
#define NSEC_TO_MS 1000000

static long last_execution_time_ms = 0;

/* La fonction struct timespec StartTime()
 * Récupère et retourne l’instant de départ avant l’exécution d’une commande.
 * Cette fonction est utilisée pour pouvoir mesurer la durée d’exécution
 * d’un programme lancé par le shell.
*/

struct timespec StartTime() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    return start;
}

/*
 * La fonction void StopTime(struct timespec start)
 * Calcule le temps d’exécution écoulé depuis l’instant de départ.
 * La durée est convertie en millisecondes et stockée dans une variable statique.
 */

void StopTime(struct timespec start) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    last_execution_time_ms = (end.tv_sec - start.tv_sec)*SEC_TO_MS + (end.tv_nsec - start.tv_nsec)/NSEC_TO_MS;
}

/*
 * La fonction long GetLastExecutionTime()
 * Retourne le temps d’exécution de la dernière commande lancée par le shell.
 * Cette valeur est utilisée lors de l’affichage du prompt enrichi.
 */

long GetLastExecutionTime() {
    //printf("%d",last_execution_time_ms);
    return last_execution_time_ms;
}
