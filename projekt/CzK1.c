
#include "funkcje.h"
#include "funkcje.c"


int main()
{

    printf("Czujnik butelek");
    char butelka;


    sem_t* sem = sem_open(SEMNAME, 0);
    if(sem == SEM_FAILED)
    {
        printf("\nCzK1 - semafor nieotwarty\n");
        exit(1);
    }

    int* addr = SharedMemoryOpen();
    if(*addr == -1)
    {
        printf("\nCzK1 - blad shared memory\n");
    }

    int state = 0;//sharedmemory[4]
    int start = 0;//sharedmemory[0]
    int temp = 0;//sharedmemory[1]


    printf("\nStan czujnika: ");

    while(1)
    {



    //czyszczenie bufora stdin
    __fpurge(stdin);

    if( temp == TEMPWORK_FLAG && start == 1 && (butelka = getc(stdin)) == '1')
    {
        state = 1;
        printf("\nStan czujnika: ");
    }
    else if(temp == TEMPWORK_FLAG && start == 1)
    {
        state = 0;
        printf("\nStan czujnika: ");
    }
    else
        state = 0;

    //pobierz info czy ma dzialac
    sem_wait(sem);
    start = addr[0];
    temp = addr[1];
    sem_post(sem);

    if(temp == TEMPWORK_FLAG && start == 1)
    {
        //wyslij stan
        sem_wait(sem);
        addr[4] = state;
        sem_post(sem);
    }




    if(start == -1)
    {
        sem_wait(sem);
        addr[4] = -1;
        sem_post(sem);
        break;
    }

    usleep(100000);

    }

    sem_close(sem);
    return 0;
}






