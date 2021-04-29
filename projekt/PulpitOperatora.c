
#include "funkcje.h"
#include "funkcje.c"

void Dodaj(void);
void Usun(void);
void Pokaz(void);

int main()
{

    int* addr = SharedMemoryOpen();

    sem_t* sem = sem_open(SEMNAME, 0);
    if(sem == SEM_FAILED)
    {
        printf("\nPulpitOperatora - semafor nieotwarty\n");
        exit(1);
    }

    char ch;
    int admin = 0;
    int logout = 0;
    int out = 0;



    while(1)
    {
        out = 0;
        logout = 0;
        admin = 0;
        //login:$id$salt$hashedpass (5 bajtowy salt)
        while(!out)
        {
            printf("\n1. Login\n2. Exit\n");
            __fpurge(stdin);

            if((ch = getc(stdin)) == '1')
            {
                __fpurge(stdin);
                FILE* fp;

                char login[20], pass[30];
                printf("\nWpisz login: ");
                scanf("%s", login);
                getchar();
                printf("\nWpisz haslo: ");
                scanf("%s", pass);
                getchar();


                if((fp = fopen(PWDFILE, "r")) == NULL)
                {
                    printf("\nNie udalo sie otworzyc pliku\n");

                }
                else
                {
                    char flogin[20], fpass[96];
                    while(fscanf(fp, "%s %s", flogin, fpass) != EOF)
                    {

                        if(strcmp(flogin, login) == 0)
                        {
                            char fsalt[10], fhash[87];
                            strncpy(fsalt, fpass, 9);
                            //strncpy(fhash, fpass+9, 86);

                            char* hash = crypt(pass, fsalt);
                            if(strcmp(hash, fpass) == 0)
                            {
                                if(strcmp(login, "admin") == 0)
                                {
                                    admin = 1;
                                }
                                out = 1;
                                break;
                            }
                        }
                    }

                if(!out)
                    printf("\nZle dane\n");

                }

                fclose(fp);
            }
            else if(ch == '2')
            {
                sem_wait(sem);
                addr[0] = -1;
                sem_post(sem);
                sem_close(sem);
                return 0;
            }


            usleep(100000);

        }



        int state = 0;
        if(admin && !logout)
        {
            printf("\nWitaj admin\n");

            while(!logout)
            {
                usleep(100000);
                printf("\n1. Dodaj nowego uzytkownika\n2. Usun uzytkownika\n3. Pokaz uzytkownikow\
\n4. Exit\n5. Logout\n");
                __fpurge(stdin);
                if( (ch = getc(stdin)) != '\n')
                {

                    switch(ch)
                    {
                    case '1':
                        Dodaj();
                        break;
                    case '2':
                        Usun();
                        break;
                    case '3':
                        Pokaz();
                        break;
                    case '4':
                        state = -1;
                        break;
                    case '5':
                        state = 0;
                        logout = 1;
                        break;
                    default:
                        break;
                    }

                    sem_wait(sem);
                    addr[0] = state;
                    sem_post(sem);

                    if(state == -1)
                        break;

                }


            }
        }
        else if(!logout)
        {
            printf("\nWitaj uzytkowniku\n");
            while(!logout)
            {

                usleep(100000);
                printf("\n1. Start\n2. Stop\n3. Exit\n4. Logout\n");
                __fpurge(stdin);
                if( (ch = getc(stdin)) != '\n')
                {


                    switch(ch)
                    {
                    case '1':
                        state = 1;
                        break;
                    case '2':
                        state = 0;
                        break;
                    case '3':
                        state = -1;
                        break;
                    case '4':
                        state = 0;
                        logout = 1;
                        break;
                    default:
                        break;
                    }

                    sem_wait(sem);
                    addr[0] = state;
                    sem_post(sem);

                    if(state == -1)
                        break;

                }


            }


        }
        if(state == -1)
            break;
    }
    sem_close(sem);


    return 0;
}

void Usun(void)
{
    FILE* fp;
    FILE* fd;
    char login[20];
    char flogin[20];
    char fpass[96];
    printf("\nPodaj login: ");
    scanf("%s", login);
    getchar();

    if((fp = fopen(PWDFILE, "r")) == NULL)
    {
        printf("\nBlad podczas otwierania pliku hasel\n");
        return;
    }
    if((fd = fopen("newpwdfile.txt", "w")) == NULL)
    {
        printf("\nBlad podczas otwierania pliku hasel\n");
        return;
    }

    printf("Usuwanie uzytkownika...");
    while(fscanf(fp, "%s %s", flogin, fpass) != EOF)
    {
        int def = 1;
        if(strcmp(flogin, login) != 0 || (def = strcmp(login, "admin")) == 0)
        {
            if(def == 0)
            {
                printf("\nNie mozna usunac admina\n");
            }
            fprintf(fd, "%s %s\n", flogin, fpass);
        }
    }

    fclose(fp);
    fclose(fd);
    remove(PWDFILE);
    rename("newpwdfile.txt", PWDFILE);
}


void Dodaj(void)
{
    char login[20];
    char haslo[30];
    char salt[9] = "$6$";

    char saltbytes[6];
    saltbytes[5] = '\0';

    for(int i = 0; i < 5; i++)
    {
        saltbytes[i] = (rand()%75)+48;
    }

    strcat(salt, saltbytes);

    printf("\nWpisz login: ");
    scanf("%s", login);
    getchar();

    printf("\nWpisz haslo: ");
    scanf("%s", haslo);
    getchar();

    char* hash = crypt(haslo, salt);

    FILE* fp = fopen(PWDFILE, "a");

    fprintf(fp, "%s %s\n", login, hash);

    fclose(fp);

    printf("\nNowy uzytkownik dodany\n");

}

void Pokaz(void)
{
    FILE* fp;
    char flogin[20];
    char fpass[96];
    getchar();

    if((fp = fopen(PWDFILE, "r")) == NULL)
    {
        printf("\nBlad podczas otwierania pliku hasel\n");
        return;
    }
    printf("\nKonta:\n");
    while(fscanf(fp, "%s %s", flogin, fpass) != EOF)
    {
        printf("%s\n", flogin);
    }

    fclose(fp);




}

