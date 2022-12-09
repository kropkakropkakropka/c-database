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
    id();
    return 0;
}

void id(){
    char linia[150];

    FILE *fpointer, *fpointer2;
    fpointer = fopen("ksiazki.txt", "r");
    fpointer2 = fopen("pomocniczy.txt", "w");
    int i = 3;
    while (fgets(linia, 150, fpointer)){
        fprintf(fpointer2, "%s", linia);
    }
    fclose(fpointer);
    fclose(fpointer2);

    remove("ksiazki.txt");
    rename("pomocniczy.txt", "ksiazki.txt");
}
