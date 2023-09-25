#include <iostream>

using namespace std;

struct Szamowienie{
    int p;
    int ko;
  };

void scal(Szamowienie **Wsk_na_elem, Szamowienie **pom, int l_index, int s_index, int p_index);              //FUNKCJA SCALAJACA DO PONIZSZEGO
void sortowanie_przez_scalanie(Szamowienie **Wsk_na_elem, Szamowienie **pom, int l_index, int p_index);      //SORTOWANIE WSK DO STRUKTUR

void scal2(int **Wsk_na_pole_kon, int **pom2, int l_index, int s_index, int p_index);                        //FUNKCJA SCALAJACA DO PONIZSZEGO
void sortowanie_przez_scalanie2(int **Wsk_na_pole_kon, int **pom2, int l_index, int p_index);                //SORTOWANIE WSK DO POLA ko

Szamowienie * kiedy_najgrubsza (Szamowienie **Wsk_na_elem, int **Wsk_na_pole_kon, int *max_grub, int n);    //FUNKCJA SZUKAJACA KIEDY JEST "NAJWIEKSZE ZAPOTRZEBOWANIE"

/****************************************************************************************************************************************************************************************************/
int main(){

  int n;

  while( cin >> n ){

    Szamowienie  *tab_elem;
    Szamowienie  *kiedy_max;

    Szamowienie **Wsk_na_elem;
    Szamowienie **pom;

    int         ** Wsk_na_pole_kon;
    int         ** pom2;
    int         max_grub;

   //TWORZENIE TABLIC DYNAMICZNYCH                     ( zwolniona pamiec na koncu maina)

    tab_elem            = new Szamowienie[n];           //dyn tablica struktur

    Wsk_na_elem         = new Szamowienie*[n];          //dyn tablica wsk do struktur
    pom                 = new Szamowienie*[n];          //pomocnicza  dyn tablica wsk do struktur

    Wsk_na_pole_kon     = new int*[n];                  //dyn tablica wskaznikow do inta
    pom2                = new int*[n];                  //pomocnicza dyn tablica wskaznikow do inta


   //INPUT DO TABLIC
        for (int i=0; i<n; i++) {
            cin >> tab_elem[i].p;
            cin >> tab_elem[i].ko;
            Wsk_na_elem[i]       = &tab_elem[i];
            Wsk_na_pole_kon[i]   = &tab_elem[i].ko;
        }

    //SORTOWANIE
    sortowanie_przez_scalanie(Wsk_na_elem, pom, 0,n-1);             // SORTOWANIE WSKAZNIKOW DO STRUKTUR PO KLUCZU p ORAZ KLUCZU ko
    sortowanie_przez_scalanie2(Wsk_na_pole_kon, pom2, 0,n-1);       // SORTOWANIE WSKAZNIKOW DO SAMEGO POLA ko

    //SZUKANIE MIEJSCA GDY "GRUBOSC" JEST NAJWIEKSZA TJ. WYZNACZANIE MINIMALNEJ ILOSCI TASM BY SPROSTAC WSZYSTKIM ZAMOWIENIOM
    kiedy_max = kiedy_najgrubsza (Wsk_na_elem, Wsk_na_pole_kon, &max_grub, n);

    //WYPIS

      //GRUBOSCI
      cout << max_grub << "\n";

      //ZAMOWIEN KTORYCH ZMNIEJSZENIE SPOWODUJE ZMNIEJSZENIE ILOSCI TASM DO WYPRODUKOWANIA

      for (int i=0; i<n; i++){
          if (  ((Wsk_na_elem[i]->p ) <= kiedy_max->p )   &&    ((Wsk_na_elem[i]->ko ) >= kiedy_max->p)  )       // GDY POCZATEK TASM JEST PRZED LUB W MOMENCIE STARTU MAX_GRUB,
            cout << (Wsk_na_elem[i]->p ) << " " << (Wsk_na_elem[i]->ko ) << "\n";                                       // ORAZ GDY KONIEC TYCH TASM TEZ JEST W MOMENCIE STARTU LUB ZA STARTEM
      }                                                                                                          // TO WYPISUJ

    delete [] tab_elem;
    delete [] Wsk_na_elem;
    delete [] pom;
    delete [] Wsk_na_pole_kon;
    delete [] pom2;

    }   //KONIEC WHILE

           return 0;

} //KONIEC MAINA

/**************************************************************************************************************************************************************************************************/
//SORTOWANIE WSK DO STRUKTUR


void sortowanie_przez_scalanie(Szamowienie **Wsk_na_elem, Szamowienie **pom, int l_index, int p_index)
{
        if(p_index <= l_index) return;              //jak zostal jeden element, to koniec sortowania
        int s_index = (p_index + l_index) / 2;      //jak wiecej niz jeden element to znajdujemy srodek obecnej podtablicy

        sortowanie_przez_scalanie(Wsk_na_elem,pom, l_index, s_index);       //rekurencyjnie sortujemy osobno 1 polowe
        sortowanie_przez_scalanie(Wsk_na_elem,pom, s_index+1 , p_index);    //rekurencyjnie sortujemy osobno 2 polowe

        scal(Wsk_na_elem, pom, l_index, s_index, p_index);                  //po czym scalamy obie polowy (ostatecznie scalimy caly ciag do posortowania)
}

/***************************************************************************************************************************************************************************************/
//SCALANIE DO POWYZSZEJ FUNKCJI


void scal(Szamowienie **Wsk_na_elem, Szamowienie **pom, int l_index, int s_index, int p_index)
{
        int i = l_index;                                               // lewy pierwszej polowy
        int j = s_index + 1;                                           // lewy drugiej polowy (liczymy druga polowe od srodka + 1)

    for(int i = l_index; i <= p_index; i++)                          // do pomocniczej tablicy wskaznikow na struktury kopiuje zakres wskaznikow z jakim wszedlem
         pom[i] = Wsk_na_elem[i];

//GLOWNA TRESC SCALANIA
    for(int k = l_index; k <= p_index; k++)                         //od lewego do prawego wskaznika struktur  - w danym zakresie (od l_indexu do p_indexu)
       if (i <= s_index)                                        //gdy lewy pierwszej polowy nie dojechal jeszcze do srodka przedzialu (lacznie z srodkiem)
             if (j <= p_index){                                 //oraz gdy lewy drugiej polowy nie dojechal do konca prawej strony to


                     if (pom[j]->p < pom[i]->p)                           //jesli poczatek tasmy zapisany w lewym 2 polowy, jest mniejszy, niz poczatek tasmy zapisany w lewym 1 polowy
                             Wsk_na_elem[k] = pom[j++];                   //to w kolejne miejsce w posortowanym ciagu wskaznikow tasm(o obecnym zakresie) , wpisz wskaznik, w ktorym znajduje sie
                                                                          //poczatek tasmy, zapisany w lewym 2 polowy. Potem zwieksz indeks lewego 2 polowy.

                     else if ((pom[j]->p == pom[i]->p) && (pom[j]->ko >= pom[i]->ko))   //jesli poczatki w obu lewych sa rowne, i gdy koniec zapisany w lewym 2 polowy jest wiekszy od konca zapisanego w
                                     Wsk_na_elem[k] = pom[i++];                         //lewym 1 polowy, tzn ze lewy 1 polowy jest wlasciwym lewym. Potem zwieksz indeks lewego 1 polowy.

                     else if  ((pom[j]->p == pom[i]->p) && (pom[j]->ko < pom[i]->ko))   //jesli poczatki w obu lewych sa rowne, i gdy koniec zapisany w lewym 2 polowy jest mniejszy od konca zapisanego w
                                         Wsk_na_elem[k] = pom[j++];                     //lewym 1 polowy, tzn ze lewy 2 polowy jest wlasciwym lewym. Potem zwieksz indeks lewego 2 polowy.
                     else
                               Wsk_na_elem[k] = pom[i++];                               //jesli poczatek tasmy w lewym 2 polowy jest wiekszy niz poczatek zapisany w lewym 1 polowy
                                                                                        //to do posortowanego ciagu wskaznikow wpisz lewy 1 polowy. Potem zwieksz indeks lewego 1 polowy.
                    }
             else
                 Wsk_na_elem[k] = pom[i++];              //jak dobilismy juz do przwego brzegu w 2 polowie to do posortowanego ciagu przepisz to co pozostalo w 1 polowie
       else
          Wsk_na_elem[k] = pom[j++];                     //jesli dobilismy juz do przwego brzegu w 1 polowie to do posortowanego ciagu przepisz to co pozostalo w 2 polowie
}

/***********************************************************************************************************************************************************/
//FUNKCJE SORTUJACE I SCALAJACE DLA POLA KONIEC (TO POTRZEBNE DO WYZNACZANIA KOLEJNOSCI ZDARZEN), ANALOGICZNE JAK WYZEJ, ALE SORTUJEMY WSK DO INTOW A NIE STRUKTUR

void sortowanie_przez_scalanie2(int **Wsk_na_pole_kon, int **pom2, int l_index, int p_index){
    if(p_index <= l_index) return;
        int s_index = (p_index + l_index) / 2;

        sortowanie_przez_scalanie2(Wsk_na_pole_kon,pom2, l_index, s_index);
        sortowanie_przez_scalanie2(Wsk_na_pole_kon,pom2, s_index+1 , p_index);


        scal2(Wsk_na_pole_kon, pom2, l_index, s_index, p_index);
}

/***********************************************************************************************************************************************************/
//SCALANIE KROTSZE NIZ WCZESNIEJ BO TU NIE MA ZNACZENIA ZE OBA INTY SA TAKIE SAME, (NIE MUSIMY PISAC CO WOWCZAS)

void scal2(int **Wsk_na_pole_kon, int **pom2, int l_index, int s_index, int p_index){
    int i = l_index;
        int j = s_index + 1;

    for(int i = l_index; i <= p_index; i++)
        pom2[i] = Wsk_na_pole_kon[i];


    for(int k = l_index; k <= p_index; k++)
        if (i <= s_index)
        {
             if (j <= p_index)
             {
                   if (*pom2[j] < *pom2[i])
                          Wsk_na_pole_kon[k] = pom2[j++];
                   else
                          Wsk_na_pole_kon[k] = pom2[i++];
             }
             else
                   Wsk_na_pole_kon[k] = pom2[i++];
       }
        else
            Wsk_na_pole_kon[k] = pom2[j++];
}

/****************************************************************************************************************/
//SZUKAMY KIEDY JEST MOMENT O NAJWIEKSZEJ LICZBIE POCZATKOW, ABY WIEDZIEC ILE TASM POTRZEBUJEMY oRAZ JAKIE ZAMOWIENIA EWENTUALNIE ANULOWAC

Szamowienie *kiedy_najgrubsza (Szamowienie **Wsk_na_elem, int **Wsk_na_pole_kon, int *max_grub, int n){

    int grub = 0;
    *max_grub = 0;                          // poczatkowo 0, weszlismy z tym do funkcji przez wskaznik
    int i = 0;
    int j = 0;
    struct Szamowienie * kiedy_najg;        // tymczasowy wskaznik do struktur
    kiedy_najg = Wsk_na_elem[0];            // poczatkowo jest wskaznikiem na 1 wskaznik w tablicy

    //SKORO SORTOWANIE ZAKONCZONE TO SPRAWDZAMY JAKA BYLA KOLEJNOSC ZDARZEN
    while (i < n && j < n)
    {
        //JESLI POCZATEK TO
        if ( Wsk_na_elem[i]->p  <=  *Wsk_na_pole_kon[j]){
            grub++;                                                 // zwieksz grubosc
            if (grub > *max_grub){                                  // porownaj z maksymalna gruboscia
               *max_grub = grub;                                    // jak wieksza to mamy nowa maxymalna grubosc
               kiedy_najg = Wsk_na_elem[i];                         // i zapamietujemy w ktorym wskazniku(momencie) wystepuje max grubosc
            }
            i++;
        }
        //JESLI KONIEC TO
        else{
           grub--;                                                  // zmniejsz grubosc
           j++;
        }
   }
   return kiedy_najg;                                               // zwroc moment max grubosci
}