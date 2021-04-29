#include "funkcje.h"



extern int* SharedMemoryOpen(void)
{
    int fd = shm_open(SHMNAME, O_RDWR, S_IRUSR | S_IWUSR);
    static int bad = -1;
    if(fd == -1)
    {
        perror("actor_open\n");
        return &bad;
    }


    void *addr = mmap(NULL, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED)
    {
        perror("actor_mmap\n");
        return &bad;
    }

    return (int*)addr;
}






extern int ReadInt(int* number, int size)
{
    char ch;
    char str[size];
    int i = 0;

    for(int a = 0; a < size; a++) //zerowanie poniewaz zostawaly smieci w tablicy pomimo utworzenia nowej
        str[a] = '\0';

    __fpurge(stdin);
    while(i != size && (ch = getc(stdin)) >= '0' && ch <= '9')
    {
        str[i] = ch;
        i++;
    }
    if((ch < '0' || ch > '9') && ch != '\n')
    {
        printf("\nNieprawidlowe dane\n");
        return 0;
    }
    __fpurge(stdin);
    *number = atoi(str);


    return 1;
}
