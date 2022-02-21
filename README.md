# inode-infos

This program helps finding out which type of file is the one mentioned as a command parameter.

Following **types** can be recognized: regular, dir, pipe, socket, char, link.

## Compile
In order to compile the program, you first need to have "C compiler" installed.
Open the directory of the program in your terminal and type one of the following commands:  ```make all```
or use the traditional way of compiling a C programm by typing:
```
gcc -Wall -pedantic -std=c11 InodeInfo.c -o InodeInfo
```

## Run
After you have compiled the program, run it by typing ``` ./InodeInfo ``` and the targeted file as a parameter.
Example:

```
./InodeInfo /etc/master.passwd
```
The expected result is **regular**.
