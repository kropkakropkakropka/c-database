#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdarg.h>

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

void formatuj_wejscie_wyjscie(char znakDoUsuniecia, char znakDoDodania ,int num_args, ...);
void sortuj_id(book *tab, int rozmiarTab);
void sortuj_nazwa(book *tab, int rozmiarTab);
void sortuj_strony(book *tab, int rozmiarTab);
void wypisz(book *tab, int rozmiarTab, int ros); // wypisuje rekordy
int rozmiar();// zwraca ilosc wierszy w pliku
int id();// zwraca indeks

void wczytaj_tytul(book *tytul);
void wczytaj_autor(book *autor);
void wczytaj_strony(book *ksiazka);
void wczytaj_przeczytane(book *ksiazka);

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
    // wczytywanie poszczegolnych wartosc struktury book
    wczytaj_tytul(&ksiazka.nazwa);
    wczytaj_autor(&ksiazka.autor);
    wczytaj_strony(&ksiazka);
    wczytaj_przeczytane(&ksiazka);

    ksiazka.id = id(); // ustawia id dla dodanej ksiazk
    formatuj_wejscie_wyjscie(32, 95, 2, ksiazka.nazwa, ksiazka.autor); //formatuje tytuł i autora ksiązki w odpowiedni sposób
    // wpisuje wartosci do pliku
    fprintf(fpointer, "%d %s %s %d %c\n", ksiazka.id, ksiazka.nazwa, ksiazka.autor, ksiazka.strony, ksiazka.przeczytana); 

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

    wczytaj_tytul(&szukanaKsiazka.nazwa);
    formatuj_wejscie_wyjscie(32, 95, 1, szukanaNazwa);

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
            formatuj_wejscie_wyjscie(95, 32, 2, szukanaKsiazka.nazwa, szukanaKsiazka.autor);
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
    book* szukanaKsiazka = malloc(sizeof(book) * rozmiar());

    fpointer = fopen("ksiazki.txt", "r");
    if (fpointer == NULL)
    {
        fprintf(stderr, "\nError\n");
        return 1;
    }

    int i = 0;
    while (fscanf(fpointer, "%d %s %s %d %c", &szukanaKsiazka[i].id, &szukanaKsiazka[i].nazwa, &szukanaKsiazka[i].autor, &szukanaKsiazka[i].strony, &szukanaKsiazka[i].przeczytana) > 0)
    {
        formatuj_wejscie_wyjscie(95, 32, 2, szukanaKsiazka[i].nazwa, szukanaKsiazka[i].autor);
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
    free(szukanaKsiazka);
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

    while (fscanf(fpointer, "%d %s %s %d %c", &szukanaKsiazka.id, &szukanaKsiazka.nazwa, &szukanaKsiazka.autor, &szukanaKsiazka.strony, &szukanaKsiazka.przeczytana) > 0)
    {
    }
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

void formatuj_wejscie_wyjscie(char znakDoUsuniecia, char znakDoDodania ,int num_args, ...){
    va_list args;
    va_start(args, num_args);
    for (int i = 0; i < num_args; i++)
    {
        char *arg = va_arg(args, char *);
        for (int j = 0; j < strlen(arg); j++)
        {
            if (arg[j] == znakDoUsuniecia)
            {
                arg[j] = znakDoDodania;
            }
        }
    }
    return;  
}

void wczytaj_tytul(book *tytul){
    while (1)
    {
        printf("Podaj tytul ksiazki: \n");
        scanf(" %[^\n]s", tytul);

        if (strlen(tytul) > 100 || strlen(tytul) <= 0)
        {
            printf("Tytul ksiażki musi zawierac conajmniej 1 znak i nie wiecej niz 100 znakow");
            continue;
        }
        break;
    }
}
void wczytaj_autor(book *autor){
    while (1)
    {
        printf("Podaj autora ksiazki: \n");
        scanf(" %[^\n]s", autor);
        if (strlen(autor) > 30)
        {
            printf("Autor nie moze zawierac wiecej niz 30 znakow");
            continue;
        }
        break;
    }
}
void wczytaj_strony(book *ksiazka){
    while (1)
    {
        printf("Podaj ilosc stron: \n");
        scanf("%d", &ksiazka->strony);
        if (ksiazka->strony <= 0)
        {
            printf("Ksiazka musi miec conajmniej jedna strone");
            continue;
        }
        break;
    }
}
void wczytaj_przeczytane(book *ksiazka){
    while (1)
    {
        printf("Czy ksiazka zotsala przez ciebie przeczytana?(t-tak, n-nie): \n");
        scanf(" %c", &ksiazka->przeczytana);
        if (tolower(ksiazka->przeczytana) != 't' && tolower(ksiazka->przeczytana) != 'n')
        {
            printf("%c\n", ksiazka->przeczytana);
            printf("Prosze wpisac t albo n");
            continue;
        }
        break;
    }
}