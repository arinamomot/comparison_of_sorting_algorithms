# Semestrální práce PJC "Porovnání řadicích algoritmů".

## Třídící program příkazového řádku
je nástroj příkazového řádku pro třídění objektů _jakéhokoli datového typu_ (string, char, int, double). Program obsahuje jednovláknovou i vícevláknovou implementaci.

Program čte data ze souboru (input.txt) a vrací seřazená data v souboru (output.txt) pro každý objekt na samostatném řádku od nejmenšího po největší shora dolů.

Každý algoritmus **má své vlákno.** To umožní porovnat pracovní dobu algoritmů.

## Řadící algoritmy

Řadící algoritmy slouží k setřízení jednotlivých prvků vstupního souboru (obvykle seznamu) dle jejich velikosti.

## Definice problému

Na vstupu je posloupnost záznamů: S = (S1, S2,…, Sn); cílem je najít takovou posloupnost S'= (S'1, S'2,…, S'n), pro kterou platí dvě základní kritéria:

1. Tato posloupnost je seřazená:
S'1 ≤ S'2 ≤ … ≤ S'n

2. Posloupnost S' je permutací původní posloupnosti S (obsahuje tedy stejná data, jen v jiném pořadí).

## Použité algoritmy třídění

**Přehled běžných univerzálních algoritmů řazení:**

|Název | Znám jako | Časová složitost(Průměrně) | Dodatečná paměť | Stabilní | Přirozená | Metoda |
| ------------- |:------------------:| -----:| ------------- |:------------------:| -----:|  ------------- |
| Bublinkové řazen | bubble sort | O(n²) | O(1) | ano | ano | záměna |
| Řazení slučováním | merge sort | O(n log n) | O(log n) | ano | ano | slučování |
| Rychlé řazení	| quick sort | O(n log n) | O(log n) | ne | ne | záměna |
| Řazení výběrem	| selection sort | O(n²) | O(1) | zprav. ne | ne | výběr |
| Řazení vkládáním	| insertion sort | O(n²) | O(1) | ano | ano | vkládání |

* **Řazení záměnou:** v souboru se vždy nalezne (nějakou metodou závislou na konkrétním algoritmu) nějaká dvojice prvků, která je ve špatném pořadí, a tyto prvky se navzájem zamění.
* **Řazení slučováním:** Vstupní soubor se rozdělí na části, které se (typicky rekurzivně) seřadí; výsledné seřazené části se poté sloučí takovým způsobem, aby i výsledek byl seřazený.
* **Řazení výběrem:** v souboru se vždy najde nejmenší ze zbývajících položek a uloží na konec postupně budovaného seřazeného souboru.
* **Řazení vkládáním:** ze souboru neseřazených dat se postupně bere položka po položce a vkládá se na správné místo v seřazeném souboru (zpočátku prázdném).

**Běžný algoritm řazení založený na jiném principu:**

|Název | Znám jako | Časová složitost | Dodatečná paměť | Stabilní | Stručný popis metody | 
| ------------- |:------------------:| -----:| ------------- |:------------------:| -----:| 
|Řazení počítáním četností | Counting sort |	O(n + k) | O(k)	| ano | umístění do správného pořadí po spočítání četností jednotlivých hodnot |

## Implementace

Program obsahuje jednovláknovou i vícevláknovou implementaci.

### Jednovláknová
Možnost samostatného spuštění každého typu třídění.
### Vícevláknová 
Možnost současného paralelního spuštění všech typů třídění.
### Popis složek projektu

* main.cpp - pro spuštění programu.
* helpers.cpp - obsahuje všechny funkce nezbytné pro fungování programu.
* generator.hpp - obsahuje funkce pro generování náhodných úvodních dat.
* message.hpp - obsahuje zprávu, která se zobrazí při zadání příkazu "--help" nebo "-h".
* sort.hpp -  rodičovská třída pro třídící třídy.
* sortings - složka, která obsahuje třídy třídění:
  * bubbleSort.cpp
  * countingSort.cpp
  * insertionSort.cpp
  * mergeSort.cpp
  * quickSort.cpp
  * selectionSort.cpp
* input_data - složka, která obsahuje vstupní soubory.
* output_data - složka, která obsahuje vystupní soubory.
* CMakeLists.txt - soubor obsahuje sadu směrnic a pokynů popisujících zdrojové soubory a cíle projektu (spustitelný soubor, knihovny nebo obojí).

## Použití programu

### Nejjednodušší způsob, jak spustit projekt:
1. Naklonovat Projekt do počítače pomocí __git clone__ .
2. Spustit program ve Clion.

*Pak jsou 2 způsoby:* 

1. Otevřit okno "Run/Debug Configurations".
2. Do řádku "Program arguments" zadat argument(y) (argumenty viz. níže). 
3. Spustit program.

Nebo:

1. Otevřit terminál a napsat příkaz "bash" .
2. Napsat příkaz "cmake ." .
3. Napsat příkaz "cmake --build ./ --target all -- -j 3" .
4. Napsat příkaz "./Semestralni_Prace argument". (argumenty viz. níže).

### Příkazy a argumenty
* Pro výpis nápovědy použijte argumenty „-help“ nebo „-h“. 

* Pro generaci data do vstupního souboru(input.txt), musíte zadat příkaz "-g" nebo "--generate" + datový typ + množství pomocí příkazu "-co" nebo "--count":
  * Příklad: "-g string -co 10000" nebo "--generate string --count 10000" 
  <br>

* Pro spuštění paralelního třídění(spouštění všech druhů třídění najednou), musíte zadat příkaz "-p" nebo "--parallel" + datový typ:
  * Příklad: "-p string" nebo "--parallel string" 
  <br>
* Pro spuštění jedného z typů třídění, musíte zadat příkaz:
  * Bubble sort: "-b" nebo "--bubble-sort"
  * Quick sort: "-q" nebo "--quick-sort"
  * Merge sort: "-m" nebo "--merge-sort"
  * Selection sort: "-s" nebo "--selection-sort"
  * Insertion sort: "-in" nebo "--insertion-sort"
  * Counting sort: "-c" nebo "--counting-sort" <br>
+zadat datový typ. <br>
**Pozor! Counting sort funguje pouze s datovými typy INT nebo CHAR.**
    * Příklad: "-b string" nebo "--bubble-sort string" 
  <br>
* Pro nastavení vstupního souboru je třeba zadat příkaz "-i" nebo "--input" + jeho název:
  * Příklad: "-i input.txt" nebo "--input input.txt". 
  * Příklad pro můj projekt: "-i ../input_data/input.txt"
  * Lze použít se všemi typy třídění a s paralelním tříděním. Výchozí je soubor "input.txt" ve složce input_data:
    * Příklad: "-b string -i input2.txt" "-p int -i input2.txt" <br>
  <br>
* Pro nastavení vystupního souboru je třeba zadat příkaz "-o" nebo "--output" + jeho název:
  * Příklad: "-o output.txt" nebo "--output output.txt". 
  * Příklad pro můj projekt: "-o ../output_data/output.txt" 
  * Lze použít se všemi typy třídění. Výchozí je soubor "output.txt" ve složce output_data:
    * Příklad: "-b string -o output2.txt" 
  <br>
* Příklad použití input a output v 1 příkazu: "-b string -i input2.txt -o output2.txt"
* Pro kontrolu správnosti třídění je třeba zadat příkaz "-ch" nebo "--check-sorting" + název souboru + datový typ:
  * Příklad: "-ch bubble_output.txt int" nebo "--check-sorting bubble_output.txt int"
  <br>
* Pro porovnání obsahu dvou souborů je třeba zadat příkaz "-cf" nebo "--comparison-files" + název prvního souboru + název druhého souboru + datový typ:
  * Příklad: "-cf bubble_output.txt quick_output.txt int" nebo "--comparison-files bubble_output.txt quick_output.txt int"
  <br>
* Pro otočení souboru je třeba zadat příkaz "-r" nebo "--reverse" + název souboru + datový typ:
  * Příklad: "-r bubble_output.txt int" "--reverse bubble_output.txt int"
   <br>

* Pro zobrazení obsahu vstupního souboru je třeba zadat příkaz "-si" nebo "--show-input" + název souboru + datový typ:
  * Příklad: "-si input.txt string" nebo "--show-input input.txt string"
  <br>
* Pro zobrazení obsahu vystupního souboru je třeba zadat příkaz "-so" nebo "--show-output" + název souboru + datový typ:
  * Příklad: "-so output.txt string" nebo "--show-output output.txt string"
  <br>
* Pro zjištění počtu objektů v souboru je třeba zadat příkaz "-cnt" nebo "--count-file" + název souboru + datový typ:
  * Příklad: "-cnt output.txt string" nebo "--count-file output.txt string"
  <br>

## Příklady, které lze postupně zkopírovat a použít v programu:

1. Výpis nápovědy: "-h"
2. Generaci: "-g int -co 10000"
3. Paralelní tříděni: "-p int"
4. Otočení jedného z vystupních souborů: "-r ../output_data/bubble_output.txt int"
5. Kontrola spravnosti třídění jedného z vystupních souborů: "-ch ../output_data/insertion_output.txt int"
6. Porovnaní dvou z vystupních souborů: "-cf ../output_data/merge_output.txt ../output_data/selection_output.txt int"
7. Zjištění kolik objektů jsou ve souboru: "-cnt ../output_data/quick_output.txt int"
8. Zobrazení obsahu vstupního souboru: "-si ../input_data/input.txt int"
9. Zobrazení obsahu vystupního souboru "-so ../output_data/counting_output.txt int"

## Časové porovnání třídění

Měření proběhlo na notebooku s 2.5 GHz Intel(R) Core(TM) i5-7200U CPU (2 jádra).

### INT

Pomocí funkce generování (-g int -co 90.000) byl vytvořen soubor input.txt, který obsahuje 90.000 celých čísel v rozsahu (-1000000, 1000000).

|Název |Znám jako | Čas třídění (ms) | Čas třídění (s) | Správnost třídění | Pořadí dokončení třídění.|
| ------------- |:------------------:| -----:| -----:| -----:|-----:| 
| Bublinkové řazen | bubble sort | 76478 | 76,478 | správně | 6 |
| Řazení slučováním | merge sort | 426 | 0,426 | správně | 2 |
| Rychlé řazení	| quick sort | 3653 | 3,653 | správně | 3 |
| Řazení výběrem	| selection sort | 39747 | 39,747 | správně | 5 |
| Řazení vkládáním	| insertion sort | 30496 | 30,496 | správně | 4 |
| Řazení počítáním četností | Counting sort | 136 | 0,136 | správně | 1 |

### CHAR

Pomocí funkce generování (-g char -co 90.000) byl vytvořen soubor input.txt, který obsahuje 90.000 znaků.

|Název |Znám jako | Čas třídění (ms) | Čas třídění (s) | Správnost třídění | Pořadí dokončení třídění.|
| ------------- |:------------------:| -----:| -----:| -----:|-----:| 
| Bublinkové řazen | bubble sort | 74829 | 74,829 | správně | 6 |
| Řazení slučováním | merge sort | 390 | 0,39 | správně | 2 |
| Rychlé řazení	| quick sort | 3292 | 3,292 | správně | 3 |
| Řazení výběrem	| selection sort | 39362 | 39,362 | správně | 5 |
| Řazení vkládáním	| insertion sort | 30288 | 30,288 | správně | 4 |
| Řazení počítáním četností | Counting sort | 6 | 0,006 | správně | 1 |

### STRING

Pomocí funkce generování (-g string -co 10.000) byl vytvořen soubor input.txt, který obsahuje 10.000 řádků různé délky.

|Název |Znám jako | Čas třídění (ms) | Čas třídění (s) | Správnost třídění | Pořadí dokončení třídění.|
| ------------- |:------------------:| -----:| -----:| -----:|-----:| 
| Bublinkové řazen | bubble sort | 5606 | 5,606 | správně | 4 |
| Řazení slučováním | merge sort | 205 | 0,205 | správně | 1 |
| Rychlé řazení	| quick sort | 36682 | 36,682 | správně | 5 |
| Řazení výběrem	| selection sort | 2062 | 2,062 | správně | 2 |
| Řazení vkládáním	| insertion sort | 2182 | 2,182 | správně | 3 |

### DOUBLE

Pomocí funkce generování (-g double -co 100.000) byl vytvořen soubor input.txt, který obsahuje 100.000 ne celá čísla v rozsahu (-1000000, 1000000).

|Název |Znám jako | Čas třídění (ms) | Čas třídění (s) | Správnost třídění | Pořadí dokončení třídění.|
| ------------- |:------------------:| -----:| -----:| -----:|-----:| 
| Bublinkové řazen | bubble sort | 98956 | 98,956 | správně | 5 |
| Řazení slučováním | merge sort | 391 | 0,391 | správně | 1 |
| Rychlé řazení	| quick sort | 7016 | 7,016 | správně | 2 |
| Řazení výběrem	| selection sort | 50615 | 50,615 | správně | 4 |
| Řazení vkládáním	| insertion sort | 39011 | 39,011 | správně | 3 |
