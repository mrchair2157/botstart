#include "main.h"

//file
//while run is true the program will do it's thing
bool run = true;
//ints that are to who proses identification, once is for killing the program if ^C is hit twice
int pid = -1, pidc = -1, once = 0;


//todo Make a function to read strings as commands to pasue resume and stop the proram.
int main(int argc, char **argv)
{

    if(argc < 3)
    { 
        printf("Needs input file and comparison file.\n");
        return -1;
    }
    struct stat sa;
    if(stat(argv[2],&sa) < 0)
        {
            printf("%s does not exsist\n",argv[2]);
            return -1;
        }

    //starts the bot
    if((pid = fork()) == 0)
        {
            if(0 > execlp("python3","python3", argv[1]/*,">>","log.txt"*/,NULL))
                {
                    printf("program failed to start.\n");
                    return -1;
                }
        }
    //main loop
    bool started = true;
    while(run == true)
    {
            //pauses at dif
            if((diff(argv[1], argv[2])) == false)
                {
                    //kill the bot, get previous fork pid
                    //the fork record the pid of the fork and exec python3 bot
                    printf("they are different, reloading bot.\n");

                    kill(pid,9);
                    started = false;

                    //copys the bot
                    if((pidc = fork()) == 0)
                        {

                            printf("starting copy.\n");
                            if( 0 > execlp("cp","cp","-r",argv[2], argv[1],NULL))
                                {
                                    printf("cp failed.\n");
                                    return -1;
                                }
                            else
                                {
                                    return 0;
                                }

                        }
                    printf("waiting.\n");
                    waitpid(pidc,NULL,0);
                    //restarts the bot
                    if((pid = fork()) == 0)
                        {
                            if(0 > execlp("python3","python3", argv[1]/*,">>","log.txt"*/,NULL) && started == false)
                                {
                                    printf("program failed to start.\n");
                                    return -1;
                                }
                            else
                                {
                                    printf("program started.\n");
                                    started = true;
                                    return 0;
                                }

                        }


                }
        sleep(30);
        started = true;

    }

    

    return 0;
}
