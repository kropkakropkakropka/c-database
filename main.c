#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

void menu();
void zapisz();
void wyszukaj();
void wyswietl();
void usun();

void usun_spacje();
void dodaj_spacje();
int get_id();

typedef struct
{
    int id, strony;
    char nazwa[100], autor[30], przeczytana;

} book;

int main()
{
    menu();
    return 0;
}

void menu()
{
    int wybor;
    while (wybor != 5)
    {
        printf("1 - Dodaj nowa ksiazke\n2 - Wyszukaj ksiazke\n3 - Wyswietl wszystkie rekordy\n4 - Usun ksiazke\n5 - Wyjdz\n");
        scanf("%d", &wybor);
        system("cls");
        switch (wybor)
        {
        case 1:
            zapisz();
            break;
        case 2:
            wyszukaj();
            printf("Wcisnij jakikolwiek przycisk aby kontynuowac\n");
            getch();
            system("cls");
            break;
        case 3:
            wyswietl();
            printf("Wcisnij jakikolwiek przycisk aby kontynuowac\n");
            getch();
            system("cls");
            break;
        case 4:
            usun();
            break;

        default:
            break;
        }
    }
}

void zapisz()
{
    book ksiazka;

    FILE *fpointer;
    fpointer = fopen("ksiazki.txt", "a");

    if (fpointer == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit(1);
    }

    // wczytuje poszczegolne wartosc struktury
    while (1)
    {
        printf("Podaj tytul ksiazki: \n");
        scanf(" %[^\n]s", ksiazka.nazwa);

        if (strlen(ksiazka.nazwa) > 100 || strlen(ksiazka.nazwa) <= 0)
        {
            printf("Tytul ksiażki musi zawierac conajmniej 1 znak i nie wiecej niz 100 znakow");
            continue;
        }
        break;
    }
    while (1)
    {
        printf("Podaj autora ksiazki: \n");
        scanf(" %29[0-9a-zA-Z ]", ksiazka.autor);
        if (strlen(ksiazka.autor) > 30)
        {
            printf("Autor nie moze zawierac wiecej niz 30 znakow");
            continue;
        }
        break;
    }
    while (1)
    {
        printf("Czy ksiazka zotsala przez ciebie przeczytana?(t-tak, n-nie): \n");
        scanf(" %c", &ksiazka.przeczytana);
        if (tolower(ksiazka.przeczytana) != 't' && tolower(ksiazka.przeczytana) != 'n')
        {
            printf("Prosze wpisac t albo n");
            continue;
        }
        break;
    }
    while (1)
    {
        printf("Podaj ilosc stron: \n");
        scanf("%d", &ksiazka.strony);
        if (ksiazka.strony <= 0)
        {
            printf("Ksiazka musi miec conajmniej jedna strone");
            continue;
        }
        break;
    }

    ksiazka.id = get_id();
    usun_spacje(ksiazka.nazwa);
    usun_spacje(ksiazka.autor);

    fprintf(fpointer, "%d %s %s %d %c\n", ksiazka.id, ksiazka.nazwa, ksiazka.autor, ksiazka.strony, ksiazka.przeczytana); // wpisuje wartosci do pliku

    fclose(fpointer);
    system("cls");
    return;
}

void wyszukaj()
{
    book szukanaKsiazka;
    char szukanaNazwa[100];

    while (1)
    {
        printf("Podaj tytul szukanej ksiazki ksiazki: \n");
        scanf(" %[^\n]s", szukanaNazwa);

        if (strlen(szukanaKsiazka.nazwa) > 100 || strlen(szukanaKsiazka.nazwa) <= 0)
        {
            printf("Tytul ksiażki musi zawierac conajmniej 1 znak i nie wiecej niz 100 znakow");
            continue;
        }
        break;
    }
    system("cls");
    usun_spacje(szukanaNazwa);
    FILE *fpointer;
    fpointer = fopen("ksiazki.txt", "r");

    while (fscanf(fpointer, "%d %s %s %d %c", &szukanaKsiazka.id, &szukanaKsiazka.nazwa, &szukanaKsiazka.autor, &szukanaKsiazka.strony, &szukanaKsiazka.przeczytana) > 0)
    {
        if (strcasecmp(szukanaKsiazka.nazwa, szukanaNazwa) == 0)
        {
            dodaj_spacje(szukanaKsiazka.nazwa);
            dodaj_spacje(szukanaKsiazka.autor);
            printf("ID: %d\n", szukanaKsiazka.id);
            printf("Nazwa ksiazki: %s\n", szukanaKsiazka.nazwa);
            printf("Autor: %s\n", szukanaKsiazka.autor);
            printf("Ilosc stron: %d\n", szukanaKsiazka.strony);
            printf("Przeczytana: %c\n", szukanaKsiazka.przeczytana);
            fclose(fpointer);
            return;
        }
    }

    printf("Nie znaleziono ksiazki");
    fclose(fpointer);
    return;
}

void wyswietl()
{
    FILE *fpointer;
    book szukanaKsiazka;

    fpointer = fopen("ksiazki.txt", "r");

    while (fscanf(fpointer, "%d %s %s %d %c", &szukanaKsiazka.id, &szukanaKsiazka.nazwa, &szukanaKsiazka.autor, &szukanaKsiazka.strony, &szukanaKsiazka.przeczytana) > 0)
    {
        dodaj_spacje(szukanaKsiazka.nazwa);
        dodaj_spacje(szukanaKsiazka.autor);
        printf("ID: %d\n", szukanaKsiazka.id);
        printf("Nazwa ksiazki: %s\n", szukanaKsiazka.nazwa);
        printf("Autor: %s\n", szukanaKsiazka.autor);
        printf("Ilosc stron: %d\n", szukanaKsiazka.strony);
        printf("Przeczytana: %c\n", szukanaKsiazka.przeczytana);
        printf("\n");
    }
    fclose(fpointer);
    return;
}

void usun()
{
    book szukanaKsiazka;

    FILE *fpointer, *fpointer2;
    fpointer = fopen("ksiazki.txt", "r");
    fpointer2 = fopen("pomocniczy.txt", "w"); // tworze plik pomocniczy

    int usunto;
    printf("wprowadz id ksiazki ktora chcesz usunac: ");
    scanf("%d", &usunto);

    while (fscanf(fpointer, "%d %s %s %d %c", &szukanaKsiazka.id, &szukanaKsiazka.nazwa, &szukanaKsiazka.autor, &szukanaKsiazka.strony, &szukanaKsiazka.przeczytana) > 0)
    {
        if (szukanaKsiazka.id != usunto)
        {
            fprintf(fpointer2, "%d %s %s %d %c\n", szukanaKsiazka.id, szukanaKsiazka.nazwa, szukanaKsiazka.autor, szukanaKsiazka.strony, szukanaKsiazka.przeczytana);
        }
        
    }
    fclose(fpointer);
    fclose(fpointer2);

    remove("ksiazki.txt");                   // usuwa originalny plik
    rename("pomocniczy.txt", "ksiazki.txt"); // zmienia nazwe pomocniczego pliku na nazw originalną
    
}

void usun_spacje(char *znaki)
{
    for (int i = 0; i < strlen(znaki); i++)
    {
        if (isspace(znaki[i]))
        {
            znaki[i] = 95;
        }
    }
    return;
}

void dodaj_spacje(char *znaki)
{
    for (int i = 0; i < strlen(znaki); i++)
    {
        if (znaki[i] == 95)
        {
            znaki[i] = 32;
        }
    }
    return;
}

int get_id()
{
    char linia[150];

    FILE *fpointer, *fpointer2;
    fpointer = fopen("ksiazki.txt", "r");
    int i = 0;
    do
    {
        i++;
    } while (fgets(linia, 150, fpointer));

    fclose(fpointer);
    return i;
}