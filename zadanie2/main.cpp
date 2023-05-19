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
#include <bits/stdc++.h>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Reprezentacia uzla zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node *next; // adresa nasledujuceho uzla zoznamu
};

// Reprezentacia zretazeneho zoznamu
struct List {
    Node *first; // adresa prveho uzla zoznamu
};

// Pomocna struktura pre ulohu 2
struct ListData {
    int *data; // pole hodnot uzlov
    size_t len; // dlzka pola 'data'
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na koniec zretazeneho zoznamu 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr') a moze
           mat lubovolny pocet uzlov (0 a viac).

    PARAMETRE:
        [in, out] list - adresa zretazeneho zoznamu, do ktoreho ideme pridavat uzol
        [in] val       - hodnota uzla, ktory sa ma pridat na koniec zoznamu 'list'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        prazdny zoznam, 5 ---> (5)
        (1), 1 ---> (1,1)
        (8,2,6,6), 14 ---> (8,2,6,6,14)
        (6,100,33), -85 ---> (6,100,33,-85)
        (1,2,3,4,5), 3 ---> (1,2,3,4,5,3)
*/

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

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam, ktory bude skonstruovany pomocou udajov vo vstupnej
    strukture 'listData'. Struktura 'listData' obsahuje polozku 'data', ktora reprezentuje pole
    hodnot pre jednotlive uzly zoznamu. Struktura 'listData' taktiez obsahuje polozku 'len', ktora
    hovori aku ma dlzku pole 'data'. Vytvoreny zoznam musi obsahovat uzly, ktore zodpovedaju
    svojimi hodnotami a poradim prvkom ulozenym v poli 'data' (dlzka zoznamu bude 'len').
    Funkcia nakoniec vrati adresu takto vytvoreneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'listData' vzdy existuje (t.j. 'listData' je rozny od 'nullptr').
        2) Pre polozku 'len' plati, ze 'len' >= 0 a nikdy nebude mat vacsiu hodnotu ako je
           realny pocet prvkov v poli 'data'.
    VYSTUPNA PODMIENKA:
        1) Ak je polozka 'len' rovna 0, vtedy sa vytvori a vrati prazdny zretazeny zoznam
           (t.j. platny zoznam, ktory ma 0 uzlov).

    PARAMETRE:
        [in] listData - struktura, pomocou ktorej sa vytvori zoznam

    NAVRATOVA HODNOTA:
        Adresa zretazeneho zoznamu, ktory bol vytvoreny pomocou struktury 'listData'.
        Vid pokyny vyssie.

    PRIKLADY:
        polozka 'data' = (1,2,3)
        polozka 'len' = 0
        vystupny zoznam bude mat 0 uzlov, t.j. ()

        polozka 'data' = (1,2,3)
        polozka 'len' = 2
        vystupny zoznam bude (1,2)

        polozka 'data' = (1,2,3)
        polozka 'len' = 3
        vystupny zoznam bude (1,2,3)

        polozka 'data' = (-9,412,64,72,100,100,6)
        polozka 'len' = 4
        vystupny zoznam bude (-9,412,64,72)
*/

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

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' do vzostupne zotriedeneho zoznamu 'sortedList'.
    Pridanie musi prebehnut takym sposobom, aby bol zoznam 'sortedList' po pridani noveho uzla
    stale vzostupne zotriedeny.

    POZNAMKA: Na poradi duplikatov v zozname 'sortedList' nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'sortedList' vzdy existuje (t.j. 'sortedList' je rozny od 'nullptr').
        2) Vstupny zoznam 'sortedList' moze mat lubovolny pocet uzlov (0 a viac).
        3) Vstupny zoznam 'sortedList' je vzostupne zotriedeny.

    PARAMETRE:
        [in, out] sortedList   - adresa vstupneho zretazeneho zoznamu, ktory je zotriedeny
                                 vzostupne (z angl. ascending)
        [in] val               - hodnota uzla, ktory sa ma pridat do zoznamu 'sortedList'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        (), 0 ---> (0}
        (), 156 ---> (156)
        (8), 4 ---> (4,8)
        (7), 10 ---> (7,10)
        (55), 55 ---> (55,55) ... poznamka: na poradi duplikatov nezalezi
        (1,8,236,888), 70 ---> (1,8,70,236,888)
        (5,5,14,82,82,100), 5 ---> (5,5,5,14,82,82,100)
*/

void insertNode(List *sortedList, const int val) {
    if (sortedList->first == nullptr){  //ak je to prazdny zoznam
        appendNode(sortedList, val);//pridaj node
        return;
    }

    if (sortedList->first->data >= val){ //ak je to prvy uzol
        Node *insert = new Node;
        insert->data = val;
        insert->next = sortedList->first;     //nalinkuj novovytvoreny na stary prvy (teraz druhy)
        sortedList->first = insert;           //nastav novy ako prvy
        return;
    }

    Node* tmp = sortedList->first;            //pomocny node pre cyklus
    Node* prev = tmp;                         //node na ukladanie predchadzajuceho node
    while (tmp != nullptr){
        if (tmp->data <= val){                //je hodnota uzla mensia?
            prev = tmp;                       //uloz predchadzajuci node
            tmp = tmp->next;
        } else {                        //ak nie je
            Node *insert = new Node;    //tak vytvor uzol
            insert->data = val;         //daj tam udaje
            insert->next = tmp;   //novy ukaze na ten vacsi uzol
            prev->next = insert;  //predchadzajuci ukaze na novy
            return;
        }
    }
    appendNode(sortedList, val);    //pridaj node v pripade ked kazdy uzol je mensi
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zoznam spojenim zoznamov 'list1' a 'list2'. Funkcia vrati adresu
    novo vytvoreneho zoznamu. V spojenom zozname idu najprv uzly zoznamu 'list1' (v nezmenenom poradi)
    a potom nasleduju uzly zoznamu 'list2' (v nezmenenom poradi). Pri vytvarani noveho zoznamu mozete
    pouzit hlboku alebo plytku kopiu existujucich uzlov (obe riesenia budu akceptovane).

    POZNAMKA:
        Prazdny zoznam je taky zoznam, ktory je platny, ale obsahuje 0 uzlov
        (t.j. polozka 'first' je nastavena na 'nullptr').

    VSTUPNE PODMIENKY:
        1) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).

    PARAMETRE:
        [in, out] list1 - adresa prveho zoznamu
        [in, out] list2 - adresa druheho zoznamu

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol spojenim zoznamov 'list1' a 'list2'.

    PRIKLADY:
        () + () ---> ()
        (5,9) + () ---> (5,9)
        () + (2,2,2) ---> (2,2,2)
        (1) + (2) ---> (1,2)
        (7) + (3,9,16) ---> (7,3,9,16)
        (50,-47,23,1) + (0,0,9,-8) ---> (50,-47,23,1,0,0,9,-8)
*/

List *joinLists(List *list1, List *list2) {
    Node* tmp = list1->first;
    if (tmp == nullptr){    //ak je prazdny list
        return list2;
    }
    while (tmp->next != nullptr){   //prejdi na koniec listu
        tmp = tmp->next;
    }
    tmp->next = list2->first;       //posledny node prepoj s prvym z list 2

    return list1;
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani posledny uzol zo zoznamu 'list'. Ak je zoznam 'list' prazdny, funkcia nic
    nevykona. Pamat uzla, ktory funkcia vymaze musi byt korektne dealokovana.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in, out] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        () ---> ()
        (1) ---> ()
        (1,2) ---> (1)
        (1,2,3) ---> (1,2)
*/

void removeLastNode(List *list) {
    Node *tmp = list->first;    //prvy uzol
    if (tmp == nullptr){        //ak je prazdny nerob nic
        return;
    }
    if (tmp->next == nullptr){  //ak je tam jeden
        delete list->first;             //tak ho vymaz
        list->first = nullptr;
        return;
    }
    Node *BeforeLast = tmp;     //pomocny node na najdenie predposledneho node-u
    while (BeforeLast->next->next != nullptr){      //najdi predposledny node
        BeforeLast = BeforeLast->next;
    }
    delete BeforeLast->next;        //vymaz posledny
    BeforeLast->next = nullptr;     //a nastav predposledny (teraz posledny) na nullptr
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci je vstupny zoznam 'list' palindrom. Prazdny zoznam budeme povazovat za
    palindrom.

    Poznamka: Palindrom predstavuje taku postupnost hodnot, ktora sa cita rovnako v oboch smeroch.
    URL: https://sk.wikipedia.org/wiki/Palindr%C3%B3m
    Priklad palindromu: 1212121 alebo 4953594

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci vstupny zoznam je/nie je palindrom.

    PRIKLADY:
        () ---> true
        (1) ---> true
        (2,2,2,2) ---> true
        (1,2,3,4,5) ---> false
        (1,2,2,1) ---> true
        (8,4,8,4,8) ---> true
        (9,842,613,2,613,842,9) ---> true
        (7,9,1,2) ---> false
        (0,0,0,7,0,0) ---> false
*/

bool isPalindrome(const List *list) {
    Node* tmp = list->first;
    stack <int> stack1;              //vytvor stack

    while(tmp != nullptr){          //daj vsetko na stack
        stack1.push(tmp->data);
        tmp = tmp->next;
    }

    tmp = list->first;              //reset tmp na zaciatok listu
    while(tmp != nullptr){
        int i = stack1.top();       //zober prvy prvok v stacku (co je posledny prvok v list)
        stack1.pop();               //vymaz ho

        if(tmp->data != i){         //je prvy prvok listu rovny prvemu zo stacku (prvy vo stacku je posledny v liste)
            return false;           //ak nie tak vyskoc
        }
        tmp = tmp->next;
    }
    return true;                    //ak vsetky sa rovnaju tak je to palindrom
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati sucet hodnot prvych 'n' uzlov v zozname 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).
        3) Parameter 'n' nebude zaporny a nebude mat nikdy vyssiu hodnotu ako je realny pocet
           uzlov v zozname.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] n - pocet uzlov od zaciatku zoznamu 'list', ktorych sucet sa vrati

    NAVRATOVA HODNOTA:
        Sucet hodnot prvych 'n' uzlov zoznamu 'list'. Ak 'n'=0, vtedy funkcia vrati hodnotu 0.

    PRIKLADY:
        (), 0 ---> 0
        (1,2,3), 0 ---> 0
        (6), 1 ---> 6
        (5,6,7), 2 ---> 11
        (4,4,4,4,4,4), 6 ---> 24
        (-8,41,-314,21), 3 ---> -281
*/

int sumNodes(const List *list, const size_t n) {
    Node *tmp = list->first;
    if (n==0){      //ak je to prazdny zoznam vrat 0
        return 0;
    }
    int sum = 0;
    for (size_t i = 0; i < n; i++){     //spocitaj hodnotu uzlov po n
        sum = sum + tmp->data;
        tmp = tmp->next;
    }
    return sum;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci zoznam 'list1' obsahuje vsetky hodnoty uzlov zoznamu 'list2'.
    Na poradi nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list1' a 'list2' vzdy existuju (t.j. su rozne od 'nullptr').
        2) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).
        3) Zoznam 'list2' nebude obsahovat duplicitne uzly.

    PARAMETRE:
        [in] list1 - prvy zoznam
        [in] list2 - druhy zoznam

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci zoznam 'list1' obsahuje/neobsahuje
        vsetky hodnoty uzlov zoznamu 'list2'.

    PRIKLADY:
        (), () ---> true
        (), (1,2,3) ---> false
        (1,2,3), () ---> true
        (5,6,7), (5,6,8) ---> false
        (8,4,3), (3,8,4) ---> true
        (7,6,1,9,8), (1,6,8) ---> true
        (3,3,3,3,3), (2,3) ---> false
        (8,6,1,2,5,0,7,7), (7) ---> true
        (9,5,10), (41,10,5) ---> false
*/

bool contains(const List *list1, const List *list2) {
    Node *tmp1 = list1->first;
    Node *tmp2 = list2->first;

    if ((tmp1 == nullptr) && (tmp2 == nullptr)) {       //2 prazdne listy
        return true;
    }
    if ((tmp1 == nullptr) && (tmp2 != nullptr)){        //prvy prazdny druhy neprazdny
        return false;
    }

    if (tmp2 == nullptr){                               //druhy prazdny
        return true;
    }

    while (tmp2 != nullptr){                //porovnavanie hodnoty prveho uzla z list2 so
        while (tmp1 != nullptr){            //vsetkymi z prveho listu
            if (tmp2->data == tmp1->data){  //ak je zhoda
                tmp2 = tmp2->next;          //testuj druhy uzol z list2
                break;
            } else{                         //inak vyskusaj dalsi uzol u list1
                tmp1 = tmp1->next;
            }
        }
        if (tmp1 == nullptr){   //ak si na konci list1 a nenasiel si uzol
            return false;       //tak nema tu hodnotu
        }
        tmp1 = list1->first;    //ak nastala zhoda resetni smernik na zaciatok zoznamu
    }
    return true;
    //ak to nebude fungovat tak ma asi streli :)
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati HLBOKU kopiu zoznamu 'list'. Vo vytvorenej kopii musia byt zachovane
    hodnoty a poradie uzlov z povodneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa zoznamu, ktoreho hlboku kopiu treba vytvorit

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol ako hlboka kopia vstupneho zoznamu 'list'. Kopiou
        prazdneho zoznamu je prazdny zoznam.

    PRIKLADY:
        Vstup = ()
        Vystup = ()

        Vstup = (1,2,3)
        Vystup = (1,2,3)
        Poznamka: adresy uzlov na rovnakych poziciach v oboch zoznamoch sa musia lisit
        (pretoze je to hlboka kopia)
*/

List *deepCopyList(const List *list) {
    Node *tmp = list->first;    //prvy uzol
    List *NewList = new List;   //vytvor prazdny list

    if (tmp == nullptr){        //ak neexistuje prvy uzol
        return NewList;
    }

    Node *tmpnew = new Node;    //vytvor prvy uzol pre novy list
    NewList->first = tmpnew;    //nastav ako prvy
    tmpnew->data = tmp->data;               //skopiruj udaje

    while (tmp->next != nullptr){   //ak OG list ma dalsi uzol
        tmp = tmp->next;            //prejdi nanho
        Node *newnode = new Node;   //vytvor novy uzol
        newnode->data = tmp->data;              //skopiruj udaje
        tmpnew->next = newnode;     //nalinkuj ho na novovytvoreny uzol
        tmpnew = tmpnew->next;      //posun sa na novy
    }

    tmpnew->next = nullptr;
    return NewList; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najde posledny vyskyt uzla s hodnotou 'val' v zozname 'list' a vrati jeho adresu.
    Ak sa v zozname 'list' takyto uzol nenachadza, funkcia vrati 'nullptr'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hladana hodnota uzla

    NAVRATOVA HODNOTA:
        Adresa posledneho vyskytu uzla s hodnotou 'val' v zozname 'list'.

    PRIKLADY (treba otestovat pomocou debuggera):
        (), 2 ---> nullptr
        (5,4,3,2), 1 ---> nullptr
        (-5,4,-9,66), 4 ---> adresa 2. uzla
        (1,1,1,5,6,41), 1 ---> adresa 3. uzla
        (8,6,7,3,2,6), 6 ---> adresa 6. uzla
*/

Node *findLastNodeOccurrence(const List *list, const int val) {
    Node *tmp = list->first;
    Node *LFadress = nullptr;       //adresa hladaneho nodu
    while (tmp != nullptr){         //prejdi celym zoznamom
        if (tmp->data == val){      //ak si nasiel zhodu
            LFadress = tmp;         //uloz adresu
            tmp = tmp->next;        //a hladaj dalej
        } else{
            tmp = tmp->next;
        }
    }

    return LFadress;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {
    int NormalArray[] = {5,4,5,6,9};
    ListData NormalArrayData = {NormalArray, 5};
    //uloha 1 a 2
    List *NormalList = createList(&NormalArrayData);

    //uloha 3

    int SortedArray[] = { 1,8,236};
    ListData SortedArrayData = {SortedArray, 4};
    List *SortedList = createList(&SortedArrayData);
    insertNode(SortedList, 70);

    //uloha 4
//    List *JoinedLists = joinLists(SortedList, NormalList);

    //uloha 5
//    removeLastNode(SortedList);

    //uloha 6
    int PalindromeArray[] = {2,4,4,2};
    ListData PalindromeList = {PalindromeArray,4 };
    List *PalindromeLinkedList = createList(&PalindromeList);
//    bool isitpali = isPalindrome(PalindromeLinkedList);

    //uloha 7
//    int sum = sumNodes(SortedList, 3);

    //uloha 8
//    (), () ---> true
//            (), (1,2,3) ---> false
//            (1,2,3), () ---> true
//            (5,6,7), (5,6,8) ---> false
//            (8,4,3), (3,8,4) ---> true
//            (7,6,1,9,8), (1,6,8) ---> true
//            (3,3,3,3,3), (2,3) ---> false
//            (8,6,1,2,5,0,7,7), (7) ---> true
//            (9,5,10), (41,10,5) ---> false
    int ListArray1[] = {9,5,10};
    ListData List1Data = {ListArray1, 3};
    List *List1 = createList(&List1Data);

    int ListArray2[] = {41,10,5};
    ListData List2Data = {ListArray2, 3};
    List *List2 = createList(&List2Data);

//    bool yesorno = contains(List1, List2);
//    std::cout << "Hodnota: " << yesorno;

    //uloha 9
 //   List *deepcopy = deepCopyList(SortedList);

    //uloha 10
 //   Node *last = findLastNodeOccurrence(NormalList, 5);
    return 0;
}
