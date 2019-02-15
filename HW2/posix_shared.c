#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define NAME "/some_shared_memory"
// struct to share
struct shared {
	int numbers[4096];
};

pid_t child_pid;

// collatz logic
static int next_consumed(int collatz_num)
{
  if(collatz_num % 2 == 0)
  {
    return collatz_num / 2;
  }else
  {
    return 3 * collatz_num + 1;
  }
}

int main(int argc, const char **args)
{
  int num = atoi(args[1]);
// created shared object
  int shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666 );
  ftruncate(shm_fd, sizeof(struct shared));
  struct shared *obj;
  // map it
 obj= mmap(0, sizeof(struct shared), PROT_WRITE, MAP_SHARED, shm_fd, 0);
 obj->numbers[0] = num;

  size_t sequence_length = 1;
  do
  {
    num = next_consumed(num);
    obj->numbers[sequence_length] = num;
    ++sequence_length;
}while( num != 1);
  obj->numbers[sequence_length] = 0;
// child process can read shared memory
 	 if ((child_pid = fork()) == 0)
 	 {
		 // debug print statement
		 // printf("This is the child process. My pid is %d and my parent's id is %d.\n", child_pid, getppid());
 		   int fd = shm_open(NAME, O_RDONLY, 0666);

 		   ftruncate(fd, sizeof(struct shared));
		   struct shared *obj;
		   int index = 0;
 		  obj = mmap(0, sizeof(struct shared), PROT_READ, MAP_SHARED, fd, 0);

 	   while(obj->numbers[index]!= 0)
 	   {
 			  printf("%d\n", obj->numbers[index]);
 		   ++index;
 	   }
 	  shm_unlink(NAME);
 	 }
 	 else
	 {
		 // debug statement to make sure parent is really waiting for child to exit
	 	//printf("This is the parent process. I'm waiting..My pid is %d \n",  getpid());
 	 	wait(NULL);
 	 }
  return 0;
}
