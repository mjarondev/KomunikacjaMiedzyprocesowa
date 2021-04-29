
#include "funkcje.h"
#include "funkcje.c"


int main(int argc, char *argv[])
{
    char napelnienie;
    int name;
    if(argc >= 2)
    {
        name = atoi(argv[1]);
    }
    else
        name = 1;

    printf("Napelnienie rozdrabniacza nr. %d\n", name);



    sem_t* sem = sem_open(SEMNAME, 0);
    if(sem == SEM_FAILED)
    {
        printf("\nRozdrabniacz%d - semafor nieotwarty\n", name);
        exit(1);
    }

    int* addr = SharedMemoryOpen();
    if(*addr == -1)
    {
        printf("\nRozdrabniacz%d - blad shared memory\n", name);
    }


    int start = 0;//sharedmemory[0]
    int state = 0;//sharedmemory[7/8]
    int temp = 0;//sharedmemory[1]


    printf("Stan napelnienia rozdrabniacza%d: ", name);


    while(1)
    {

        __fpurge(stdin);
        if( temp == TEMPWORK_FLAG && start == 1)
        {
            switch(napelnienie = getc(stdin))
            {
            case '1':
                state = 1;
                break;
            case '2':
                state = 2;
                break;
            case '3':
                state = 3;
                break;
            case '4':
                state = 4;
                break;
            default:
                state = 0;
                break;
            }
        printf("Stan napelnienia rozdrabniacza%d: ", name);
        }

        sem_wait(sem);
        start = addr[0];
        temp = addr[1];
        sem_post(sem);

        if(temp == TEMPWORK_FLAG && start == 1)
        {
            //wyslij stan
            sem_wait(sem);
            addr[name+6] = state;
            sem_post(sem);
        }

        if(start == -1)
        {
            sem_wait(sem);
            addr[name+6] = -1;
            sem_post(sem);
            break;
        }

        usleep(100000);


    }

    sem_close(sem);
    return 0;
}
