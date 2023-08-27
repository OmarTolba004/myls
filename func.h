/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  func.h
 *  Module:  	  
 *
 *  Description:  header file for func.c
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Omar Tolba
 *	Date:		  27/8/2023
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/

/*******************************************************************************
 * Service Name: concatenatePathAndFile
 * Parameters (in):  path - char *, file - char *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: char *
 * Description: Function to print File Type And Permission
 *******************************************************************************/
char *concatenatePathAndFile(char *path, char *file);

/*******************************************************************************
 * Service Name: printlsFromStat
 * Parameters (in):  filePath - char *, file - char *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: unsigned char
 * Description: Function to print ls content using lstat
 *******************************************************************************/
unsigned char printlsFromStat(char *filePath , char * file);
