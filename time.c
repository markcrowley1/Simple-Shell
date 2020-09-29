/*Mark Crowley*/

#include "myShell.h"

//Function prints prompt with date
void printPrompt(){
    //Varibales initialised to get time
    time_t basicTime;
    struct tm *info;
    char str[20], temp[5];

    //Current time is found and stored
    time(&basicTime);
    info = localtime(&basicTime);

    //String is created and printed
    //Date and time printed in blue colour
    strftime(str,80,"%d/%m %I:%M", info);
    printf("\033[1;34m[%s]\033[0m# ", str);

    return;
}
