/*Mark Crowley*/

//This file contains function neccessary to execute user commands

#include "myShell.h"

//Function handles arguments from user and executes command
void executeCommand(char *command, char **args, int argCount){
    int i, flag = 0, flagPoint;
    int saved_stdout;

    //Redirect for stout to file
    if(strcmp(command, "echo") == 0){

        //Checks args for ">" signalling output to file
        for(i = 1; i < argCount; i++){
            if(strcmp(args[i], ">") == 0){
                flag = 1;
                flagPoint = i;//Registers position of ">"
                break;
            }
        }

        //If ">" is found
        if(flag == 1){
            //Arg after ">" taken as filename
            char *fileName = args[flagPoint + 1];

            //Copy of stdout file descriptor made
            saved_stdout = dup(1);

            //File is opened for writing
            //File descriptor is copied to 1 with dup2()
            int f = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            dup2(f, 1);

            //Correct args are writte to file
            for(i = 1; i < flagPoint; i++){
                printf("%s ", args[i]);
            }

            printf("\n");

            //File is closed
            close(f);
            
            //File descriptor closed
            //Done to ensure program stops writing to stdout & returns to prompt
            dup2(saved_stdout, 1);
            close(saved_stdout);
        }

    }

    //Access to execvp function
    if(strcmp(command, "cd") != 0 && flag == 0){
        pid_t child_pid;
        int childStatus;

        //Child is created
        child_pid = fork();

            //Child executes execvp
            if(child_pid == 0){
                //No return if execvp is successful
                execvp(command, args);

                //Child returns if there is an error
                //Error message printed and child exits
                perror("Problem: ");
                printf("Unknown command: %s\n", command);
                exit(0);
            }
            else{
                //Parent waits for child
                wait(&childStatus);
            }
    }
    //If user enters cd command
    else if(strcmp(command, "cd") == 0){
        int ret;

        //To navigate to ~ directory enter cd 
        if(args[1] == NULL) args[1] = getenv("HOME");

        //Shell changes directory
        ret = chdir(args[1]);
        //Path is printed
        if(ret == 0)printf("%s\n", getcwd(NULL, 0));

        //If directory cannot be accessed print error
        else if(ret != 0){
            char errorMsg[50];
            strcat(errorMsg, "cd: ");
            strcat(errorMsg,  args[1]);
            perror(errorMsg);
        }
        
    }

    return;
}
