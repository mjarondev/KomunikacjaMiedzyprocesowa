#include "funkcje.h"
#include "funkcje.c"


int main(int argc, char *argv[])
{
    char butelka;
    int name;
    if(argc >= 2)
    {
        name = atoi(argv[1]);
    }
    else
        name = 1;

    printf("Licznik butelek nr. %d\n", name);



    sem_t* sem = sem_open(SEMNAME, 0);
    if(sem == SEM_FAILED)
    {
        printf("\nLicznik%d - semafor nieotwarty\n", name);
        exit(1);
    }

    int* addr = SharedMemoryOpen();
    if(*addr == -1)
    {
        printf("\nLicznik%d - blad shared memory\n", name);
    }


    int start = 0;//sharedmemory[0]
    int state = 0;//sharedmemory[5/6]
    int temp = 0;//sharedmemory[1]

    printf("Stan Licznika%d: ", name);

    while(1)
    {

        __fpurge(stdin);

        if( temp == TEMPWORK_FLAG && start == 1 && (butelka = getc(stdin)) == '1')
        {
            state = 1;
            printf("\nStan Licznika%d: ", name);
        }
        else if(temp == TEMPWORK_FLAG && start == 1)
        {
            state = 0;
            printf("\nStan Licznika%d: ", name);
        }
        else
            state = 0;

        sem_wait(sem);
        start = addr[0];
        temp = addr[1];
        sem_post(sem);

        if(temp == TEMPWORK_FLAG && start == 1)
        {
            //wyslij stan
            sem_wait(sem);
            addr[name+4] = state;
            sem_post(sem);
        }




        if(start == -1)
        {
            sem_wait(sem);
            addr[name+4] = -1;
            sem_post(sem);
            break;
        }

        usleep(100000);
    }


    sem_close(sem);
    return 0;
}

