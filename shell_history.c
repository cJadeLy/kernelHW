#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include<errno.h>

#define MAX_LIST 80

void executeCommand(char** parsed)
{
	//printf("0 %s , 1 %s, 2  %s\n", parsed[0], parsed[1], parsed[2]);

    // Forking a child process to execute commands
    pid_t pid = fork();

    if (pid < 0) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        execvp(parsed[0], parsed);
			printf("failure to execute because %s\n", strerror(errno));
			printf("string was %s\n", parsed[0]);

        exit(0);

    } else {
        // waiting for child to terminate
        wait(NULL);
        return;
    }
}


void parse(char* str, char** parsed)
{
    int i;

    for (i = 0; i < MAX_LIST; i++)
	{
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
		{
			executeCommand(parsed);
			break;
		}

	//	printf("%s\n", parsed[i]);
        if (strlen(parsed[i]) == 0)
		{
			i--;
		}

    }
	return;
}
void executeFromHistory(char** args,  int command_index, char buffer[MAX_LIST][MAX_LIST])
{

	char *parsed_command[MAX_LIST];
	 printf(" looking at command (%d) is string: %s\n",command_index, buffer[command_index]);


	   strcpy(*args,buffer[command_index]);
		 printf("most recent command (%d) is string: %s\n",command_index , args[0]);
	     parse(*args, parsed_command);


}
int valid_index(int valid, int range)
{
	if(valid >= 1 && valid < range)
	return 1;

	return 0;
}
int main()
{
    char full_command[MAX_LIST], *parsed_command[MAX_LIST];
	char history[MAX_LIST][MAX_LIST], *history_buffer[MAX_LIST];

    int history_buffer_index = 1, print_index = 0;


    while (1) {
printf("osh> ");
        // Read in user input
fgets(full_command, MAX_LIST, stdin);
// Replace newline with NULL
full_command[strlen(full_command)-1]= '\0';
printf("full command is %s\n", full_command);
		// Deal with exit command here, not a "real" command
		if(strcmp(full_command, "exit") == 0)
		{

				strcpy(history[history_buffer_index] ,full_command);
				break;
		}


		if(strcmp(full_command, "!!") == 0)
		{

			if(valid_index(history_buffer_index - 1, history_buffer_index))
			{
				strcpy(history[history_buffer_index], history[history_buffer_index - 1]);
				history_buffer_index++;
				executeFromHistory(history_buffer, history_buffer_index - 1, history);
			}
			else
			{
				printf("No commands in history\n");
			}
		}else if(strncmp(full_command, "!", 1) == 0)
		{
			print_index  = atoi(&full_command[1]);
			if(valid_index(print_index, history_buffer_index))
			{
				strcpy(history[history_buffer_index], history[print_index]);
				executeFromHistory(history_buffer, print_index, history);
			}
			else
			{
				printf("No such command in history\n");
			}
		}else
		{
			// Add full command to history before parsing & executing
			strcpy(history[history_buffer_index] ,full_command);
			// Only go to next index of history array if user still entering commands
			history_buffer_index ++;
			// Parse out commands and in this function we will call a function that calls execvp()
			parse(full_command, parsed_command);
		}


		//printf("copied %s to index %d of history array. \n", history[history_buffer_index], history_buffer_index);





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
