#ifndef CON_INCLUDED
#define CON_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio_ext.h>
#include <time.h>
#include <signal.h>

#define SIZE (9)*sizeof(int) // rozmiar shared memory w int nie liczc zegara (dodac rozmiar zegara)

#define SHMNAME "/SHA_MEM"
#define SEMNAME "/SEM_NAME"

#define TEMPWORK_FLAG 3

#define PWDFILE "pwd.txt"

/*
shared memory, kazda kratka ma rozmiar sizeof(int)
####################################################################################
#pulpit    # temperatura # temperatura# tempetaruta # stan #stan #stan #stan # stan#
#operatora # dzialania   # T1         # T2          # CzK1 # L1  # L2  #PW1  # PW2 #
####################################################################################
0          1             2            3             4      5     6     7     8
*/

extern int* SharedMemoryOpen(void);
extern int ReadInt(int* , int);

/*
    obiekty:

    0 Seg1
    1 P1
    2 P2
    3 Tasm
    4 Tasm1
    5 Tasm2
    6 T1
    7 T2
    8 T4
    9 T5
    10 Zg1
    11 Zg2
    12 Rozdr1
    13 Rozdr2
    14 Otw1
    15 Otw2
    16 Licz1
    17 Licz2
    18 Zap1
    19 Zap2
    20 Mag1
    21 Mag2
    22 Zeg
*/
#endif
