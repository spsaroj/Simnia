
/*
 *  * builtins.c
 *   * \author Saroj Paudel
 *    * \Header file for builtins.c
 *     */

#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>


const char* BUILTINS[] = {"cd", NULL};
const void (*FCNS[])(const strvec * cmd) = {_cd, NULL};

//function to execute cd command
void _cd(const strvec * cmd){
    if(strvec_size(*cmd) >= 3){
        printf("The cd has too many arguments");
    }
    else if(strvec_size(*cmd) == 1){
        chdir(getenv("HOME"));
    }
    else{
        if(chdir(strvec_get(*cmd, 1)) == -1){
            perror("cd");
        }
    }
}