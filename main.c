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
        //status = executeOneCommand(&execute_time);
        //status = executeOneCommandComplexe(&execute_time);
        status = executeOneCommandComplexeWithRedirection(&execute_time);
    }
    return EXIT_SUCCESS;
}
