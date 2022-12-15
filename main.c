#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

typedef struct
{
    int id, strony;
    char nazwa[100], autor[30], przeczytana;

} book;

void menu();
void zapisz();
void wyszukaj();
void wyswietl();
void usun();

void usun_spacje(char *znaki);  // usuwa spacje i dodaje podkreślenie
void dodaj_spacje(char *znaki); // dodaje spacje w miejsce podkreśleń
void sortuj_id(book *tab, int rozmiarTab);
void sortuj_nazwa(book *tab, int rozmiarTab);
void sortuj_strony(book *tab, int rozmiarTab);
void wypisz(book *tab, int rozmiarTab, int ros); // wypisuje rekordy
int rozmiar();                                   // zwraca rozmiar
int id();                                        // zwraca indeks

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
        fprintf(stderr, "\nError\n");
        return 1;
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
        scanf(" %[^\n]s", ksiazka.autor);
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

    ksiazka.id = id(); // ustawia id dla dodanej ksiazk
    usun_spacje(ksiazka.nazwa);
    usun_spacje(ksiazka.autor);

    fprintf(fpointer, "%d %s %s %d %c\n", ksiazka.id, ksiazka.nazwa, ksiazka.autor, ksiazka.strony, ksiazka.przeczytana); // wpisuje wartosci do pliku

    fclose(fpointer);
    system("cls");
    return;
}

void wyszukaj()
{
    if (rozmiar() == 0)
    {
        printf("W bazie nie znajduje sie zadna ksiazka\n");
        return;
    }
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
    usun_spacje(szukanaNazwa);

    FILE *fpointer;
    fpointer = fopen("ksiazki.txt", "r");
    if (fpointer == NULL)
    {
        fprintf(stderr, "\nError\n");
        return 1;
    }

    int znalezione = 1;
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
            znalezione = 0;
        }
    }
    if (znalezione)
    {
        printf("Nie znaleziono ksiazki\n");
    }

    fclose(fpointer);
    return;
}

void wyswietl()
{
    // sprawdza czy w bazie jest jakis rekord
    if (rozmiar() == 0)
    {
        printf("W bazie nie znajduje sie zadna ksiazka\n");
        return;
    }
    FILE *fpointer;
    book szukanaKsiazka[500];

    fpointer = fopen("ksiazki.txt", "r");
    if (fpointer == NULL)
    {
        fprintf(stderr, "\nError\n");
        return 1;
    }

    int i = 0;
    while (fscanf(fpointer, "%d %s %s %d %c", &szukanaKsiazka[i].id, &szukanaKsiazka[i].nazwa, &szukanaKsiazka[i].autor, &szukanaKsiazka[i].strony, &szukanaKsiazka[i].przeczytana) > 0)
    {
        dodaj_spacje(szukanaKsiazka[i].nazwa);
        dodaj_spacje(szukanaKsiazka[i].autor);
        i++;
    }

    int wybor, wybor2;
    printf("Wybierz wartosc wedlug ktorej chcesz posortowac:\n");
    printf("1 - ID 2 - Nazwa ksiazki 3 - Ilosc stron\n");
    scanf("%d", &wybor);
    printf("1 - Rosnaco 0 - malejaco:\n");
    scanf("%d", &wybor2);
    switch (wybor)
    {
    case 1:
        sortuj_id(szukanaKsiazka, i);
        break;
    case 2:
        sortuj_nazwa(szukanaKsiazka, i);
        break;
    case 3:
        sortuj_strony(szukanaKsiazka, i);
        break;

    default:
        break;
    }
    system("cls");

    wypisz(szukanaKsiazka, i, wybor2);

    fclose(fpointer);
    return;
}

void usun()
{
    // sprawdza czy w bazie jest jakis rekord
    if (rozmiar() == 0)
    {
        printf("W bazie nie znajduje sie zadna ksiazka\n");
        return;
    }
    book szukanaKsiazka;

    FILE *fpointer, *fpointer2;
    fpointer = fopen("ksiazki.txt", "r");
    fpointer2 = fopen("pomocniczy.txt", "w"); // tworze plik pomocniczy
    if (fpointer == NULL)
    {
        fprintf(stderr, "\nError\n");
        return 1;
    }
    if (fpointer2 == NULL)
    {
        fprintf(stderr, "\nError\n");
        return 1;
    }
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
int id()
{
    if (rozmiar() == 0)
    {
        return 1;
    }
    FILE *fpointer;
    book szukanaKsiazka;

    fpointer = fopen("ksiazki.txt", "r");
    if (fpointer == NULL)
    {
        fprintf(stderr, "\nError\n");
        return 1;
    }

    while (fscanf(fpointer, "%d %s %s %d %c", &szukanaKsiazka.id, &szukanaKsiazka.nazwa, &szukanaKsiazka.autor, &szukanaKsiazka.strony, &szukanaKsiazka.przeczytana) > 0){}
    return szukanaKsiazka.id + 1;
}
int rozmiar()
{
    char linia[150];

    FILE *fpointer;
    fpointer = fopen("ksiazki.txt", "r");
    if (fpointer == NULL)
    {
        fprintf(stderr, "\nError\n");
        return 1;
    }
    int i = 0;
    while (fgets(linia, 150, fpointer))
    {
        i++;
    }

    fclose(fpointer);
    return i;
}

void sortuj_id(book *tab, int rozmiarTab)
{
    int i, j;
    book temp;
    for (i = 0; i < rozmiarTab; i++)
    {
        for (j = 0; j < rozmiarTab - i - 1; j++)
        {
            if (tab[j].id > tab[j + 1].id)
            {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}
void sortuj_nazwa(book *tab, int rozmiarTab)
{
    int i, j;
    book temp;
    for (i = 0; i < rozmiarTab; i++)
    {
        for (j = 0; j < rozmiarTab - i - 1; j++)
        {
            if (strcmp(tab[j].nazwa, tab[j + 1].nazwa) > 0)
            {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}
void sortuj_strony(book *tab, int rozmiarTab)
{
    int i, j;
    book temp;
    for (i = 0; i < rozmiarTab; i++)
    {
        for (j = 0; j < rozmiarTab - i - 1; j++)
        {
            if (tab[j].strony > tab[j + 1].strony)
            {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

void wypisz(book *tab, int rozmiarTab, int ros)
{
    if (ros)
    {
        for (int i = 0; i < rozmiarTab; i++)
        {
            printf("ID: %d\n", tab[i].id);
            printf("Nazwa ksiazki: %s\n", tab[i].nazwa);
            printf("Autor: %s\n", tab[i].autor);
            printf("Ilosc stron: %d\n", tab[i].strony);
            printf("Przeczytana: %c\n", tab[i].przeczytana);
            printf("\n");
        }
    }
    else
    {
        for (int i = rozmiarTab - 1; i >= 0; i--)
        {
            printf("ID: %d\n", tab[i].id);
            printf("Nazwa ksiazki: %s\n", tab[i].nazwa);
            printf("Autor: %s\n", tab[i].autor);
            printf("Ilosc stron: %d\n", tab[i].strony);
            printf("Przeczytana: %c\n", tab[i].przeczytana);
            printf("\n");
        }
    }
}