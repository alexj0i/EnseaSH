#include <time.h>
#include <unistd.h>
#include <stdio.h>

#include "question5.h"

#define SEC_TO_MS 1000
#define NSEC_TO_MS 1000000

static long last_execution_time_ms = 0;

/*
 * The function struct timespec StartTime()
 * Retrieves and returns the starting time before a command execution.
 * This function is used to measure the duration of a program launched by the shell.
 */

struct timespec StartTime() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    return start;
}

/*
 * The function void StopTime(struct timespec start)
 * Calculates the elapsed execution time since the starting time.
 * The duration is converted to milliseconds and stored in a static variable.
 */

void StopTime(struct timespec start) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    last_execution_time_ms = (end.tv_sec - start.tv_sec)*SEC_TO_MS + (end.tv_nsec - start.tv_nsec)/NSEC_TO_MS;
}

/*
 * The function long GetLastExecutionTime()
 * Returns the execution time of the last command run by the shell.
 * This value is used when displaying the enriched prompt.
 */

long GetLastExecutionTime() {
    return last_execution_time_ms;
}
