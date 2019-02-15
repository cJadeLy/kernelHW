#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#define MODE 0666
#define BUF_SIZE 8192
int main(int argc, char *argv[]) {
	int in, out;
	int fds[2];

	pipe(fds);
	char buf[BUF_SIZE];
	if (argc != 3)
 	{
	 	perror("Please try again and enter two files, with the first being the one to copy, the second being the one to copy to. \n");
		exit(1);
	}
	fds[1] = open(argv[1], O_RDONLY);
	if (fds[1] < 0)
	{
		exit(2);
	}
	fds[0] = creat(argv[2], MODE);
	if (fds[0] < 0)
	{
		exit(3);
	}

	while (1)
	{
		in = read(fds[1], buf, BUF_SIZE);
		if (in <= 0)
		{
			break;
		}
			out = write(fds[0], buf, in);
			if (out <= 0)
			{
				break;
			}
	}
	close(fds[1]);
	close(fds[0]);
return 0;
}
