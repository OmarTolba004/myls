/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  func.c
 *  Module:  	  func 
 *
 *  Description:  source file that implemetns all needed functions 
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Omar Tolba
 *	Date:		  27/8/2023
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/**********************************************************************************************************************
 *  local function prototype
 *********************************************************************************************************************/

/*******************************************************************************
 * Service Name: getOwnerName
 * Parameters (in):  uid - uid_t
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: static char *
 * Description: Function to get file owner name
 *******************************************************************************/
static char *getOwnerName(uid_t uid);

/*******************************************************************************
 * Service Name: getOwnergroup
 * Parameters (in):  uid - uid_t
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: static char *
 * Description: Function to get file owner group
 *******************************************************************************/
static char *getOwnergroup(uid_t uid);

/*******************************************************************************
 * Service Name: insertAtLast
 * Parameters (in):  inputStr - char *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: static char *
 * Description: Function to iremove line from an end of string
 *******************************************************************************/
static char *removeNewLineFromString(char *inputStr);

/*******************************************************************************
 * Service Name: printFileTypeAndPermission
 * Parameters (in):  st_mode - mode_t, color - char *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void
 * Description: Function to print File Type And Permission
 *******************************************************************************/
static void printFileTypeAndPermission(mode_t st_mode, char *color);


/**********************************************************************************************************************
 *  FUNCTIONS IMPLEMENTATOIN
 *********************************************************************************************************************/

/*******************************************************************************
 * Service Name: concatenatePathAndFile
 * Parameters (in):  path - char *, file - char *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: char *
 * Description: Function to print File Type And Permission
 *******************************************************************************/
char *concatenatePathAndFile(char *path, char *file)
{

    unsigned int resultStrLen = strlen(path) + strlen(file) + 2; /* adding 2 for null termniator and  '/' */
    /* Dynamically allocating size for output */
    char *result = (char *)malloc(sizeof(char) * resultStrLen);
    strcpy(result, ""); /* intitallzing result to nothing*/
    strcat(result, path);
    strcat(result, "/");
    strcat(result, file);

    return result;
}

/*******************************************************************************
 * Service Name: printlsFromStat
 * Parameters (in):  filePath - char *, file - char *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: unsigned char
 * Description: Function to print ls content using lstat
 *******************************************************************************/
unsigned char printlsFromStat(char *filePath, char *file)
{
    struct stat statbuf;

    if (lstat(filePath, &statbuf) == -1)
    {
        printf("lstat Error\n");
        return -1;
    }

    /*
     *   Avaliable colors
     *   'w' --> white (default)
     *   'g' --> green (executalbe file)
     *   'b' --> blue (dir)
     */
    char color = 'w';
    printFileTypeAndPermission(statbuf.st_mode, &color);

    printf(" %ju \t", (uintmax_t)statbuf.st_nlink);
    /* Printing User and groput name*/
    printf("%s %s \t",
           getOwnerName(statbuf.st_uid), getOwnergroup(statbuf.st_gid));
    /* Printing file size*/
    printf("%jd  \t",
           (intmax_t)statbuf.st_size);

    char *myctime = ctime(&statbuf.st_ctime);
    char *myctimeEdited = removeNewLineFromString(myctime);
    printf("%s", myctimeEdited);

    if (color == 'g')
    {
        printf("\033[1;32m");
    }
    else if (color == 'b')
    {
        printf("\033[1;34m");
    }

    printf(" %s \n", file);

    /* Returnning color to white*/
    printf("\033[1;37m");
}

/*******************************************************************************
 * Service Name: getOwnerName
 * Parameters (in):  uid - uid_t
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: static char *
 * Description: Function to get file owner name
 *******************************************************************************/
static char *getOwnerName(uid_t uid)
{
    struct passwd *passwdStruct;
    passwdStruct = getpwuid(uid);
    return passwdStruct->pw_name;
}

/*******************************************************************************
 * Service Name: getOwnergroup
 * Parameters (in):  uid - uid_t
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: static char *
 * Description: Function to get file owner group
 *******************************************************************************/
static char *getOwnergroup(uid_t uid)
{
    struct group *groupStruct;
    groupStruct = getgrgid(uid);
    return groupStruct->gr_name;
}

/*******************************************************************************
 * Service Name: insertAtLast
 * Parameters (in):  inputStr - char *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: static char *
 * Description: Function to iremove line from an end of string
 *******************************************************************************/
static char *removeNewLineFromString(char *inputStr)
{
    unsigned int strSize = strlen(inputStr);
    unsigned char i = 0;
    if (strSize == 0)
    {
        printf("No input string for the function removeNewLineFromString\n");
        return NULL;
    }
    while (inputStr[i] != 0 && i < strSize)
    {
        if (inputStr[i] == '\n')
        {
            inputStr[i] = 0;
        }
        i++;
    }
    return inputStr;
}

/*******************************************************************************
 * Service Name: printFileTypeAndPermission
 * Parameters (in):  st_mode - mode_t, color - char *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void
 * Description: Function to print File Type And Permission
 *******************************************************************************/
static void printFileTypeAndPermission(mode_t st_mode, char *color)
{
    /* Printing file type*/

    switch (st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("b");
        break;
    case S_IFCHR:
        printf("c");
        break;
    case S_IFDIR:
        printf("d");
        /* Setting color*/
        *color = 'b';
        break;
    case S_IFIFO:
        printf("f");
        break;
    case S_IFLNK:
        printf("s");
        break;
    case S_IFREG:
        printf("-");
        break;
    case S_IFSOCK:
        printf("socket");
        break;
    default:
        printf("?");
        break;
    }
    printf("%s", (S_IRUSR & st_mode) ? "r" : "-");
    printf("%s", (S_IWUSR & st_mode) ? "w" : "-");
    printf("%s", (S_IXUSR & st_mode) ? "x" : "-");
    /* Setting color to green*/
    if (S_IXUSR & st_mode && ((st_mode & S_IFMT) != S_IFDIR))
        *color = 'g';

    printf("%s", (S_IRGRP & st_mode) ? "r" : "-");
    printf("%s", (S_IWGRP & st_mode) ? "w" : "-");
    printf("%s", (S_IXGRP & st_mode) ? "x" : "-");

    printf("%s", (S_IROTH & st_mode) ? "r" : "-");
    printf("%s", (S_IWOTH & st_mode) ? "w" : "-");
    printf("%s", (S_IXOTH & st_mode) ? "x" : "-");
}