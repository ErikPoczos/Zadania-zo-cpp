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
#include <cstring>

using namespace std;
//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()
*/


void insertionSort(int *data, const size_t length) {
    //cast je z cvik
    if (length <= 1){   //ak je to prazdny/jeden prvkovy zoznam, nerob s nim nic
        return;
    }
    int i, j, key;
    for (i = 1; i < length;i++){
        key = data[i];
        j = i-1;

        while (j >= 0 && data[j] < key){
            data[j+1] = data[j];
            j = j-1;
        }
        data[j+1] = key;
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        ("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", nullptr)
        ("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", "Anabela", nullptr)
        ("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej", nullptr)
        ("Andrej", nullptr) -> ("Andrej", nullptr)
        (nullptr) -> (nullptr)

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/

void insertionSort(const char *data[]) {
    //cast z cvik, trosku prerobene
    int length=0;
    int i = 0;
    while (data[i] != nullptr){                 //prazdny zoznam
        length++;
        i++;
    }

    if (length <= 1){   //ak je to prazdny/jeden prvkovy zoznam, nerob s nim nic
        return;
    }
    const char *key;
    const char *ptr;
    int j;

    for (i = 1; i < length;i++){
        key = data[i];
        j = i-1;

        while ((j >= 0) && (strcmp(data[j], key)) < 0){
            ptr = data[j+1];
            data[j+1] = data[j];
            data[j] = ptr;
            j = j-1;
        }
        data[j+1] = key;
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/

void insertionSort(List * list){
    Node *head = list->first;

    if (head == nullptr){
        return;
    }

    Node* sortedHead = head;
    Node* sortedLast;
    Node* sortedCurrent;
    head = head->next;
    sortedHead->next = nullptr;

    while (head != nullptr) {   //prehladaj po koniec linked list
        Node* pNode = head;     //predchadzajuci node
        if (sortedHead->data <= head->data) {
            head = head->next;
            pNode->next = sortedHead;
            sortedHead = pNode;
        } else {
            sortedLast = sortedHead;
            sortedCurrent = sortedHead;
            while (sortedCurrent != nullptr && sortedCurrent->data > pNode->data) {   //ak najdes vacsi node
                sortedLast = sortedCurrent;
                sortedCurrent = sortedCurrent->next;
            }

            head = head->next;              //daj ho dopredu
            pNode->next = sortedCurrent;
            sortedLast->next = pNode;
        }
    }

    list->first = sortedHead;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1], zvysne prvky v 'output' funkcia nemeni.
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10)
        output pred vykonanim funkcie: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
        output po vykonani funkcie:    (20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low, const size_t middle, const size_t high){
    //toto bolo na cvikach v pdfku, male zmeny su urobene

    int lowptr = low;
    int middleptr = middle;
    int out = low;

    while(lowptr < middle && middleptr < high) {
        if(input[lowptr] >= input[middleptr]){
            output[out] = input[lowptr];
            out++;
            lowptr++;
        }else {
            output[out] = input[middleptr];
            out++;
            middleptr++;
        }
    }
    while(lowptr < middle) {
        output[out] = input[lowptr];
        out++;
        lowptr++;
    }
    while(middleptr < high) {
        output[out] = input[middleptr];
        out++;
        middleptr++;
    }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/
// void mergeSort(int *arrayA, int *arrayB, const size_t low, const size_t high) { // Priklad deklaracie rekurzivnej funkcie, v pripade pristupu top-down
// }

void swapPtr(int **first, int **second) //funkcia na prehodenie pointerov
{
    int *tmp = (*first);
    (*first) = (*second);
    (*second) = tmp;
}

void mergeSort(int *data, const size_t length) {

    if (length <=1){    //ak je to jeden prvkovy prvok alebo menej tak netreba triedit
        return;
    }

    int *tmpdata = new int[length]; //pomocne pole

    int *input = data;
    int *output = tmpdata;
    bool swap = false;

    size_t low,mid,high;

    int counter = 0;

    for (size_t power = 1; power < length; power *= 2){     //
        for (size_t i = 0; i < length; i += 2*power){
            low = i;                //vypocet low
            high = i + 2*power;     //vypocet high
            mid = (low+high)/2;     //midddle je presne medzi low a high

            if (mid > length){      //ak je neparny pocet prvok, mid a high sa mozu posunut mimo arrayu
                mid = length;       //v tom pripade sa nastavia na max (lenght)
            }
            if (high > length){
                high = length;
            }

            mergeNeighbours(output,input, low, mid, high);
        }
        swapPtr(&input, &output);   //zmena pointerov
        swap = !swap;       //sledovanie v ktorom arrayi je sorted list
    }

    if (swap) { //ak treba prekopirovat (ak je pocet prvokov v arrayi parny tak treba)
        std::memcpy(output, input, length * sizeof(int));
        // std::copy
    }

    delete[] tmpdata;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

// Pomocna struktura pre ulohu 2
struct ListData {
    int *data; // pole hodnot uzlov
    size_t len; // dlzka pola 'data'
};

void appendNode(List *list, const int val) {
    Node* tmp = list->first;    //node na prehladavanie cyklu

    Node* new_node = new Node;  //novy posledny node
    new_node->data = val;
    new_node->next = nullptr;

    if (list->first == nullptr){ //ak je to prazdny list
        list->first = new_node;  //pridaj node
        return;
    }
    while (tmp->next != nullptr) {  //prejdi listom kym nenajdes koniec
        tmp = tmp->next;
    }
    tmp->next = new_node;       //ak mas koniec tak pridaj node
}

List *createList(const ListData *listData) {
    List *list = new List;      //vytvor zoznam
    list->first = nullptr;
    if (listData->len == 0) {       //ak nemame udaje tak bude prazdny
        return list;

    } else {
        for (size_t i = 0; i < listData->len; i++) {    //vytvoria sa uzly a pridaju sa hodnoty
            appendNode(list, listData->data[i]);
        }
    }
    return list;
}



int main() {
    //Uloha1
    //(1, 3, 2) -> (3, 2, 1)
    //(1, 2, 2, 1) -> (2, 2, 1, 1)
    int data[] = {1, 3, 2};
    insertionSort(data, 3);

    //uloha2
    const char *mena[] = {"Juraj", "Anabela", "Peter", "Andrej", nullptr};
    insertionSort(mena);

 //Uloha3
    int NormalArray[] = {5,1,8,6,5};
    ListData NormalArrayData = {NormalArray, 5};
    //uloha 1 a 2
    List *NormalList = createList(&NormalArrayData);

//    insertionSort(NormalList);
//uloha4
    int in[]  = { 10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10};
    int out[] = { 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
//    mergeNeighbours(out, in, 4, 8, 12);

//uloha5
    int dataasdas[]  = { 3,1,2};
 //   mergeSort(dataasdas, 3);
    for (int dataasda : dataasdas){
        std::cout << dataasda << endl;
    }
    return 0;
}
