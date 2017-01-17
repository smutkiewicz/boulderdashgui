#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<unistd.h>
#include<ncurses.h>
#include"header.h"
#include"graphics.h"
#include"engine.h"

/* Uruchamia gre.
 * W funkcji main struktura programu wyglada nastepujaco:
 * I Sprawdzamy stabilnosc pobranej planszy.
 * II Wykonujemy jakiekolwiek operacje tylko na stabilnej planszy:
 *  - do momentu konca pliku z ruchami badz konca gry powtarzamy cykl:
 *    1. Pobranie znaku ruchu.
 *      1. Wykonanie ruchu badz nie, gdy jest niedozwolony.
 *    2. Zapewnienie stabilnosci planszy.
 * III Na koniec wyswietlamy plansze po rozgrywce.
 *
 * Zmienna zdobycze to nasze aktualnie zdobyte diamenty.
 * Zmienna dozdobycia to niezebrane diamenty.
 * Gra zatrzymuje sie dopiero gdy funkcja WykonajOstatniRuch() jest wywolana
 * (funkcja ta zmienia wartosc zmiennej boolowskiej "KoniecGry" w strukturze "stanplanszy" na false)
 * lub gdy skoncza sie znaki wpisywane przez uzytkownika (funkcja PobierzZnak() zwroci EOF).
 */
int main(int argc, char* argv[])
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);

    struct wsppostaci danerf;
    struct stangry stanplanszy;

    while(Menu())
    {
        stanplanszy.zdobycze = 0; /* inicjalizuje ilosc diamentow na poczatku rozgrywki */
        stanplanszy.dozdobycia = 0; /* inicjalizuje ilosc diamentow na planszy na 0 przed ich policzeniem */
        stanplanszy.KoniecGry = false;

        PobierzPlansze(&danerf, &stanplanszy, argv[1]); /* pobiera plansze i dane o jej stanie: */
        /*pozycje Rockforda, wszystkie diamenty do zdobycia, wymiary planszy */

		if(Sprawdz(&stanplanszy))
	    {
	        Stabilizuj(&stanplanszy);  /*Stabilizuje plansze */
	        WyswietlPlansze(&stanplanszy);
	        printw("Plansza: %s", argv[1]);

	        while(!stanplanszy.KoniecGry)
	        {
	            Graj(PobierzZnak(), &danerf, &stanplanszy); //inicjuje rozgrywke w oparciu o dane o planszy
	            Stabilizuj(&stanplanszy);
	            WyswietlPlansze(&stanplanszy);
	            printw("Plansza: %s", argv[1]);
	        }

	        WyswietlPlansze(&stanplanszy);
	        sleep(1);
	        clear();
	        mvprintw(10, 10, "WYGRALES!!!!");
	        refresh();
	        sleep(1);
	    }
	}

    clear();
    refresh();
    endwin();

    return 0;
}
