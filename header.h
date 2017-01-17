#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define YMAX 100 /* rzedna */
#define XMAX 200 /* odcieta */
#define KAMIEN 'O'
#define DIAMENT '$'
#define SKALA '#'
#define PUSTY ' '
#define WYJSCIE 'X'
#define ROCKFORD '&'
#define ZIEMIA '.'
#define WDOL 1  /* wspolrzedne kierunkow */
#define WGORE -1 /* odpowiada skoku o indeks w gore tablicy dwuwymiarowej */
#define WPRAWO 1 /* odpowiada skoku o indeks w prawo tablicy dwuwymiarowej */
#define WLEWO -1 /* odpowiada skoku o indeks w lewo tablicy dwuwymiarowej */
#define NIGDZIE 0 /* odpowiada skoku o indeks w gore tablicy dwuwymiarowej */

typedef struct wsppostaci{

    int x; /* wspolrzedna postaci, nr kolumny */
    int y; /* wspolrzedna postaci, nr wiersza */

}wsppostaci;

typedef struct stangry{

    int Plansza[YMAX][XMAX]; /* inicjujemy plansze rozgrywki */
    int zdobycze; /*zdobyte do tej pory diamenty*/
    int dozdobycia; /* wszystkie diamenty do zdobycia na planszy */
    int ilekol; /* kolumny */
    int ilewi; /* wiersze */
    bool KoniecGry;

}stangry;

#endif //HEADER_H_INCLUDED
