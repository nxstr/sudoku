# sudoku



## Popis projektu

Projekt je implementaci hry Sudoku.
Hráč zadává do příkazové Radky povolené příkazy, na zaklade kterých program bude něco dělat.
Hra používá klasická pravidla Sudoku: jsou povolené číslice od 1 do 9, které se nesmí opakovat v jedněm čtverce, v jednem radku a v jednem sloupci.
Taky, program nabízí uživateli vyber složitosti hry, jsou tři varianty: easy, medium, hard.
Složitost označí generátoru hry, kolik známých číslic bude na začátku hry.

## Spuštění a přepínače

Hra se spoušti z příkazové řádky příkazem `./sudoku`
bez žadných parametrů.
(P.S.: zkoušela jsem spustit program jenom na windows a na mac os, na linuxu bohužel ne, proto nevím, jestli tam spuštěni je úplně stejné.
CMakeLists jsem udělala podle ukázkové hry tic tac toe, proto spuštěni by mělo byt asi stejné, jenom s použitím slova "sudoku" místo "Piskvorky")

Po zadaní tohoto příkazu v příkazove řadce se objeví první otazka: "Do you want to start new game(n) or load saved(l)? n/l",
pokud příkaz `l` - načte se poslední uložena hra, pokud uživatel zadá příkaz `n`, zgeneruje se nova hra a další otázka programu bude ohledně složitosti hry.
## Ovládání programu

Po nastaveni prvních výběru z předchozího kroku načte se deska.
a hráč má zadat následující data: souřadnice a hodnotu "kamenu".
Například, příkaz `1 2 3` bude znamenat, ze leva souřadnice se rovna 1, horní souřadnice se rovna 2, hodnota číslice které uživatel chci umístit je 3.

Program zkontroluje jestli vstup je validní a pokud ano - přidá číslice na desku.
Předem známa číslici (které se nedá změnit) jsou vypsané bílou barvou.
Číslici které přidává uživatel jsou vypsané zelenou barvou, a uživatel je může kdykoliv měnit.

Příkaz `save` uloží momentální stav hry do souboru saved.txt

Příkaz `solve` zavolá automatické vyřešeni desky, pokud řešeni existuje - vypíše výslednou desku, pokud ne - vypíše hlášku, že deska už řešeni nemá.
Po zavolaní tohoto příkazu program se automaticky ukonči.

Příkaz `quit` ukonči program.

Program se skonči automaticky, když nebude zadně prázdné místo na desce.
