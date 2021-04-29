#include "funkcje.h"
#include "funkcje.c"

#define ROZMIAR 4

int main(int argc, char *argv[])
{
    int name;
    if(argc >= 2)
    {
        name = atoi(argv[1]);
    }
    else
        name = 1;

    printf("Czujnik temperatury nr. %d", name);

    int workFlag = 1 << (name-1);


    int* addr = SharedMemoryOpen();
    sem_t* sem = sem_open(SEMNAME, 0);
    if(sem == SEM_FAILED)
    {
        printf("\nTemp%d - semafor nieotwarty\n", name);
        exit(1);
    }

    int temp = 0;//sharedmemory[3]
    int allowWork = 0;//sharedmemory[1]
    int start = 0;//sharedmemory[0]
    int tempRead;

    printf("\nTemperatura%d: ", name);
    while(1)
    {

        __fpurge(stdin);
        if(start == 1 && ReadInt(&tempRead, ROZMIAR) )
        {
            printf("%d", tempRead);
            if(tempRead >=0 && tempRead <= 1300)
                temp = tempRead;
            else if(tempRead < 0)
            {
                printf("\nTemperatura poza zakresem czujnika\n");
                temp = 0;
            }
            else
            {
                printf("\nTemperatura poza zakresem czujnika\n");
                temp = 9999;
            }

            if(tempRead >= 1150 && tempRead <= 1250)
                allowWork = 1;
            else
                allowWork = 0;

            printf("\nTemperatura%d: ", name);

        }

        sem_wait(sem);
        start = addr[0];
        sem_post(sem);

        if(start == 1)
        {
            sem_wait(sem);
            addr[name+1] = temp;
            if( (addr[1] & workFlag) == workFlag && allowWork == 0)
                addr[1] -= workFlag;
            else if( (addr[1] & workFlag) != workFlag && allowWork == 1)
                addr[1] += workFlag;
            sem_post(sem);
        }


        if(start == -1)
        {
            sem_wait(sem);
            addr[name+1] = -1;
            addr[1] = -1;
            sem_post(sem);
            break;
        }


            usleep(100000);
    }


    sem_close(sem);
    return 0;
}




