/*  
    Author:     Yaman Aljazairi
    Compile:    gcc -Wall -pedantic -std=c11 InodeInfo.c -o InodeInfo
                or by using makefile --> make all
    Run:        ./InodeInfo

    Data to check: /dev/ada0 /bin/sh /usr/bin/tar /var/spool /etc/master.passwd /tmp/.X11-unix/X0
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/param.h>      //if FREEBSD endif
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pwd.h>


int main(int argc, char  *argv[])
{
    struct stat stOb;
    struct passwd * pID;
    
    if(argc <2 ){

        printf("Enter name(s) of the file(s) to be checked in further arguments!\n");
        exit (EXIT_FAILURE);
    }
    else if (stat(argv[1], &stOb) == -1){     // Verify existence of the file

        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    printf("\n\n");

    for(int i=1; i<argc; ++i){              // Read command line arguments starting from the second one
       
        lstat(argv[i], &stOb);
        pID= getpwuid(stOb.st_uid);

        char file_Type[20];

        /**** File types****/
        if (S_ISREG(stOb.st_mode))
        {
            strcpy(file_Type, "regular");
        }
        else if (S_ISDIR(stOb.st_mode))
        {
            strcpy(file_Type, "dir");
        }
        else if (S_ISFIFO(stOb.st_mode))
        {
            strcpy(file_Type, "pipe");
        }
        else if (S_ISCHR(stOb.st_mode))
        {
            strcpy(file_Type, "char");
        }
        else if (S_ISLNK(stOb.st_mode))
        {
            strcpy(file_Type, "link");
        }
        else if (S_ISSOCK(stOb.st_mode))        // Sockets can only be known in FreeBSD operating systems
        {
            strcpy(file_Type, "socket");
        }
        else printf("Unknown type!\n");

        /***** UserID & GroupID *****/
        printf("Filename:\t\t %s\n", argv[i]);
        printf("Filetype:\t\t %s\n", file_Type);
        printf("User-ID:\t\t %d\n", pID->pw_uid);
        printf("Group-ID:\t\t %d\n", pID->pw_gid);
        
        /* 2.Variant: USER_ID and GROUP_ID through stat_stOb!!

          printf("User-ID:\t\t %d\n", stOb.st_uid);
          printf("Group-ID:\t\t %d\n", stOb.st_gid);
        */

        printf("Name of the user:\t %s\n", pID->pw_name);     // pwd.h and getpwid()
        printf("Permissions:\t\t %o\n", stOb.st_mode);       // Access bit in octal system
        printf("Last access:\t\t %.20s %s %s", ctime(&stOb.st_atime), tzname[1],ctime(&stOb.st_atime)+20);       // Time of last access
        printf("Last Inode change:\t %.20s %s %s", ctime(&stOb.st_ctime), tzname[1],ctime(&stOb.st_atime)+20);
        printf("Last file change:\t %.20s %s %s", ctime(&stOb.st_mtime), tzname[1], ctime(&stOb.st_atime)+20);     

        #ifdef __FreeBSD__
        //printf("Creaton date: %i\n", birthtime (stOb));
        printf("File created:\t\t %.20s %s %s", ctime(&stOb.st_birthtime), tzname[1], ctime(&stOb.st_atime)+20); // only FreeBSD stores the time of file creation
        #endif

        printf("--------\n\n");
    }
    exit(EXIT_SUCCESS);
}
