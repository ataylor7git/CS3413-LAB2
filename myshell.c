/*
The shell will not accept any arguments for the commands.
Figured that this would fine since the point is to look at forks
and processes and not shell commands. Example does not accept 
arguments and instructions didn't say that it should accept arguments.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 81

int main()
{
    char *cmd;
    int pid;
    int returnCode;
    char buffer[BUFSIZE];
    int len;

    //Enter command
    printf("Enter a command: > ");
    cmd = fgets(buffer, BUFSIZE, stdin);

    while (cmd != NULL)
    {
        pid=fork();
        if(pid!=0){// Parent process
            wait(NULL);
        } else {// Child process
            len = strlen(buffer);
            if(buffer[len-1] == '\n'){
                buffer[len-1] = '\0';
            }

            // execute the command
            returnCode = execlp(cmd, cmd, NULL);
        
            // execute when the command fails
            if(returnCode != 0){
                printf("Error executing %s.\n", cmd);
                exit(0);
            }
        }

        // Enter new Command
        printf("Enter a command: > ");
        cmd = fgets(buffer, BUFSIZE, stdin);
    }
    return EXIT_SUCCESS;
}