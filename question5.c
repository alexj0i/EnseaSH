//
// Created by delayed on 17/12/2025.
//

#include <time.h>
#include <unistd.h>

#include "question5.h"

#include <stdio.h>

#define SEC_TO_MS 1000
#define NSEC_TO_MS 1000000

static long last_execution_time_ms = 0;

struct timespec StartTime() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    return start;
}

void StopTime(struct timespec start) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    last_execution_time_ms = (end.tv_sec - start.tv_sec)*SEC_TO_MS + (end.tv_nsec - start.tv_nsec)/NSEC_TO_MS;
}

long GetLastExecutionTime() {
    //printf("%d",last_execution_time_ms);
    return last_execution_time_ms;
}