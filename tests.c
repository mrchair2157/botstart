#include "main.h"
/*
  This function is to compare the two other input files and if there diffrent it will copy argv[2] into argv[1].
  I use the standard open and write over the f varients do to the fact the program does not seem to play nice with them.
*/
bool diff(const char *c, const char *r)
{
    //sets up vars, rfd and cfd will be the file discriports
    //against and run will be the comparason pointers
    //abuff and rbuf are gonna be where the files get read into.
    int cfd = 0, rfd = 0;
    char *against = NULL, *run = NULL;
    char *abuff = NULL, *rbuff = NULL;
    //gets size to alloc for the check and does a size check.
    size_t runsz = 0;
    struct stat sa;
    //if stat retruns -1 that means it failed so time to copy the file.
    if(stat(c,&sa) < 0)
        {
            return false;
        }
    runsz = sa.st_size;
    stat(r,&sa);
    //checks if the file size is diffrent so we can skip trying to check for a diffence;
    if(runsz != (unsigned long)sa.st_size)
        {
            return false;
        }
    printf("running dif.\n");
    //sets up the current bot file to be compared
    cfd = open(c, O_RDONLY);
    abuff = calloc(runsz + 5,sizeof(char));
    against = abuff;
    read(cfd,against,runsz * sizeof(char));
    //sets up the file to be read
    rfd = open(r, O_RDONLY);
    rbuff = calloc(sa.st_size + 5,sizeof(char));
    run = rbuff;
    read(rfd,run,sa.st_size * sizeof(char));

    //checks to see if the chars are the same.
    size_t count = 0;
    //state if state is retrun as false it copies the new version of the bot.
    bool state;
    for(count = 0; against[count] == run[count] && against[count] != '\0' && run[count] != '\0' ;count++);

    if (run[count] == against[count])
        {
            state = true;
        }
    else
        {
            state = false;
        }
    //frees up the current file
    free(abuff);
    close(cfd);
    //fress up the comparason file
    free(rbuff);
    close(rfd);



    printf("returning from dif.\n");
    return state;
}

