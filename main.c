#include <stdlib.h>
#include "question1.h"
#include "question2.h"
#include "question3.h"

int main(void){
    int status;

    welcomePrompt();
    while (1){
        augmentedPrompt(status);
        status = executeOneCommand();
    }
    return EXIT_SUCCESS;
}