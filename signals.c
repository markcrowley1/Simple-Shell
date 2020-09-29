/*Mark Crowley*/

#include "myShell.h"

//Function handles SIGINT signal
//Stops program from exiting on ctrl + C
void sigHandler(int sigNum){
    
    if(sigNum == SIGINT){
        fflush(stdout);
        printf("\n");
    }

    return;
}