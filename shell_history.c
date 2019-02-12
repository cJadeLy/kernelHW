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


			execArgs(parsed);
			break;
		}

		printf("%s\n", parsed[i]);
        if (strlen(parsed[i]) == 0)
            i--;
    }
	return;
}
int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
	char history[MAXLIST][MAXCOM];

    int history_buffer_index = 1, print_index = 0;


    while (1) {
printf("osh> ");
        // take input
fgets(inputString, MAXCOM, stdin);
        // process
		inputString[strlen(inputString)-1]= '\0';
		strcpy(history[history_buffer_index] ,inputString);
		printf("copied %s to index %d of history array. \n", history[history_buffer_index], history_buffer_index);
		printf("right now, this is the previous str %s  (index %d of history array). \n", history[history_buffer_index - 1], history_buffer_index - 1);

		if(strcmp(inputString, "exit") == 0)
			break;
		history_buffer_index ++;
		parseSpace(inputString, parsedArgs);
    }
//	printf("history_buffer_index returned with a value of %d\n", history_buffer_index);
printf("contents in history array: \n");
for(print_index = history_buffer_index; print_index > 0; print_index--)
printf("%d %s\n", print_index, history[print_index]);
    return 0;
}
// https://brennan.io/2015/01/16/write-a-shell-in-c/
// https://www.youtube.com/watch?v=z4LEuxMGGs8&t=117s
// http://cs.boisestate.edu/~amit/teaching/297/notes/files-and-processes-handout.pdf
