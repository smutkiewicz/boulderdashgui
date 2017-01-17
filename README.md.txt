Student:	Micha� Smutkiewicz (T2)
		msmutkie@elka.pw.edu.pl
Prowadz�cy:  	mgr in�. Andrzej Woje�ski
Podstawy Programowania (PRM) � projekt
specyfikacja funkcjonalna
Temat: Komputerowa gra logiczna Boulder Dash z GUI przy u�yciu biblioteki ncurses.
Definicje poj��: Boulder Dash (https://en.wikipedia.org/wiki/Boulder_Dash) to komputerowa gra logiczno-zr�czno�ciowa. Tematem zadania jest jej wariant, pozbawiony element�w zr�czno�ciowych.
Ncurses � kontynuacja biblioteki curses z BSD. Dostarcza ona funkcji do obs�ugi terminala tekstowego niezale�nie od jego typu (korzysta z terminfo lub termcap), z optymalizacj� (ekran nie jest odrysowywany w ca�o�ci). Umo�liwia ona tworzenie aplikacji z interfejsem przypominaj�cym interfejs graficzny. (�r�d�o: Wikipedia.org)
Zasady gry:
Rozgrywka "Boulder Dasha" toczy si� na prostok�tnej planszy, kt�rej pola s� zorganizowane w wiersze i kolumny. Gracz steruje postaci� Rockforda. Jego zadaniem jest zebranie wszystkich diament�w, kt�re znajduj� si� na planszy i opuszczenie jej przez wyj�cie. Opr�cz Rockforda, diament�w i wyj�cia, na polach planszy s� r�wnie�: ziemia, ska�a lub kamie�. Na ka�dym polu mo�e by� co najwy�ej jeden z wymienionych obiekt�w.
Rockford porusza si� po planszy, przechodz�c na jedno z czterech p�l s�siaduj�cych w wierszu lub kolumnie z polem, na kt�rym si� znajduje. Mo�e wej�� na pole docelowe, je�eli spe�niony jest jeden z warunk�w:
�	jest ono puste,
�	jest na nim ziemia,
�	jest na nim diament,
�	jest na nim kamie�, s�siaduje ono z polem Rockforda w wierszu a kolejne pole w tym wierszu, licz�c od strony Rockforda, jest puste,
�	na polu docelowym jest wyj�cie a Rockford zebra� ju� z planszy wszystkie diamenty.
Nie mo�na wi�c wej�� na pole ze ska��, a na pole z wyj�ciem wchodzimy tylko, je�li wcze�niej zebrali�my wszystkie diamenty.
W ka�dym przypadku pole opuszczone przez Rockforda staje si� puste. Rockford, wchodz�c na pole z diamentem, zabiera go a wchodz�c na pole z ziemi� "przekopuje" j� i ziemia znika.
Je�li na polu docelowym jest wyj�cie, Rockford znika z planszy i gra ko�czy si�. Wej�cie Rockforda na pole, na kt�rym jest kamie�, powoduje przesuni�cie kamienia na kolejne, puste pole.
Je�eli bezpo�rednio poni�ej pola, na kt�rym jest kamie� lub diament, czyli w kolejnym wierszu tej samej kolumny, jest pole puste, to ten kamie� lub diament "spada" - jest przenoszony na puste pole poni�ej niego. Stan planszy nazywamy stabilnym, je�li poni�ej �adnego kamienia i poni�ej �adnego diamentu nie ma pustego pola. Przed i po ka�dym ruchu Rockforda wszystkie kamienie i diamenty, kt�re mog� to zrobi� "spadaj�", sprowadzaj�c plansz� do stanu stabilnego.
Inaczej ni� w grze "Boulder Dash", Rockford nie ginie, gdy spadnie na niego kamie� lub diament.
Schematy blokowe:
G��wnego algorytmu:
 	Stabilizuj()
 


Format danych wej�ciowych: Na wej�ciu programu jest, zako�czony pustym wierszem, opis stanu pocz�tkowego planszy, nie koniecznie stabilnego.
Opis planszy sk�ada si� z ci�gu niepustych wierszy, z kt�rych wszystkie s� tej samej d�ugo�ci.
Stan pola jest opisany jednym znakiem:
�	'&' - Rockford,
�	' ' - pole puste,
�	'.' - ziemia,
�	'#' - ska�a,
�	'O' - kamie�,
�	'$' - diament,
�	'X' - wyj�cie.
Na ka�dym polu w pierwszym i w ostatnim wierszu planszy oraz w jej pierwszej i ostatniej kolumnie jest ska�a. Na planszy jest dok�adnie jeden Rockford.
Zak�adamy, �e dane wej�ciowe s� poprawne.
Zak�adamy, �e plansza ma maksymalnie 100 wierszy i maksymalnie 200 kolumn.

Przyk�ad planszy wej�ciowej:
###########
# O#O#O#O##
# $$$$$$$$#
#.#O#O#O#O#
#..... ...#
#&......X.#
###########

Format danych wyj�ciowych: Wynikiem programu jest ko�cowy, stabilny stan planszy. Wypisujemy go w takim samym formacie, jaki mia� stan pocz�tkowy na wej�ciu, po czym wy�wietlana jest plansza z napisem �wygra�e��.

