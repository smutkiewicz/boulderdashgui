Student:	Micha³ Smutkiewicz (T2)
		msmutkie@elka.pw.edu.pl
Prowadz¹cy:  	mgr in¿. Andrzej Wojeñski
Podstawy Programowania (PRM) – projekt
specyfikacja funkcjonalna
Temat: Komputerowa gra logiczna Boulder Dash z GUI przy u¿yciu biblioteki ncurses.
Definicje pojêæ: Boulder Dash (https://en.wikipedia.org/wiki/Boulder_Dash) to komputerowa gra logiczno-zrêcznoœciowa. Tematem zadania jest jej wariant, pozbawiony elementów zrêcznoœciowych.
Ncurses – kontynuacja biblioteki curses z BSD. Dostarcza ona funkcji do obs³ugi terminala tekstowego niezale¿nie od jego typu (korzysta z terminfo lub termcap), z optymalizacj¹ (ekran nie jest odrysowywany w ca³oœci). Umo¿liwia ona tworzenie aplikacji z interfejsem przypominaj¹cym interfejs graficzny. (Ÿród³o: Wikipedia.org)
Zasady gry:
Rozgrywka "Boulder Dasha" toczy siê na prostok¹tnej planszy, której pola s¹ zorganizowane w wiersze i kolumny. Gracz steruje postaci¹ Rockforda. Jego zadaniem jest zebranie wszystkich diamentów, które znajduj¹ siê na planszy i opuszczenie jej przez wyjœcie. Oprócz Rockforda, diamentów i wyjœcia, na polach planszy s¹ równie¿: ziemia, ska³a lub kamieñ. Na ka¿dym polu mo¿e byæ co najwy¿ej jeden z wymienionych obiektów.
Rockford porusza siê po planszy, przechodz¹c na jedno z czterech pól s¹siaduj¹cych w wierszu lub kolumnie z polem, na którym siê znajduje. Mo¿e wejœæ na pole docelowe, je¿eli spe³niony jest jeden z warunków:
•	jest ono puste,
•	jest na nim ziemia,
•	jest na nim diament,
•	jest na nim kamieñ, s¹siaduje ono z polem Rockforda w wierszu a kolejne pole w tym wierszu, licz¹c od strony Rockforda, jest puste,
•	na polu docelowym jest wyjœcie a Rockford zebra³ ju¿ z planszy wszystkie diamenty.
Nie mo¿na wiêc wejœæ na pole ze ska³¹, a na pole z wyjœciem wchodzimy tylko, jeœli wczeœniej zebraliœmy wszystkie diamenty.
W ka¿dym przypadku pole opuszczone przez Rockforda staje siê puste. Rockford, wchodz¹c na pole z diamentem, zabiera go a wchodz¹c na pole z ziemi¹ "przekopuje" j¹ i ziemia znika.
Jeœli na polu docelowym jest wyjœcie, Rockford znika z planszy i gra koñczy siê. Wejœcie Rockforda na pole, na którym jest kamieñ, powoduje przesuniêcie kamienia na kolejne, puste pole.
Je¿eli bezpoœrednio poni¿ej pola, na którym jest kamieñ lub diament, czyli w kolejnym wierszu tej samej kolumny, jest pole puste, to ten kamieñ lub diament "spada" - jest przenoszony na puste pole poni¿ej niego. Stan planszy nazywamy stabilnym, jeœli poni¿ej ¿adnego kamienia i poni¿ej ¿adnego diamentu nie ma pustego pola. Przed i po ka¿dym ruchu Rockforda wszystkie kamienie i diamenty, które mog¹ to zrobiæ "spadaj¹", sprowadzaj¹c planszê do stanu stabilnego.
Inaczej ni¿ w grze "Boulder Dash", Rockford nie ginie, gdy spadnie na niego kamieñ lub diament.
Schematy blokowe:
G³ównego algorytmu:
 	Stabilizuj()
 


Format danych wejœciowych: Na wejœciu programu jest, zakoñczony pustym wierszem, opis stanu pocz¹tkowego planszy, nie koniecznie stabilnego.
Opis planszy sk³ada siê z ci¹gu niepustych wierszy, z których wszystkie s¹ tej samej d³ugoœci.
Stan pola jest opisany jednym znakiem:
•	'&' - Rockford,
•	' ' - pole puste,
•	'.' - ziemia,
•	'#' - ska³a,
•	'O' - kamieñ,
•	'$' - diament,
•	'X' - wyjœcie.
Na ka¿dym polu w pierwszym i w ostatnim wierszu planszy oraz w jej pierwszej i ostatniej kolumnie jest ska³a. Na planszy jest dok³adnie jeden Rockford.
Zak³adamy, ¿e dane wejœciowe s¹ poprawne.
Zak³adamy, ¿e plansza ma maksymalnie 100 wierszy i maksymalnie 200 kolumn.

Przyk³ad planszy wejœciowej:
###########
# O#O#O#O##
# $$$$$$$$#
#.#O#O#O#O#
#..... ...#
#&......X.#
###########

Format danych wyjœciowych: Wynikiem programu jest koñcowy, stabilny stan planszy. Wypisujemy go w takim samym formacie, jaki mia³ stan pocz¹tkowy na wejœciu, po czym wyœwietlana jest plansza z napisem „wygra³eœ”.

