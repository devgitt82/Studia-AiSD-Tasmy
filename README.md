# Taśmy.

### Zadanie  z przedmiotu AiSD na drugim semestrze studiów, programowanie proceduralne bez STL.


> Pewna firma produkuje taśmy z kolejnymi numerkami (dla urzędów pocztowych, banków itp.). Każda taśma jest podzielona na prostokąty z kolejnymi numerami, rozpoczynając od 0. Zaczął się nowy rok i jej klienci uzupełniają zapasy. Każdy z nich przysłał zamówienie w postaci pary a, b, gdzie a to numer początkowy a b to numer końcowy fragmentu taśmy, który jest mu potrzebny. Firma optymalizuje koszty więc chce zużyć jak najmniejszą liczbę taśm.


**Wejście**
---

>Na wejściu programu zostanie podana liczba zamówień (nie będzie większa niż 100000) oraz zamówienia w postaci par a b (każde w osobnej linii (0 ≤ a < b < 2000000000).

**Wyjście**
---
    
>Na wyjściu należy wypisać minimalną liczbę taśm potrzebnych do zrealizowania zamówienia oraz te zamówienia, których anulowanie zmniejszy liczbę wymaganych taśm. Zamówienia powinny być uporządkowane względem numeru początkowego, oraz numeru końcowego (w przypadku takich samych numerów początkowych).

**Przykłady**
---


**Wejście**
```
6
0 10
1 9
2 8
3 7
4 6
5 5
```

**Wyjście**
```
6
0 10
1 9
2 8
3 7
4 6
5 5
```

---

**Wejście**
```
10
0 10
11 12
9 12
8 13
12 13
1 2
3 4
5 6
1 3
4 6
```

**Wyjście**
```
4
8 13
9 12
11 12
12 13
```
