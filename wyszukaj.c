#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#include<ctype.h> 

void menu();
void zapisz();
void wyszukaj();
// void aktualizuj();
// void usun();
int get_id();

typedef struct 
{
    int id, strony;
    char nazwa[100], autor[30], przeczytana;

} book;


int main(){
    wyszukaj();
    return 0;
}

void wyszukaj(){
    book szukanaKsiazka;
    char linia[150];

    while (1)
    {
        printf("Podaj tytul szukanej ksiazki ksiazki: \n");
        scanf(" %99[0-9a-zA-Z ]", szukanaKsiazka.nazwa);
        
        if (strlen(szukanaKsiazka.nazwa) > 100 || strlen(szukanaKsiazka.nazwa) <= 0)
        {
            printf("Tytul ksiażki musi zawierac conajmniej 1 znak i nie wiecej niz 100 znakow");
            continue;
        }
        break;
    }
    
    FILE *fpointer;
    fpointer = fopen("ksiazki.txt", "r");

    while (fgets(linia, 150, fpointer)){

        if(strstr(linia, szukanaKsiazka.nazwa) != NULL){ //problem - załóżmy ze mamy książke wampir z nysy a potem ksiazke wampir, przy próbie wyszukania książki wampir dostaniemy ksiazke wampir z nysy
            printf("%s", linia);
            return;
        }
        // char kopia[100];
        // int indeks, indeks2;
        // //zrob to w jednej petli
        // for (int i = 0; i < strlen(linia); i++)
        // {
        //     if (linia[i] == ' ')
        //     {
        //         indeks = i + 1;
        //         break;
        //     }
            
        // }
        // for (int i = indeks; i < strlen(linia); i++)
        // {
        //     if (linia[i] == ',')
        //     {
        //         indeks2 = i;
        //         break;
        //     }
            
        // }
        // strncpy(kopia, &linia[indeks], indeks2 - indeks);
        // kopia[indeks2 - indeks] = '\0';
        // if (strcmp(szukanaKsiazka.nazwa, kopia) == 0)
        // {
        //     printf("%s", linia);
        //     return;
        // }
        
    }
    printf("Nie znaleziono ksiazki");
}
