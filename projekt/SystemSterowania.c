
#include "funkcje.h"

#define L_OB 23
#define L_BUTELEK 10 //20
#define MIN_BUTELEK 5
#define TIME1 5
#define TIME2 3

void Actors(void);
int* SharedMemoryCreate(void);
int SharedMemoryRemove(void*);
void GetSharedTab(int* tab, int* addr, sem_t* sem);
void ObiektyStan(int* data, int* obiekty);
void ObiektyWyswietl(int* data, int* obiekty);


int main()
{

    struct timespec offtime, now, last;


    int obiekty[L_OB];

    for(int i = 0; i < L_OB; i++)
        obiekty[i] = 0;


    printf("hello\n");
    int* addr = SharedMemoryCreate();

    //utworzenie semafora
    sem_t* semafor = sem_open(SEMNAME, O_CREAT, O_RDWR | S_IRUSR | S_IWUSR, 1);
    if(semafor == SEM_FAILED)
    {
        printf("\nSemafor nieutworzony\n");
        exit(1);
    }

    int data[SIZE];

    //zerowanie tablic shared memory i danych
    for(int i = 0; i <= SIZE; i++)
    {
        addr[i] = 0;
        data[i] = 0;
    }

    Actors();


    clock_gettime(CLOCK_MONOTONIC, &now);
    last = now;

    unsigned int sleeptime = 100000;
    while(1)
    {
        usleep(sleeptime);
        GetSharedTab(data, addr, semafor);

        clock_gettime(CLOCK_MONOTONIC, &now);
        obiekty[22] = now.tv_sec - last.tv_sec;
        last = now;

        ObiektyStan(data, obiekty);
        ObiektyWyswietl(data, obiekty);

        printf("\n\n");

        if(data[0] == -1 && data[4] == -1 && data[2] == -1 && data[3] == -1 &&
            data[5] == -1 && data[6] == -1 && data[7] == -1 && data[8] == -1)
            break;
    }

    sem_close(semafor);
    sem_unlink(SEMNAME);
    SharedMemoryRemove(addr);


    return 0;
}

void ObiektyStan(int* data, int* obiekty)
{
    if(data[0] == 1)
    {
        if(data[4] == 1) //CzK1
            obiekty[0] = 1; //Seg1
        else
            obiekty[0] = 0;

        if(data[2] < 1190) //Temp1
            obiekty[1] = 1; //P1
        else if(data[2] > 1210)
            obiekty[1] = 0;

        if(data[3] < 1190) //Temp2
            obiekty[2] = 1; //P2
        else if(data[3] > 1210)
            obiekty[2] = 0;

        if(obiekty[16] < L_BUTELEK && obiekty[17] < L_BUTELEK)//Licz1, Licz2
            obiekty[3] = 1; //Tasm
        else
            obiekty[3] = 0;

        if(data[7] < 3 || (data[7] >= 3 && obiekty[8] < TIME2) ) //PW1, T4
            obiekty[4] = 1; //Tasm1
        else if(data[7] >= 3 && obiekty[8] >= TIME2 && obiekty[8] < 2*TIME2 )
            obiekty[4] = 2;
        else
            obiekty[4] = 0;

        if(data[8] < 3 || (data[8] >= 3 && obiekty[9] < TIME2) ) //PW2, T5
            obiekty[5] = 1; //Tasm2
        else if(data[8] >= 3 && obiekty[9] >= TIME2 && obiekty[9] < 2*TIME2 )
            obiekty[5] = 2;
        else
            obiekty[5] = 0;

        if(obiekty[16] >= MIN_BUTELEK && obiekty[10] != 1 && obiekty[22] != 0 ) //Licz1, Zg1, Zeg
            obiekty[6] += 1; //T1
        else if(obiekty[16] < MIN_BUTELEK || obiekty[10] == 1)
            obiekty[6] = 0;

        if(obiekty[17] >= MIN_BUTELEK && obiekty[11] != 1 && obiekty[22] != 0 ) //Licz2, Zg2, Zeg
            obiekty[7] += 1; //T2
        else if(obiekty[17] < MIN_BUTELEK || obiekty[11] == 1)
            obiekty[7] = 0;

        if(data[7] < 3) //PW1
            obiekty[8] = 0; //T4
        else if(data[7] >= 3 && obiekty[22] != 0 && obiekty[8] <= 2*TIME2)
            obiekty[8] += 1;

        if(data[8] < 3)//PW2
            obiekty[9] = 0;//T5
        else if(data[8] >= 3 && obiekty[22] != 0 && obiekty[9] <= 2*TIME2)
            obiekty[9] += 1;


        if(obiekty[6] > TIME1) //T1
            obiekty[10] = 1; //Zg1
        if(rand() % 5 == 0) //przyblizenie automatycznego wylaczania sie obiektu
            obiekty[10] = 0;

        if(obiekty[7] > TIME1) //T2
            obiekty[11] = 1; //Zg2
        if(rand() % 5 == 0) //przyblizenie automatycznego wylaczania sie obiektu
            obiekty[11] = 0;


        if(data[7] >= 3 && obiekty[8] >= TIME2 && obiekty[8] <= 2*TIME2) //PW1, T4
            obiekty[12] = 1; //Rozdr1
        else if(rand() % 10 == 0) //przyblizenie automatycznego wylaczania sie obiektu
            obiekty[12] = 0;

        if(data[8] >= 3 && obiekty[9] >= TIME2 && obiekty[9] <= 2*TIME2) //PW2, T5
            obiekty[13] = 1; //Rozdr2
        else if(rand() % 10 == 0) //przyblizenie automatycznego wylaczania sie obiektu
            obiekty[13] = 0;



        if(obiekty[6] > 0 && obiekty[6] <= TIME1) //T1
            obiekty[14] = 1; //Otw1
        else
            obiekty[14] = 0;


        if(obiekty[7] > 0 && obiekty[7] <= TIME1) //T2
            obiekty[15] = 1; //Otw2
        else
            obiekty[15] = 0;



        if(data[5] == 1)//L1
            obiekty[16] += 1;//Licz1
        if(obiekty[6] > TIME1)//T1
            obiekty[16] = 0;

        if(data[6] == 1)//L2
            obiekty[17] += 1;//Licz2
        if(obiekty[7] > TIME1)//T2
            obiekty[17] = 0;


        if(data[7] >= 3) //PW1
            obiekty[18] = 0; //Zap1
        else
            obiekty[18] = 1;


        if(data[8] >= 3)
            obiekty[19] = 0;
        else
            obiekty[19] = 1;


        if(data[7] < 3 || (data[7] >=3 && obiekty[8] < TIME2)) //PW1, T4
            obiekty[20] = 1; //Mag1
        else if(data[7] >= 3 && obiekty[8] >= TIME2)
            obiekty[20] = 0;

        if(data[8] < 3 || (data[8] >=3 && obiekty[9] < TIME2)) //PW2, T5
            obiekty[21] = 1; //Mag2
        else if(data[8] >= 3 && obiekty[9] >= TIME2)
            obiekty[21] = 0;


    }
    else if(data[0] == 0)
    {
        for(int i = 0; i < 14; i++)
            obiekty[i] = 0;
    }
    else if(data[0] == -1)
    {
        for(int i = 0; i < L_OB; i++)
            obiekty[i] = -1;
    }

}

void ObiektyWyswietl(int* data, int* obiekty)
{
    printf("\nWork: %d\tTemperature: %d\n", data[0], data[1]);

    printf("Temperatura1: %d   Temperatura2: %d\nCzK: %d   L1: %d   L2: %d   PW1: %d   PW2: %d\n",
    data[2], data[3], data[4], data[5], data[6], data[7], data[8]);


    printf("Piec1: %d   Piec2: %d\nGlowny tasmiociag: %d   Tasmociag1: %d   Tasmociag2: %d\n",
    obiekty[1], obiekty[2], obiekty[3], obiekty[4], obiekty[5]);

    printf("Czasomierze:\tT1: %d   T2: %d   T3: %d   T4: %d\n", obiekty[6],
    obiekty[7], obiekty[8], obiekty[9]);

    printf("Liczniki:\tLicz1: %d   Licz2: %d\n", obiekty[16], obiekty[17]);

    printf("Silownik: %d\n", obiekty[0]);

    printf("Zgniatarka1: %d   Zgniatarka2: %d\n", obiekty[10], obiekty[11]);

    printf("Zapadnia zgniatarki1: %d   Zapadnia zgniatarki2: %d\n", obiekty[14], obiekty[15]);

    printf("Rozdrabniacz1: %d   Rozdrabniacz2: %d\n", obiekty[12], obiekty[13]);

    printf("Zapadnia rozdrabniacza1: %d    Zapadnia rozdrabniacza2: %d\n", obiekty[18], obiekty[19]);

    printf("Magnes1: %d   Magnes2: %d\n", obiekty[20], obiekty[21]);

}

int SharedMemoryRemove(void* addr)
{
    int res = munmap(addr, SIZE);
    if(res == -1)
    {
        perror("munmap");
        return -1;
    }

    int fd = shm_unlink(SHMNAME);
    if(fd == -1)
    {
        perror("shm_unlink");
        return -1;
    }

    return 0;
}

int* SharedMemoryCreate(void)
{
    int fd = shm_open(SHMNAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    static int bad = -1;
    if(fd == -1)
    {
        perror("shm_open\n");
        return &bad;
    }

    int res = ftruncate(fd, SIZE);
    if(res == -1)
    {
        perror("ftruncate\n");
        return &bad;
    }

    void *addr = mmap(NULL, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED)
    {
        perror("mmap\n");
        return  &bad;
    }

    return (int*)addr;
}

void Actors(void)
{
    printf("\nstart\n");


    //execl("/bin/sh", "sh", "-c", "xterm -e ./wlacz &", (char *) NULL);

    system("xterm -geometry 80x7+0+0 -e ./PulpitOperatora &");

    system("xterm -geometry 40x5+0+125 -e ./Temp1 1 &");

    system("xterm -geometry 40x5+250+125 -e ./Temp1 2 &");

    system("xterm -geometry 40x5+0+325 -e ./Licznik 1 &");

    system("xterm -geometry 40x5+250+325 -e ./Licznik 2 &");

    system("xterm -geometry 40x5+0+425 -e ./PW 1 &");

    system("xterm -geometry 40x5+250+425 -e ./PW 2 &");

    system("xterm -geometry 80x5+0+225 -e ./CzK1 &");


    printf("uruchomiono wszystkie procesy\n");
}

void GetSharedTab(int* tab, int* addr, sem_t* sem)
{
    sem_wait(sem);
    memcpy(tab, addr, SIZE);
    if(addr[4] != -1) addr[4] = 0;
    if(addr[5] != -1) addr[5] = 0;
    if(addr[6] != -1) addr[6] = 0;
    sem_post(sem);

}


