/*
Meno a priezvisko: Erik Poczos

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <algorithm>
#include <initializer_list>

using namespace std;

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati priemernu hodnotu prvkov vstupneho inicializacneho zoznamu.
    Ak inicializacny zoznam neobsahuje ziadne prvky, tak vyhodi vynimku typu 'std::invalid_argument',
    ktorej metoda 'what' vrati textovy retazec: "inicializacny zoznam je prazdny".

    Na vypocet sumy cisiel, v implementacii pouzite 'std::accumulate'.

    PARAMETER:
        [in] data - zoznam prvkov

    NAVRATOVA HODNOTA:
        Priemerna hodnota prvkov vstupneho inicializacneho zoznamu

    VYNIMKA:
        Ak je inicializacny zoznam prazdny, tak funkcia vyhodi vynimku typu 'std::invalid_argument',
        ktorej metoda 'what' vrati vysvetlujuci popis: "inicializacny zoznam je prazdny" (dodrzte presne tento textovy retazec! (ctrl+c, ctrl+v))
*/

double average(const initializer_list<int> & data) {
    if (empty(data)){
        throw invalid_argument("inicializacny zoznam je prazdny");
    }
    double sum = accumulate(data.begin(), data.end(), 0);
    return sum/data.size(); // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati iterator na 1. prvok zoznamu 'data' obsahujuci hodnotu 'value'.
    Pozor na pripad, ked 'data' obsahuje viac prvkov s hodnotou 'value'.

    V implementacii pouzite 'std::find'.

    PARAMETRE:
        [in] data - zoznam, v ktorom funkcia hlada 1. vyskyt hodnoty 'value'
        [in] value - hodnota hladaneho prvku

    NAVRATOVA HODNOTA:
        Ak 'data' obsahuje prvok s hodnotou 'value', tak vrati konstantny iterator na 1. takyto prvok.
        Inak vrati iterator za posledny prvok 'data' (iterator 'data.cend()')
*/

list<int>::const_iterator findValue(const list<int> & data, int value) noexcept {
    auto it = std::find(data.begin(), data.end(),value);
    if (it != data.end())
        return it;

    return data.cend(); // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati iterator na 1. prvok, ktoreho hodnota je v rozsahu <200, 400> (vratane 200 a 400).

    V implementacii pouzite funkciu 'std::find_if'.
    Pri jej volani pouzite ako jeden z argumentov funkciu 'isInRange200to400'.

    PARAMETER:
        [in] data - zoznam, v ktorom sa hlada 1. vyskyt hodnoty v rozsahu <200, 400>

    NAVRATOVA HODNOTA:
        Ak 'data' obsahuje prvok/prvky v rozsahu <200,400>, tak vrati iterator na 1. takyto prvok.
        Inak vrati iterator za posledny prvok (iterator 'data.cend()').
*/

bool isInRange200to400(const int element) noexcept {
    return element >= 200 && element <= 400;
}

list<int>::const_iterator findInRange200to400(const list<int> & data) noexcept {
    auto it = find_if(data.begin(), data.end(), isInRange200to400);
    if (it != data.end())
        return it;

    return data.cend(); // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia v zozname 'data' nahradi vsetky hodnoty v rozsahu <200, 400> (vratane 200 a 400), hodnotou 5.

    V implementacii pouzite funkciu 'std::replace_if'.
    Pri jej volani pouzite ako jeden z argumentov funkciu 'isInRange200to400' (definovanu v zadani predchadzajucej ulohy).

    PARAMETER:
        [in, out] data - zoznam, v ktorom funkcia nahradi vsetky hodnoty v rozsahu <200, 400>, hodnotou 5
*/

void replace200to400by5(list<int> & data) noexcept {
    replace_if(data.begin(), data.end(), isInRange200to400, 5);
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zvysi hodnotu kazdeho prvku vstupneho zoznamu o 1 (ku kazdej hodnote pripocita 1).

    V implementacii pouzite funkciu 'std::transform'.
    Pri jej volani pouzite ako jeden z argumentov funkciu 'increment'.

    PARAMETER:
        [in, out] data - zoznam, v ktorom funkcia zvysi hodnotu kazdeho prvku o 1
*/

int increment(int element) noexcept {
    return element + 1;
}

void incrementAll(list<int> & data) noexcept {
    transform(data.begin(), data.end(),data.begin(), increment);
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//----------------------------------------------------------------------------------------------
/*
    Vstupny zoznam obsahuje celkovy pocet bodov z predmetu, pre kazdeho studenta.
    Ak je pocet bodov teste pod hranicou na lepsiu znamku (do lepsej znamky chyba 1 bod),
    tak funkcia zvysi pocet bodov o 1.
    Inak funkcia nezmeni pocet bodov.

    V implementacii pouzite funkciu 'std::transform'.
    Pri jej volani pouzite ako jeden z argumentov  funkciu 'incrementPointsIfItHelps'.

    PARAMETER:
        [in, out] points - celkovy pocet bodov z predmetu pre kazdeho studenta
                           (niektore mozu byt po vykonani funkcie inkrementovane)

    PRIKLAD:
        vstup:  { 100, 90, 91, 92, 93, 53, 54, 55, 56, 57, 91, 92 }
        vystup: { 100, 90, 92, 92, 93, 53, 54, 56, 56, 57, 92, 92 }
                            ^                   ^           ^
*/

int incrementPointsIfItHelps(int points) noexcept {
    switch (points) {
        case 91 :
            return 92;
        case 82:
            return 83;
        case 73:
            return 74;
        case 64:
            return 65;
        case 55:
            return 56;
        default:
            return points;
    }
}

void helpAfterExam1(list<int> & points) noexcept {
    transform(points.begin(), points.end(), points.begin(), incrementPointsIfItHelps);
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//----------------------------------------------------------------------------------------------
/*
    Implementujte rovnaku funkcionalitu ako v predchadzajucej ulohe,
    ale namiesto 'std::transform' pouzite "range-based for" cyklus, v ktorom budete volat 'incrementPointsIfItHelps'.
*/

void helpAfterExam2(list<int> & points) noexcept {
    for (auto it : points){
        std::replace(points.begin(), points.end(), it, incrementPointsIfItHelps(it));
    }
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati novy zoznam, v ktorom hodnota kazdeho prvku je dana suctom prvkov v 'data1' a 'data2'
    s rovnakou poziciou.

    V implementacii pouzite 'std::transform'.
    Pri jej volani pouzite ako jeden z argumentov 'std::plus<int>()'.

    PARAMETRE:
        [in] data1 - obsahuje scitance
        [in] data2 - obsahuje scitance

    NAVRATOVA HODNOTA:
        Zoznam, v ktorom hodnota kazdeho prvku je suctom prvkov v 'data1' a 'data2' s rovnakou poziciou.

    VSTUPNA PODMIENKA:
        'data1' a 'data2' maju rovnaky pocet prvkov

    VYSTUPNA PODMENKA:
        Nech 'output' je vystupny zoznam.
        Pocet prvkov 'output' je rovnaky ako pocet prvkov 'data1' a 'data2'.
        Pre kazde i take, ze i >= 0 && i < data1.size() plati: output[i] = data1[i] + data2[i].

    PRIKLAD:
        vstup: data1 = { 2, 1, 1, 4, 5 }
               data2 = { 1, 0, 4, 6, 2 }
        vystup:        { 3, 1, 5,10, 7 }
*/

list<int> add(const list<int> & data1, const list<int> & data2) noexcept {
    list<int> sum (data1.size());
    transform(data1.begin(), data1.end(), data2.begin(), sum.begin(), plus<int>());
    return sum; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky vektora od najvacsieho po najmensi.

    V implementacii pouzite 'std::sort' alebo 'std::stable_sort' s parametrom 'std::greater<int>()'.

    PARAMETER:
        [in, out] data - vektor, ktory funkcia usporiada
*/

void sort1(vector<int> & data) noexcept {
    sort(data.begin(),data.end(), greater<int>());
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky vektora od najvacsieho po najmensi.

    V implementacii pouzite 'std::sort' alebo 'std::stable_sort' s reverznymi iteratormi.

    PARAMETER:
        [in, out] data - vektor, ktory funkcia usporiada
*/

void sort2(vector<int> & data) noexcept {
    sort(data.rbegin(), data.rend(),less<int>());
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {
    initializer_list <int> data;
    //Uloha1
    auto value2 = average(data);

    //Uloha2
    int x = 1; int y = 5;
    auto value = findValue(data, 30);

    //Uloha3
    auto value1 = findInRange200to400(data);

    //Uloha4
    //replace200to400by5(data);

    //Uloha5
   // incrementAll(data);

    //Uloha6
    //helpAfterExam1(data);

    //Uloha7
    //helpAfterExam2(data);

    //Uloha8
    list <int>data1 = { 2, 1, 1, 4, 5 };
    vector <int>data2 = { 1, 0, 4, 6, 2 };
    //vystup:        { 3, 1, 5,10, 7 }
    //auto exit = add(data1, data2);

    //Uloha9
   // sort1(data2);

    //Uloha10
    sort2(data2);
    return 0;
}
