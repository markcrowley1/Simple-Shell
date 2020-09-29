/*Mark Crowley*/

/*This program is an implementation of a simple shell.
  Program reads from stdin using getline.
  Program exits without error when EOF is received (Ctrl + D).
  
  SIGINT is caught and handled by function. Prompt is not printed immediately,
  enter key must be pressed.
  It will still work immediately as method of killing previous commands e.g. sleep.

  There is a limit to the length of string a user can input at once.

  In this implementtion of step 5, the user must enter the command echo,
  and include > in input to write to a file.
  */
#include "myShell.h"

int parseInput(char *str, char **tokens, int length);

int main(){
    //Handling User input
    //---------------------
    int argCount = 0;
    char *input, *command, **tokens;
    size_t inputSize = 40;
    int characters;

    //Memory allocated for input string
    input = (char*)malloc(inputSize * sizeof(char));

    //Handles errors allocating memory
    if(input == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
    //---------------------

    //Handling ^C signal
    //See sigHandler function in signals.c
    signal(SIGINT, sigHandler);

    //Main Program loop
    while(1){  
        printPrompt();

        //User input is read from stdin
        //Number of characters is recorded
        characters = getline(&input, &inputSize, stdin);

        //Loop breaks if Ctrl + D is pressed
        //Program will exit
        if(characters == EOF){
            printf("\n");
            break;
        }

        //If statement ensures program will not break when '\n' entered by user
        if(characters > 1){

            //Memory allocated for user args
            tokens = malloc(sizeof(char*));

            //Inut parsed for args
            argCount = parseInput(input, tokens, characters);
            command = tokens[0];

            //Command is executed
            executeCommand(command, tokens, argCount);
        }
    }

    return 0;
}

//Function to parse string input by user into different arguments
//Returns number of arguments input by user
int parseInput(char *str, char **tokens, int length){
    int i = 0;

    //Overwriting \n in string
    str[length - 1] = '\0';

    //Strtok used to seperate string into args
    //deliminator - " " - at each space new arg
    char *tempStr = strtok(str, " ");

    while(tempStr != NULL){
        tokens[i] = tempStr;

        i++;
        tokens = realloc(tokens, (i + 1) * sizeof(char *));
        tempStr = strtok(NULL, " ");
    }

    //Ensures that final element is null
    //Necessary while using execvp
    tokens[i] = NULL;

    return i;
}
