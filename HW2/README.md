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

# Project 1 - Simple Shell
## Build Instructions
Mac/Linux/UNIX Only!!

```
gcc -o shell shell_history.c
./shell

```
To view command history type `history`

To execute most recent command type `!!`

To execute the Nth command in your command history type `!N`

*you can only access the 10 most recent commands, however, the count will continue to increment*

This means, if you enter 35 commands and then you type `history`, only the most recent 10 commands will be echoed to the screen, but they will be numbered 26 - 35

To exit, type `exit`
