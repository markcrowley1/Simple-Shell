/*Mark Crowley*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

void printPrompt();

void executeCommand(char *command, char **args, int argCount);

void sigHandler(int sigNum);