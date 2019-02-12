// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #define MAX_LINE 80 /* The maximum length command */
// pid_t pid;
// int command(int flag)
// {
// 	char argcs[100]; /* command line arguments */
//
//
// int flag2;
// 		printf("enter some stuff \n");
// 	//fgets(argcs, 80, stdin);
// 	scanf("%s \n", argcs);
// 	// Returns first token
// 	char* token = strtok(argcs, " ");
// 	    // Keep printing tokens while one of the
// 	    // delimiters present in str[].
//
// 	    while (flag) {
// 		//	fflush(stdout);
// 	        printf("%s\n", token);
// 			fflush(stdout);
//
// 	        token = strtok(NULL, " ");
// 		// 	if(strcmp(token, "&") == 0)
// 		// 	{
// 		// 	printf("ampersand!\n");
// 		// 	fflush(stdout);
// 		// 	flag2 = 3;
// 		// }
// 		// 	if(strcmp(token, "exit") == 0)
// 		// 	flag2 = 2;
// 		//
// 		// 	if(strcmp(token, "\n") == 0)
// 		// 	{
// 		// 		break;
// 		//
// 		//
// 		// }
// 		// return 0;
// 	}
// 		return flag2;
// }
// int main(int argc, const char **args)
// {
//
//
// if( command(1) == 0 || command(1) == 3)
// {
// 	command(1);
// }
// int should_run = 1; /* flag to determine when to exit program */
// // while (should_run) {
// // printf("osh>"); fflush(stdout);
//
//
// /**
// * After reading user input, the steps are:
// * (1) fork a child process using fork()
// * (2) the child process will invoke execvp()
// * (3) if command included &, parent will invoke wait() */
// // pid = fork();
// // execvp(argcs[0], argcs);
// // should_run = argcs[2];
// //    }
// return 0;
// }
//
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include<errno.h>
#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

void execArgs(char** parsed)
{
	//printf("0 %s , 1 %s, 2  %s\n", parsed[0], parsed[1], parsed[2]);

    // Forking a child
    pid_t pid = fork();

    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        execvp(parsed[0], parsed);
			printf("failure to execute because %s\n", strerror(errno));

        exit(0);

    } else {
        // waiting for child to terminate
        wait(NULL);
        return;
    }
}

void parseSpace(char* str, char** parsed)
{
    int i;

    for (i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
		{
			printf("count = %d.. about to execute\n", i);
			execArgs(parsed);
			break;
		}
		printf("%s\n", parsed[i]);
        if (strlen(parsed[i]) == 0)
            i--;
    }
}
int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];

    int execFlag = 0;


    while (1) {
printf("osh> ");
        // take input
fgets(inputString, MAXCOM, stdin);
        // process
		inputString[strlen(inputString)-1]= '\0';
		if(strcmp(inputString, "exit") == 0)
		break;
		parseSpace(inputString, parsedArgs);

            //execArgs(parsedArgs);


    }
    return 0;
}
// https://brennan.io/2015/01/16/write-a-shell-in-c/
// https://www.youtube.com/watch?v=z4LEuxMGGs8&t=117s
// http://cs.boisestate.edu/~amit/teaching/297/notes/files-and-processes-handout.pdf
