#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include<errno.h>

#define MAX_LIST 80
// All that is left to do is execute the command (as long as fork doesn't fail!)
void executeCommand(char** parsed)
{
    // Forking a child process to execute commands
    pid_t pid = fork();

    if (pid < 0) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if(execvp(parsed[0], parsed) < 0)
		{
			printf("failure to execute because %s\n", strerror(errno));
			printf("string was %s\n", parsed[0]);
		}


        exit(0);

    } else {
        // waiting for child to terminate
        wait(NULL);
        return;
    }
}
// prepare a command to be executed by separating each word
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
		// Don't process the empty string
        if (strlen(parsed[i]) == 0)
		{
			i--;
		}

    }
	return;
}
// Makes sure a specific command from the history buffer is executed
void executeFromHistory(char** args,  int command_index, char buffer[MAX_LIST][MAX_LIST])
{
	char *parsed_command[MAX_LIST];
	 //printf(" looking at command (%d) is string: %s\n",command_index, buffer[command_index]);
	strcpy(*args,buffer[command_index]);
		// printf("most recent command (%d) is string: %s\n",command_index , args[0]);
	parse(*args, parsed_command);
}
// Checks to make sure there is a valid command from the history buffer to execute
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

    int history_buffer_index = 1, print_index = 0, should_run = 1;


	while (should_run)
	{
		printf("osh> ");
		// Read in user input
		fgets(full_command, MAX_LIST, stdin);
		// Replace newline with NULL
		full_command[strlen(full_command)-1]= '\0';
		// Deal with exit command here, not a "real" command
		if(strcmp(full_command, "exit") == 0)
		{
				strcpy(history[history_buffer_index] ,full_command);
				break;
		}
		if(strcmp(full_command, "!!") == 0)
		{	// if there is a previous command, add it to the most recent index of the history buffer and execute it
			if(valid_index(history_buffer_index - 1, history_buffer_index))
			{
				strcpy(history[history_buffer_index], history[history_buffer_index - 1]);
				history_buffer_index++;
				executeFromHistory(history_buffer, history_buffer_index - 1, history);
			}else
				{
					printf("No commands in history\n");
				}
		}else if(strncmp(full_command, "!", 1) == 0)
		{
			// determine the Nth command to execute
			print_index  = atoi(&full_command[1]);
			// execute if it is a valid index
			if(valid_index(print_index, history_buffer_index))
			{
				strcpy(history[history_buffer_index], history[print_index]);
				executeFromHistory(history_buffer, print_index, history);
			}else
				{
					printf("No such command in history\n");
				}
		}else if(strcmp(full_command, "history") == 0)
		{
			if(history_buffer_index > 10)
			{
				// the current history index is empty, waiting for a new command to fill the spot
				history_buffer_index--;
				for(print_index = history_buffer_index; print_index > (history_buffer_index - 10); print_index--)
				printf("%d %s\n", print_index, history[print_index]);

				// ready for new command again
				history_buffer_index++;

			}else if(history_buffer_index <= 1)
			{
				printf("No commands in history\n");
			}else
				{
					// the current history index is empty, waiting for a new command to fill the spot
					history_buffer_index--;
					for(print_index = history_buffer_index; print_index > 0; print_index--)
					printf("%d %s\n", print_index, history[print_index]);
					// ready for new command again
					history_buffer_index++;

				}

		}else
		{
			// Add full command to history before parsing & executing
			strcpy(history[history_buffer_index] ,full_command);
			// Go to next index of history array for entering more commands
			history_buffer_index ++;
			// Prepare for execution
			parse(full_command, parsed_command);
		}
    }
		// Debug
		// printf("contents in history array: \n");
		// for(print_index = history_buffer_index; print_index > 0; print_index--)
		// printf("%d %s\n", print_index, history[print_index]);
    return 0;
}
