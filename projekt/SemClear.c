// czyszczenie semafora

#include "funkcje.h"

int main()
{
    sem_unlink(SEMNAME);
}
