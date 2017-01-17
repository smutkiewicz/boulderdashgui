# boulderdashgui
Gra "Klątwa Boulder Dasha" + GUI ze sterowaniem

Komputerowa gra logiczna Boulder Dash z GUI przy użyciu biblioteki ncurses.

Definicje pojęć: Boulder Dash (https://en.wikipedia.org/wiki/Boulder_Dash) to komputerowa gra logiczno-zręcznościowa. Tematem zadania jest jej wariant, pozbawiony elementów zręcznościowych.
Ncurses – kontynuacja biblioteki curses z BSD. Dostarcza ona funkcji do obsługi terminala tekstowego niezależnie od jego typu (korzysta z terminfo lub termcap), z optymalizacją (ekran nie jest odrysowywany w całości). Umożliwia ona tworzenie aplikacji z interfejsem przypominającym interfejs graficzny. (źródło: Wikipedia.org)

Zasady gry:
Rozgrywka "Boulder Dasha" toczy się na prostokątnej planszy, której pola są zorganizowane w wiersze i kolumny. Gracz steruje postacią Rockforda. Jego zadaniem jest zebranie wszystkich diamentów, które znajdują się na planszy i opuszczenie jej przez wyjście. Oprócz Rockforda, diamentów i wyjścia, na polach planszy są również: ziemia, skała lub kamień. Na każdym polu może być co najwyżej jeden z wymienionych obiektów.
Rockford porusza się po planszy, przechodząc na jedno z czterech pól sąsiadujących w wierszu lub kolumnie z polem, na którym się znajduje. Może wejść na pole docelowe, jeżeli spełniony jest jeden z warunków:

•	jest ono puste,
•	jest na nim ziemia,
•	jest na nim diament,
•	jest na nim kamień, sąsiaduje ono z polem Rockforda w wierszu a kolejne pole w tym wierszu, licząc od strony Rockforda, jest puste,
•	na polu docelowym jest wyjście a Rockford zebrał już z planszy wszystkie diamenty.
Nie można więc wejść na pole ze skałą, a na pole z wyjściem wchodzimy tylko, jeśli wcześniej zebraliśmy wszystkie diamenty.
W każdym przypadku pole opuszczone przez Rockforda staje się puste. Rockford, wchodząc na pole z diamentem, zabiera go a wchodząc na pole z ziemią "przekopuje" ją i ziemia znika.
Jeśli na polu docelowym jest wyjście, Rockford znika z planszy i gra kończy się. Wejście Rockforda na pole, na którym jest kamień, powoduje przesunięcie kamienia na kolejne, puste pole.
Jeżeli bezpośrednio poniżej pola, na którym jest kamień lub diament, czyli w kolejnym wierszu tej samej kolumny, jest pole puste, to ten kamień lub diament "spada" - jest przenoszony na puste pole poniżej niego. Stan planszy nazywamy stabilnym, jeśli poniżej żadnego kamienia i poniżej żadnego diamentu nie ma pustego pola. Przed i po każdym ruchu Rockforda wszystkie kamienie i diamenty, które mogą to zrobić "spadają", sprowadzając planszę do stanu stabilnego.
Inaczej niż w grze "Boulder Dash", Rockford nie ginie, gdy spadnie na niego kamień lub diament.

Format danych wejściowych: Na wejściu programu jest, zakończony pustym wierszem, opis stanu początkowego planszy, nie koniecznie stabilnego.
Opis planszy składa się z ciągu niepustych wierszy, z których wszystkie są tej samej długości.
Stan pola jest opisany jednym znakiem:
•	'&' - Rockford,
•	' ' - pole puste,
•	'.' - ziemia,
•	'#' - skała,
•	'O' - kamień,
•	'$' - diament,
•	'X' - wyjście.
Na każdym polu w pierwszym i w ostatnim wierszu planszy oraz w jej pierwszej i ostatniej kolumnie jest skała. Na planszy jest dokładnie jeden Rockford.
Zakładamy, że dane wejściowe są poprawne.
Zakładamy, że plansza ma maksymalnie 100 wierszy i maksymalnie 200 kolumn.

Przykład planszy wejściowej:
###########
# O#O#O#O##
# $$$$$$$$#
#.#O#O#O#O#
#..... ...#
#&......X.#
###########

Format danych wyjściowych: Wynikiem programu jest końcowy, stabilny stan planszy. Wypisujemy go w takim samym formacie, jaki miał stan początkowy na wejściu, po czym wyświetlana jest plansza z napisem „wygrałeś”.

