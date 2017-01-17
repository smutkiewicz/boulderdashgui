#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<unistd.h>
#include<ncurses.h>
#include"header.h"
#include"graphics.h"

/**
 * Wyswietla plansze gry w standardowym wyjsciu
 * Parametry i oraz j odpowiadaja obecnej pozycji w tablicy wyswietlanego znaku.
 */
void WyswietlPlansze(struct stangry*stanplanszy)
{
      int i, j;
      clear();
      printw("GRA BOULDER DASH V 1.0\n");
      printw("$: %d Do zdobycia: %d\n\n", stanplanszy->zdobycze, stanplanszy->dozdobycia-stanplanszy->zdobycze);

      for(i = 0;  i < stanplanszy->ilewi; i++)
      {
          for(j = 0; j < stanplanszy->ilekol; j++)
          {
              switch(stanplanszy->Plansza[i][j])
              {
                case ROCKFORD:
                  start_color();
                  init_pair( 1, COLOR_RED, COLOR_BLACK );
                  attron( COLOR_PAIR( 1 ) );
                  attron( A_BOLD );
                  printw("%c",stanplanszy->Plansza[i][j]);
                  attroff( COLOR_PAIR( 1 ) );
                  attroff( A_BOLD );
                  break;
                case DIAMENT:
                  start_color();
                  init_pair( 2, COLOR_CYAN, COLOR_BLACK );
                  attron( COLOR_PAIR( 2 ) );
                  printw("%c",stanplanszy->Plansza[i][j]);
                  attroff( COLOR_PAIR( 2 ) );
                  break;
                case KAMIEN:
                  attron( A_BOLD );
                  printw("%c",stanplanszy->Plansza[i][j]);
                  attroff( A_BOLD );
                  break;
                case WYJSCIE:
                  start_color();
                  init_pair( 3, COLOR_YELLOW, COLOR_BLACK );
                  attron( COLOR_PAIR( 3 ) );
                  printw("%c",stanplanszy->Plansza[i][j]);
                  attroff( COLOR_PAIR( 3 ) );
                  break;
                case SKALA:
                  attron( A_REVERSE );
                  printw("%c",stanplanszy->Plansza[i][j]);
                  attroff( A_REVERSE );
                  break;
                default:
                  printw("%c", stanplanszy->Plansza[i][j]);
                  break;
              }
          }

          printw("%c", '\n');
      }

      refresh();
}

/*Wyswietla menu z uzyciem biblioteki ncurses*/
bool Menu()
{
    int ktory = 1;
    int znak;
    const short int min_wybor = 1;
    const short int max_wybor = 2;

    do
    {
	    znak = getch();
	    clear();
	    refresh();
	    mvprintw( 3, 5, "&& BOULDER DASH by M.S" );
	    mvprintw( 6, 5, "Wyjdz" );
	    attron( A_REVERSE );
	    mvprintw( 5, 5, "Graj!" );
	    refresh();
	    attroff( A_REVERSE );


        if( znak == KEY_UP && ktory != min_wybor )
        {
            ktory--;
        }
        else if( znak == KEY_DOWN && ktory != max_wybor )
        {
            ktory++;
        }

        if(znak == 10)
        {
            switch(ktory)
            {
            	case 1:
          		return true;
                break;
                case 2:
                return false;
                break;
            }
        }

        switch(ktory)
        {
            case 1:
                mvprintw( 6, 5, "Wyjdz" );
                attron( A_REVERSE );
                mvprintw( 5, 5, "Graj!" );
                refresh();
                break;

            case 2:
                mvprintw( 5, 5, "Graj!" );
                attron( A_REVERSE );
                mvprintw( 6, 5, "Wyjdz" );
                refresh();
                break;
        }

        attroff( A_REVERSE );

    }while(true);

    return false;
}

/*Sprawdza, czy wyswietlanie planszy z wejscia bedzie poprawne*/
bool Sprawdz(struct stangry*stanplanszy)
{
     int y, x;
     int kolor;
     getmaxyx(stdscr, y,x);
     kolor = (stanplanszy->ilekol*stanplanszy->ilewi)/4;

     if(has_colors() == FALSE)
     {
        printw("Twoj terminal nie obsluguje kolorow.\n");
        return false;
     }

     if(stanplanszy->ilekol < x && stanplanszy->ilewi+3 < y) return true;
     else
     {
        clear();
        refresh();
        printw("Za male wymiary konsoli.\n");
        printw("Zwieksz wymiary konsoli i sprobuj jeszcze raz\n");
        refresh();
        return false;
     }

     if(stanplanszy->dozdobycia > kolor)
     {
        //tryb bez kolorow
        clear();
        refresh();
        printw("Tryb bez kolorow.\n");
        refresh();
        sleep(2);
     }

}
