#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char curr_dir[] = ".";
    char *path = NULL;
    /* making the default dir is the current dir*/
    if (argc == 1)
        path = curr_dir;
    else
        path = argv[1];

    DIR *dirptr = opendir(path);

    /* Files counter*/
    int filesCount = 0;
    /* dirctory entry variable*/
    struct dirent* directoryEntry;
    /* Looping over dirptr*/
    while ((directoryEntry = readdir(dirptr)) != NULL)
    {
        if(strcmp(directoryEntry->d_name,".") == 0 || strcmp(directoryEntry->d_name,"..")==0) continue;
        filesCount++;
    }

    printf("filesCount is %d \n", filesCount);

    return 0;
}