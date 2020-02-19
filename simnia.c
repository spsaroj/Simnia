
/*
 *  * simnia.c
 *   * \author Saroj Paudel
 *    * \Header file for simnia.c
 *     */

#include "strvec.h"
#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//asks for the command
void prompt()
{
	char host[50];
	gethostname(host, 50);
	printf("\033[1;32m%s@%s \033[1;36m$\033[0m ", getlogin(), host);
}

//reads the command provided by the user
void read_cmd(strvec * cmd)
{
	char * buffer = calloc(256, sizeof(char*));
	size_t buffsize = 256;
	int read = getline(&buffer, &buffsize, stdin);
	// make sure it's empty
	strvec_free(cmd);
	char * ptr = strtok(buffer, " \n");
	while (ptr)
	{
		strvec_push(cmd, ptr);
		ptr = strtok(NULL, " \n");
	}
	free(buffer);
	return;
}

//executes the command as per given by the user
void exec_cmd(const strvec * cmd)
{
	int i = 0;
	//this is for cd command
	while (BUILTINS[i]){
		if(strcmp(BUILTINS[i], strvec_get(*cmd, 0)) == 0){
			FCNS[i](cmd);
			return;
		}
		i++;
	}

	//creates process
    int cpid = fork();
    if (cpid == 0){
        if (execvp(strvec_get(*cmd, 0), cmd -> _vec) == -1){
            perror(strvec_get(*cmd, 0));
            exit(errno);
        }
        else{
            printf("There was error in fork.");
        }
    }
    else{
        int status;
        pid_t wpid;

        do {
            wpid = waitpid(cpid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

//main function which will call all the functions
int main(int argc, char* argv[])
{
	strvec cmd;
	strvec_init(&cmd);
	do {
		prompt();
		read_cmd(&cmd);
		exec_cmd(&cmd);
	} while (strcmp(strvec_get(cmd, 0), "exit") != 0);
	strvec_free(&cmd);
	return 0;
}
