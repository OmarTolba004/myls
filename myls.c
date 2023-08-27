/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  myls.c
 *  Module:  	  myls
 *
 *  Description:  source file for my ls
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Omar Tolba
 *	Date:		  27/8/2023
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "func.h"
#include <stdlib.h>

/**********************************************************************************************************************
 *  MAIN FUNCTION
 *********************************************************************************************************************/
int main(int argc, char *argv[])
{
    char curr_dir[] = ".";
    char *path = NULL;
    /* making the default dir is the current dir*/
    if (argc == 1)
        path = curr_dir;
    else
        path = argv[1];

    /* Open the directory */
    DIR *dirptr = opendir(path);

    /* Files counter*/
    int filesCount = 0;
    /* dirctory entry variable*/
    struct dirent *directoryEntry;
    /* Looping over dirptr*/

    char *filePath;
    while ((directoryEntry = readdir(dirptr)) != NULL)
    {

        filePath = concatenatePathAndFile(path, directoryEntry->d_name);
        printlsFromStat(filePath,directoryEntry->d_name);
        
        filesCount++;
        free(filePath);
    }
    return 0;
}
