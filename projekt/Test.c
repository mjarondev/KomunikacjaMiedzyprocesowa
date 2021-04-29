
#include "funkcje.h"

#include <stdio.h>
#include <stdio_ext.h>
#include <unistd.h>
#include <crypt.h>


int main(int argc, char* argv[])
{


    // system("xterm -e ./Test 12 &"); /////dziala

//    printf("ilosc danych: %d\n", argc);

   // printf("dane: %s\n", argv[1]);

    //while(1)
    //{
    //printf("%zu\n", __fbufsize(stdin));
    //getc(stdin);


    //}
/*
    int workFlag = 1 << 2;
    int cos = 1;


    cos += workFlag;
    workFlag = -workFlag;
    cos += workFlag;


    printf("%d", cos);
    */

    char login[20];
    char salt[9] = "$6$";

    strcat(salt, "'''''");

    printf("Login: ");
    scanf("%s", login);
    getchar();

    char* hash = crypt(login, salt);
    printf("%s", hash);

    printf("\n%s\n", salt);

    FILE* fp = fopen(PWDFILE, "a");

    fprintf(fp, "%s %s\n", login, hash);

    fclose(fp);
/*
    int size = 4;
    char ch;
    char str[size];
    int i = 0;
    int number = 0;

    __fpurge(stdin);
    while(i != size && (ch = getc(stdin)) >= '0' && ch <= '9' )
    {
        str[i] = ch;
        printf("%d ", i);
        i++;
    }
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        printf("\nNieprawidlowe dane\n");
        return 0;
    }
    printf("\n%s\n", str);
    number = atoi(str);
    printf("\n%d\n", number);

    getc(stdin);
*/
    return 0;
}
