# sudoku



## Popis projektu

Projekt je implementaci hry Sudoku.
Hrac zadava do prikazove radky povolene prikazy, na zaklade kterych program bude neco delat.
Hra pouziva klasicka pravidla Sudoku: jsou povolene cislice od 1 do 9, ktere se nesmi opakovat v jednem ctverce, v jednem radku a v jednem sloupci.
Taky, program nabizi uzivateli vyber slozitosti hry, jsou tri varianty: easy, medium, hard.
Slozitost oznaci generatoru hry, kolik znamych cislic bude na zacatku hry.

## Spuštění a přepínače

Hra se spousti z prikazove radky prikazem `./sudoku`
bez zadnych parametru.
(P.s.: zkousela jsem spustit program jenom na windows a na mac os, na linuxu bohuzel ne, proto nevim, jestli tam spusteni je uplne stejne.
CMakeLists jsem udelala podle ukazkove hry tic tac toe, proto spusteni by melo byt asi stejne, jenom s pouzitim slova "sudoku" misto "Piskvorky")

Po zadani tohoto prikazu v prikazove radce se objevi prvni otazka: "Do you want to start new game(n) or load saved(l)? n/l",
pokud prikaz `l` - nacte se posledni ulozena hra, pokud uzivatel zada prikaz `n`, zgeneruje se nova hra a dalsi otazka programu bude ohledne slozitosti hry.

## Ovládání programu

Po nastaveni prvnich vyberu z predchoziho kroku nacte se deska.
a hrac ma zadat nasledujici data: souradnice a hodnotu "kamenu".
Napriklad prikaz `1 2 3` bude znamenat, ze leva souradnice se rovna 1, horni souradnice se rovna 2, hodnota cislice ktere uzivatel chci umistit je 3.

Program zkontroluje jestli vstup je validni a pokud ano - prida cislice na desku.
Predem zname cislice (ktere se neda zmenit) jsou vypsane bilou barvou.
Cislice ktere pridava uzivatel jsou vypsane zelenou barvou, a uzivatel je muze kdykoliv menit.

Prikaz `save` ulozi momentalny stav hry do souboru saved.txt

Prikaz `solve` zavola automaticke vyreseni desky, pokud reseni existuje - vypise vyslednou desku, pokud ne - vypise hlasku ze deska uz reseni nema.
Po zavolani tohoto prikazu program se automaticky ukonci.

Prikaz `quit` ukonci program.

Program se skonci automaticky, kdyz nebude zadne prazdne misto na desce.
