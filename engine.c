#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<unistd.h>
#include<ncurses.h>
#include"engine.h"
#include"header.h"

/**
 * Sprawdza, czy wszystkie diamenty zostaly zebrane.
 * Zmienna "zdobycze" to nasze aktualnie zdobyte diamenty.
 * Zmienna "dozdobycia" to niezebrane diamenty do momentu wywolania funkcji WszystkieDiamenty().
 */

bool WszystkieDiamenty(struct stangry*stanplanszy)
{
  assert(stanplanszy->dozdobycia >= 0);
  assert(stanplanszy->zdobycze >= 0);

  if(stanplanszy->zdobycze == stanplanszy->dozdobycia) return true;
  else return false;
}

/**
 * Zalicza diament jako zdobyty.
 * Zmienna "zdobycze" to nasze aktualnie zdobyte diamenty.
 */

void ZjedzDiament(struct stangry*stanplanszy)
{
  stanplanszy->zdobycze++;
}

/*
 * Emuluje grawitacje diamentu tzn. zapisuje diament w polu bezposrednio pod nim,
 * a potem zmienia jego dotychczasowe pole na puste.
 * Parametry "i" oraz "j" odpowiadaja obecnej pozycji diamentu.
 * Parametr "kpionowy" odpowiada wspolrzednej przesuniecia diamentu w dol.
 */

void PrzesunDiament(int i, int j, int kpionowy, struct stangry*stanplanszy)
{
  stanplanszy->Plansza[i][j] = PUSTY;
  stanplanszy->Plansza[i + kpionowy][j] = DIAMENT;
}

/**
 * Przesuwa kamien w poziomie, badz emuluje jego grawitacje tzn. zapisuje kamien w polu bezposrednio pod nim,
 * a potem zmienia jego dotychczasowe pole na puste.
 * Parametry "i" oraz "j" odpowiadaja obecnej pozycji kamienia.
 * Parametry "kpionowy" i "kpoziomy" odpowiada wspolrzednej przesuniecia kamienia.
 */

void PrzesunKamien(int i, int j, int kpionowy, int kpoziomy, struct stangry*stanplanszy)
{
  stanplanszy->Plansza[i][j] = PUSTY;
  stanplanszy->Plansza[i + kpionowy][j + kpoziomy] = KAMIEN;
}

/**
 * Wykonuje ostatni ruch tzn. ustawia pole na ktorym jest postac na puste i
 * konczy gre ustawiajac zmienna "KoniecGry" na true.
 * Zmienna "KoniecGry" zatrzymuje petle while w main(). (wlasnosc stopu)
 * "y" oraz "x" to aktualna pozycja postaci na planszy.
 * Parametr danerf to wskaznik do struktury zawierajacej wspolrzedne postaci: x, y.
 * Parametr stanplanszy to wskaznik do struktury zawierajacej podstawowe informacje o planszy.
 */

void WykonajOstatniRuch(struct wsppostaci*danerf, struct stangry*stanplanszy)
{
  stanplanszy->Plansza[danerf->y][danerf->x] = PUSTY;
  stanplanszy->KoniecGry = true;
}

/**
 * Wykonuje dozwolony ruch tzn. ustawia pole na ktorym jest postac na puste i
 * przepisuje ja do pola docelowego na planszy.
 * Aktualizuje wspolrzedne postaci.
 * Parametry i oraz j odpowiadaja obecnej pozycji wspolrzednych postaci.
 * Parametr danerf to wskaznik do struktury zawierajacej wspolrzedne postaci: x, y.
 * Parametr stanplanszy to wskaznik do struktury zawierajacej podstawowe informacje o planszy.
 */

void WykonajRuch(int i, int j, struct wsppostaci*danerf, struct stangry*stanplanszy)
{
  stanplanszy->Plansza[i][j] = ROCKFORD;
  stanplanszy->Plansza[ danerf->y ][ danerf->x ] = PUSTY;

  danerf->y = i;
  danerf->x = j;
}

/**
 * Sprawdza, czy ruch na pole o podanych wspolrzednych jest mozliwy.
 * Parametry i oraz j odpowiadaja obecnej pozycji wspolrzednych obiektu.
 * Parametr stanplanszy to wskaznik do struktury zawierajacej podstawowe informacje o planszy.
 */

bool SprawdzCzyPoleJestPuste(int i, int j, struct stangry*stanplanszy)
{
  if (stanplanszy->Plansza[i][j] == PUSTY) return true;
  else return false;
}

/**
 * Odpowiada za odpowiedni ruch Rockfordem.
 * Dopasowuje akcje w zaleznosci od zawatosci pola docelowego.
 * Upewnia sie, ze pole to jest niepuste odwolujac sie do podfunkcji SprawdzCzyPoleJestPuste()
 * Konwencja parametrow polega na tym, ze "i" oraz "j" to wspolrzedne pola na ktore chcemy przejsc,
 * a "kpionowy" i "kpoziomy" to nasze przesuniecie o jedno pole do pozycji "i" oraz "j" odpowiednio w kierunku
 * pionowym lub poziomym.
 * Parametr danerf to wskaznik do struktury zawierajacej wspolrzedne postaci: x, y.
 * Parametr stanplanszy to wskaznik do struktury zawierajacej podstawowe informacje o planszy.
 */

void Ruch(int i, int j, int kpionowy, int kpoziomy, struct wsppostaci*danerf, struct stangry*stanplanszy)
{
  switch(stanplanszy->Plansza[i][j])
  {
    case PUSTY: WykonajRuch(i, j, danerf, stanplanszy); break;
    case KAMIEN:
    {
      if(SprawdzCzyPoleJestPuste(i + kpionowy, j + kpoziomy, stanplanszy))
      {
        PrzesunKamien(i, j, kpionowy, kpoziomy, stanplanszy);
        WykonajRuch(i, j, danerf, stanplanszy);
      }
      break;
    }
    case DIAMENT:
    {
      ZjedzDiament(stanplanszy);
      WykonajRuch(i, j, danerf, stanplanszy);
      break;
    }
    case ZIEMIA:
    {
      WykonajRuch(i, j, danerf, stanplanszy);
      break;
    }
    case WYJSCIE:
    {
      if(WszystkieDiamenty(stanplanszy)) WykonajOstatniRuch(danerf, stanplanszy);
      break;
    }
    default: ; break;
  }
}

/**
 * Rozdziela polecenia w zaleznosci od wybranego znaku odpowiadajacego ruchowi w dana strone.
 * Parametr Znak to znak pobrany z wejscia odpowiadajacy ruchowi.
 * Parametr danerf to wskaznik do struktury zawierajacej wspolrzedne postaci: x, y.
 * Parametr stanplanszy to wskaznik do struktury zawierajacej podstawowe informacje o planszy.
 */

void Graj(int Znak, struct wsppostaci*danerf, struct stangry*stanplanszy)
{
    switch (Znak)
    {
        case 259:
        {
            Ruch(danerf->y + WGORE, danerf->x, WGORE, NIGDZIE, danerf, stanplanszy);
            break;
        }
        case 260:
        {
            Ruch(danerf->y, danerf->x + WLEWO, NIGDZIE, WLEWO, danerf, stanplanszy);
            break;
        }
        case 258:
        {
            Ruch(danerf->y + WDOL, danerf->x, WDOL, NIGDZIE, danerf, stanplanszy);
      break;
        }
        case 261:
        {
            Ruch(danerf->y, danerf->x + WPRAWO, NIGDZIE, WPRAWO, danerf, stanplanszy);
            break;
        }
        default: ; break;
  }
}

/**
 * Pobiera znak z wejscia.
 * W przypadku konca pliku zwraca wartosc EOF.
 */

int PobierzZnak()
{
  int Znak = 0;

  do
  {
    Znak= getch();

  }while(Znak != 258 && Znak != 259 && Znak != 260 && Znak != 261);

  return Znak;
}

/**
 * Stabilizuje kolumne, ktora jest "podejrzana" o niestabilnosc po poruszeniu jednego z zawartych w niej kamieni.
 * Parametr "j" to indeks badanej kolumny.
 * Zmienna boolowska "Stabilny" to zmienna ktora mowi nam, czy cala kolumna jest stabilna.
 * Zmienna jest zadeklarowana na "true". Jesli w petli for zmienimy cos na planszy, wartosc zmiennej zostanie zaktualizowana na "false".
 * Warunkuje to ponowne wykonanie petli, czyli ponowne sprawdzenie kolumny pod katem stanilnosci.
 * Funkcja StabilizujKolumny() optymalizuje algorytm sprawdzania.
 * Zamiast sprawdzac cala plansze za kazdym razem, gdy dokonamy zmiany, funkcja bada tylko kolumne na ktorej dokonano zmiany.
 * Parametr stanplanszy to wskaznik do struktury zawierajacej podstawowe informacje o planszy.
 */

void StabilizujKolumny(int j, struct stangry*stanplanszy)
{
  int i;
  bool Stabilny;

  do
  {
    Stabilny = true;

    for(i = 1; i < stanplanszy->ilewi && !Stabilny; i++)
    {
      if (stanplanszy->Plansza[i][j] == KAMIEN)
      {
        if (SprawdzCzyPoleJestPuste(i + WDOL, j, stanplanszy))
        {
          PrzesunKamien(i, j, WDOL, NIGDZIE, stanplanszy); /* jesli nie jest stabilna, to dojdziemy tutaj */
          Stabilny = false;
        }
      }

      if (stanplanszy->Plansza[i][j] == DIAMENT)
      {
        if (SprawdzCzyPoleJestPuste(i + WDOL, j, stanplanszy))
        {
          PrzesunDiament(i, j, WDOL, stanplanszy); /* jesli nie jest stabilna, to dojdziemy tutaj */
          Stabilny = false;
        }
      }
    }

  }while(Stabilny == false);

}


/**
 * Stabilizuje plansze rozgrywki.
 * Przechodzi cala plansze tylko raz. Sprawdza, co jest na badanym polu, jesli jest to kamien badz diament, to
 * sprawdza czy pole pod nim jest puste. Jesli tak, to dokonuje zrzucenia obiektu w dol.
 * W razie jakichkolwiek zmian na planszy badana pod katem stabilnosci jest tylko kolumna na ktorej dokonano tych zmian.
 * Zmienne i oraz j odpowiadaja obecnej pozycji badanego pod katem stabilnosci pola na planszy.
 * Parametr stanplanszy to wskaznik do struktury zawierajacej podstawowe informacje o planszy.
 * Zmienna "ilekol" i "ilewi" zawiera wymiary planszy.
 */

void Stabilizuj(struct stangry*stanplanszy)
{
  int i, j;

  for(i = 1; i < stanplanszy->ilewi; i++)
  {
    for(j = 1; j < stanplanszy->ilekol; j++)
    {
      if (stanplanszy->Plansza[i][j] == KAMIEN)
      {
        if (SprawdzCzyPoleJestPuste(i + WDOL, j, stanplanszy))
        {
          PrzesunKamien(i, j, WDOL, NIGDZIE, stanplanszy);
          StabilizujKolumny(j, stanplanszy);
        }
      }

      if (stanplanszy->Plansza[i][j] == DIAMENT)
      {
        if (SprawdzCzyPoleJestPuste(i + WDOL, j, stanplanszy))
        {
          PrzesunDiament(i, j, WDOL, stanplanszy);
          StabilizujKolumny(j, stanplanszy);
        }
      }
    }
  }

}

/**
 * Pobiera plansze gry do tablicy dwuwymiarowej.
 * Pobiera stan rozgrywki.
 * Sprawdza warunek dopiero po petli, by miec dostepny odczyt z getchar().
 * Koniec planszy jest tylko, gdy i-ty wierszy zerowej kolumny jest rowny znakowi nowej linii.
 * Parametr danerf to wskaznik do struktury zawierajacej wspolrzedne postaci: x, y.
 * Parametr stanplanszy to wskaznik do struktury zawierajacej podstawowe informacje o planszy.
 * Zmienna "ilekol" i "ilewi" zawiera wymiary planszy.
 * Zmienna "pom" to kod znaku ktory jest zapisywany do planszy tylko, jesli nie jest znakiem nowej linii.
 * W przeciwnym razie moglibysmy wyjsc poza zakres 200x100 planszy.
 * Jesli "pom" jest znakiem nowej linii w zerowej kolumnie, to znaczy, ze trafilismy na koniec planszy.
 */

void PobierzPlansze(struct wsppostaci*danerf, struct stangry*stanplanszy, char* plik)
{
  int i, j;
  int pom;
  bool KoniecPlanszy = false;
  bool KoniecLinii = false;
  stanplanszy->ilekol = 0;
  stanplanszy->ilewi = 0;

  FILE* fc;
  fc=fopen(plik, "r");

  if(fc!=NULL)
  {
    for(i = 0; i < YMAX && !KoniecPlanszy; i++)
    {
      KoniecLinii = false;

      for(j = 0; j < XMAX && !KoniecLinii && !KoniecPlanszy; j++)
      {
        pom = getc(fc);

        if(j == 0)
        {
            if(pom == '\n')
            {
              KoniecPlanszy = true;
              KoniecLinii = true;
            }

            if (i == 0) stanplanszy->ilekol++;
            stanplanszy->Plansza[i][j] = pom;

        }
        else
        {
          if(pom == '\n')
          {
            KoniecLinii = true;
            stanplanszy->ilewi++;
          }
          else
          {
            stanplanszy->Plansza[i][j] = pom;
            if (i == 0) stanplanszy->ilekol++;

            if (stanplanszy->Plansza[i][j] == ROCKFORD)  /* Znajduje Rockforda */
            {
              danerf->y = i;
              danerf->x = j;
            }

            if (stanplanszy->Plansza[i][j] == DIAMENT) stanplanszy->dozdobycia++;
          }
        }
      }

    }
  }

  fclose(fc);
}
