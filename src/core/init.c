#include "init.h"
#include "prompt.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

//optimisation => fscanf function and "%s"
/***********************************************************************************************
*    init all the system via the db encrypted file.modify by removing or adding system
*    data in the db file modify also the value of the integer ret by the number of system
*    data present on the system and the "%s" in the fscanf function.
************************************************************************************************/

#define DB_FILE "file.db"

int init_user_info(void){
    //get the user info from prompt
    //decrypt the user info
    //store the user info in the dbfile
    return 0;
}

int init (void){
    //open the database file
    errno = 0;
    int fd = open("file.db",O_RDONLY,S_IRUSR);

    if(errno == ENOENT){
        //file not exist, create it
        fd = open("file.db",O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if(fd == -1){
            perror("Error creating " DB_FILE);
            return EXIT_FAILURE;
        }
        //init the user infos for the first time
        init_user_info();

    } else if(fd == -1){
        perror("Error opening " DB_FILE);
        return EXIT_FAILURE;
    }

    //initialization
    int ret =  fscanf(fd,  "%s"
                            "" 
                            "%s");
                    
    if (ret != 2) {
        perror("Error reading from " DB_FILE);
        close(fd);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}