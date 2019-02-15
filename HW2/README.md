# Getting Started
Navigate to the desired working directory

```
git clone https://github.com/cJadeLy/kernelHW.git
cd kernelHW/HW2

```
# 3.22 Shared Memory Object
## Build Instructions
if on a Windows machine

Do not attempt to build posix_shared.c, it will not work


if on a Mac:
```
gcc -o output posix_shared.c
./output 35

```
Otherwise:

```
gcc -o output posix_shared.c -lrt
./output 35
```
# 3.27 file copy
## Build Instructions

### Overview:
Copy contents of one file to another. If destination file does not exist, one will automatically be created for you

```
gcc -o [desired_name] filecopy.c
./[desired_name] [src] [dest]

```

Example using sample text files:

```
// To see file is initially empty
cat testfile2.txt

gcc -o copy filecopy.c
./copy testfile.txt testfile2.txt

// To verify copy was successfull
cat testfile2.txt
```

# Project 1 - UNIX Shell
## Build Instructions
Mac/Linux/UNIX Only!!

From `HW2` folder:

```
cd Project1
gcc -o shell shell_history.c
./shell

```
## Detail of features

To view command history type `history`

To execute most recent command type `!!`

To execute the Nth command in your command history type `!N`

*you can only access the 10 most recent commands, however, the count will continue to increment*

This means, if you enter 35 commands and then you type `history`, only the most recent 10 commands will be echoed to the screen, and they will be numbered 26 - 35

*Therefore, if attempting to execute the Nth command, it must be correctly referred to. You may want to type* `history` *to view the list of previous commands currently available*

**WARNING: As with a typical shell, the history buffer does not discriminate against invalid commands. If you attempt a bogus command, it will still be stored in history. Keep this in mind when executing `!N`**

To exit, type `exit`

# Project 2 - Linux Kernel Module for Listing Tasks
## Build Instructions - Part 1
1. Follow [these steps](http://people.westminstercollege.edu/faculty/ggagne/osc/vm/index.html) to set up your virtual environment
2. Inside of the virtual machine, run the following commands from the terminal:

From `HW2` folder:

```
cd Project2/Part1
make
sudo insmod task.ko
// to see that module loaded
lsmod | grep task*
// To see tasks from kernel log
dmesg
// compare this output to tasks in system
ps -el
// remove module
sudo rmmod task
// clear kernel log buffer
sudo dmesg -c
// to clean working directory
make clean
```
## Build Instructions - Part 2
1. Follow [these steps](http://people.westminstercollege.edu/faculty/ggagne/osc/vm/index.html) to set up your virtual environment
2. Inside of the virtual machine, run the following commands from the terminal:
From `HW2` folder:

```
cd Project2/part2
make
sudo insmod dfs.ko
// to see that module loaded
lsmod | grep dfs*
// To see tasks from kernel log
dmesg
// compare this to DFS output
ps -eLf
// remove module
sudo rmmod dfs
// clear kernel log buffer
sudo dmesg -c
// to clean working directory
make clean
```
