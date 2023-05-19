/*
Meno a priezvisko:Erik Poczos

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
(8)  V prvych osmich prikladoch mozete pouzit iterativnu alebo rekurzivnu implementaciu. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
     V pripade implementacie rekurziou, moze byt hlavna cast implemetovana v pridanej rekurzivnej funkcii. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <exception>
#include <set>
#include <stack>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol binarneho vyhladavacieho stromu
struct Node {
    int value;     // hodnota uzla
    Node *smaller; // uzol 'smaller' a jeho nasledovnici maju hodnotu mensiu ako 'value'
    Node *greater; // uzol 'greater' a jeho nasledovnici maju hodnotu vacsiu ako 'value

    explicit Node(int value = 0, Node *smaller = nullptr, Node *greater = nullptr)
    : value(value)
    , smaller(smaller)
    , greater(greater)
    {
    }
};

// Binarny vyhladavaci strom
struct BinarySearchTree {
    Node *root; // koren stromu

    explicit BinarySearchTree(Node *root = nullptr)
    : root(root)
    {
    }
};

// Vynimka oznacujuca, ze uzol so zadanou hodnotou v strome neexistuje
class ValueNotExistsException : public std::exception {
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najmensiu hodnotu v strome.
    V pripade neexistencie tejto hodnoty vyhodi vynimku.

    Riesenie (tejto, aj dalsich uloh) musi vyuzivat vlastnosti binarneho vyhladavacieho stromu.
    Napriklad, pri hladani minima treba prejst len cez potrebne uzly. Netreba prehladavat vsetky uzly (okrem specialnych pripadov).

    VSTUPNY PARAMETER:
        [in] tree - strom, v ktorom funkcia hlada minimum

    NAVRATOVA HODNOTA:
        najmensia hodnota v strome

    VYNIMKA:
        ValueNotExistsException - ak je strom prazdny
*/

int min(const BinarySearchTree *tree) {
    Node *tmp = tree->root;
    if (tmp == nullptr)                     //ak je to prazdny strom
        throw (ValueNotExistsException){};

    while (tmp->smaller != nullptr){        //chod iba do lava az po koniec
        tmp = tmp->smaller;
    }
    return tmp->value;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati hlbku uzla s hodnotou 'value' v strome 'tree'.
    Hlbka korena je 0.
    Ak hladany uzol v strome nie je, tak funkcia vyhodi vynimku.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Hlbka uzla s hodnotou 'value'.

    VYNIMKA:
        ValueNotExistsException - ak sa uzol s hodnotou 'value' v strome nenachdza
*/

unsigned depth(const BinarySearchTree *tree, int value) {
    unsigned depth = 0;
    Node *tmp = tree->root;
    if (tmp == nullptr)
        throw ValueNotExistsException();

    while (tmp->value != value){
        if (tmp->value > value && tmp->smaller != nullptr){   //ide sa do lava ak je hodnota vacsia ako co hladame
            tmp = tmp->smaller;
        } else if (tmp->greater != nullptr)                   //ak je mensia tak ideme do prava
            tmp = tmp->greater;
        else
            throw ValueNotExistsException();                //ak neexistuje lavy/pravy potomok tak ani hodnota v strome
        depth++;
    }
    return depth;
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot uzlov, ktore musi prejst pri hladani uzla s hodnotou 'value'.
    Prva hodnota vystupneho zoznamu je hodnota korena, druha hodnota zoznamu je lavy alebo pravy nasledovnik korena, atd.
    Poslednou hodnotou vo vystupnom zozname je hodnota uzla, na ktorom sa hladanie zastavilo.
    Ak 'tree' obsahuje uzol s hodnotou 'value', tak poslednou hodnotou vystupeho zoznamu je 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol s hodnotou 'value'
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Zoznam hodnot uzlov, ktorych hodnoty musela funkcia pri hladani porovnavat.
        Poradie hodnot vo vystupnom zozname musi zodpovedat poradiu prechadzania uzlov stromu.

    PRIKLADY:
        V prikladoch predpokladajme strom:
                  40
                 /  \
               20    50
              /  \    \
            10   30    60

        1. priklad
            value: 30 -> vystup: (40, 20, 30)
        2. priklad
            value: 20 -> vystup: (40, 20)
        3. priklad
            value: 45 -> vystup: (40, 50)
*/

list<int> path(const BinarySearchTree *tree, int value) noexcept {
    list<int> nodes;
    Node *tmp = tree->root;

    while (tmp != nullptr){
        if (tmp->value > value){            //ideme do lavy
            nodes.push_back(tmp->value); //pridaj uzol
            tmp = tmp->smaller;
        } else if (tmp->value < value) {    //ideme do prava
            nodes.push_back(tmp->value);
            tmp = tmp->greater;
        }
        else {
            nodes.push_back(tmp->value); //ak nevieme kam ist tak sme skoncili
            tmp = nullptr;
        }
    }

    return nodes; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu.

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho pocet uzlov funkcia zistuje

    NAVRATOVA HODNOTA:
        pocet uzlov stromu
*/

size_t countNode (Node *node){  //rekurzivna funkcia
    if (node == nullptr)
        return 0;

    return 1 + countNode(node->smaller) + countNode(node->greater); //preorder prechadzanie stromu
    //zakladna idea z cvik
}


size_t count(const BinarySearchTree *tree) noexcept {
    return countNode(tree->root);  //zavolanie rekurzie
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot vsetkych uzlov v strome 'tree'.
    Zoznam musi byt usporiadany od najmensieho prvku po najvacsi.

    Usporiadanie dosiahnite vhodnou postupnostou prechadzania uzlov stromu!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho hodnoty funkcia vrati

    NAVRATOVA HODNOTA:
        hodnoty uzlov, v poradi od najmensej po najvacsiu
*/

list<int> inOrder(const Node *node, list<int> nodes) {  //inorder rekurzia zo cvik
    if (node) {
        nodes = inOrder(node->smaller, nodes);
        nodes.push_back(node->value);
        nodes = inOrder(node->greater, nodes);
    }
    return nodes;
}

list<int> all(const BinarySearchTree *tree) noexcept {
    list<int> nodes;
    return inOrder(tree->root, nodes); //zavolanie rekurzie
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu 'tree', ktorych hodnota je vacsia ako 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia pocita pocet uzlov splnajich podmienku
        [in] value - hodnota, podla ktorej sa vyberaju uzly

    NAVRATOVA HODNOTA:
        pocet uzlov s hodnotou vacsou ako 'value'
*/

size_t counter(Node *root, int value){
    if (root == nullptr)
        return 0;

    if(root->value > value)     //scitaj jeden lavy a zvysnych pravych
        return counter(root->smaller,value) + 1 + countNode(root->greater);
    else    //scitaj vsetkych pravych potomkov
        return counter(root->greater,value);
}

size_t countGreater(const BinarySearchTree *tree, int value) noexcept {
    return counter(tree->root, value);
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani vsetky uzly stromu a dealokuje ich.

    Na dealokaciu pouzite operator 'delete'!

    VSTUPNY PARAMETER:
        [in, out] tree - strom, ktoreho uzly funkcia odstrani

    VYSTUPNE PODMIENKY:
        vsetky uzly su dealokovane
        'tree->root' je nulovy smernik
*/

void deleteTree(Node* node){    //rekurzia postorder
    if (node == nullptr)
        return;

    deleteTree(node->smaller);
    deleteTree(node->greater);

    delete node;
}

void clear(BinarySearchTree *tree) noexcept {
    deleteTree(tree->root);
    tree->root = nullptr;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia hlada hodnotu 'value' vo vektore 'data'.
    Vrati pocet prvkov v 'data', ktore pri hladni porovnala s 'value'.
    Vektor 'data' obsahuje usporiadane hodnoty.
    Casova narocnost algoritmu je O(log(n)), kde n je pocet prvkov vektora.

    PARAMETRE:
        [in] data - hodnoty usporiadane od najmensieho prvku po najvacsi
        [in] value - hodnota hladana v 'data'

    NAVRATOVA HODNOTA:
        Pocet prvkov 'data', ktore funkcia pri hladani porovnala s 'value'.
        (bez ohladu na to, ci 'data' obsahuje hodnotu 'value').

    VSTUPNA PODMIENKA:
        Hodnoty v 'data' su usporiadane od najmensieho prvku po najvacsi.

    PRIKLADY:
        data = (100, 102, 104, 106, 108, 110, 112), value = 106 -> vystup: 1
        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
        data = (100), value = 100 -> vystup: 1
        data = (100), value = 200 -> vystup: 1
        data = (), value = 100 -> vystup: 0
*/

unsigned contains(const vector<int> & data, int value) noexcept {
    unsigned amount = 0;
    int high = data.size()-1;
    int low = 0;

    while (low<=high){
        int mid = low + ((high - low) / 2); //mid vypocet
            if (value == data[mid]) {   //ak sa zhoduju koniec
                amount++;
                return amount;
            }
            //posunutie hranic
            if (value < data[mid])
                high = mid-1;
            else
                low = mid+1;
            amount++;

    }
    return amount;
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati histogram slov v 'data' (zisti, kolko krat sa ktore slovo nachadza v 'data').

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        histogram slov (pre kazde slovo z 'data' obsahuje pocet jeho vyskytov)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Histogram obsahuje iba slova, ktore sa v 'data' nachadzaju

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno" -> 1}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> 1, "" -> 1}

        vstup: data = ()
        vystup: {}
*/

map<string, size_t> histogram(const vector<string> & data) noexcept {
    map<string, size_t> histo;

    for (auto const& it : data){    //ranged based loop
        if (histo.find(it) == histo.end())   //ak neexistuje v mape
            histo.insert(pair<string, int>(it, 1));     //tak ho pridaj
        else {
            histo.find(it)->second++;   //ak existuje, tak zvacsi pocet vyskytov
        }
    }
    return histo;
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati index slov v 'data' (pre kazde slovo mnozinu indexov jeho vyskytu).

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        index slov (pre kazde slovo z 'data' obsahuje indexy, na ktorych sa slovo v 'data' nachadza)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Index obsahuje zoznamy vyskytov len pre slova, ktore sa nachadzaju v 'data'

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" -> {2, 6}, "okno" -> {5}}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> {0}, "" -> {1}}

        vstup: data = ()
        vystup: {}
*/

map<string, set<size_t>> index(const vector<string> & data) noexcept {
    map<string, set<size_t>> indexes;
    set<size_t> index;
    size_t counter = 0;

    for (auto& it : data){  //ranged based
        if (indexes.find(it) == indexes.end()) {                        //ak neexistuje v mape
            indexes.insert(pair<string, set<size_t>>(it, index)); //pridaj par
            indexes.find(it)->second.insert(counter);                //vloz index do setu
        }
        else {
            indexes.find(it)->second.insert(counter);               //ak existuje pridaj index do setu
        }
        counter++;                                                       //zvacsi index
    }
    return indexes;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

//kod zo cvik na testovanie

// rekurzivna pomocna funkcia na pridanie uzla do stromu
Node *addNode(Node *root, const int value) {
    if (!root) return new Node{value, nullptr, nullptr};
    if (value < root->value) {
        root->smaller = addNode(root->smaller, value);
    } else {
        root->greater = addNode(root->greater, value);
    }
    return root;
}

// nerekurzivna hlavna funkcia na pridanie uzla do stromu
void addNode(BinarySearchTree *bst, const int val) {
    bst->root = addNode(bst->root, val);
}

// funkcia na vytvorenie binarneho stromu z hodnot inicializacneho zoznamu
BinarySearchTree *createBST(const initializer_list<int> &i) {
    BinarySearchTree *bst{new BinarySearchTree{nullptr}};
    for (int e: i) {
        addNode(bst, e);
    }
    return bst;
}

int main() {

     BinarySearchTree *bst{createBST({20, 10, 70, 0, 15, 50, 80, 18, 55})};

    //Uloha1    works
    //auto value = min(bst);

    //Uloha2    works
    //auto value = depth(bst, 13);

    //Uloha3    works
    //auto value = path (bst, 50);

    //Uloha4    works
    //auto value = count(bst);

    //Uloha5    works
    //auto value = all(bst);

    //Uloha6    works
    auto value = countGreater(bst, 50);

    //Uloha7    works
    //clear(bst);

    //Uloha8    works

    //vector<int> data = {100, 102, 104, 106, 108, 110, 112 }; //, value = 106 -> vystup: 1
    //        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
    //        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
    //        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
    //        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
    //        data = (100), value = 100 -> vystup: 1
    //        data = (100), value = 200 -> vystup: 1
    //        data = (), value = 100 -> vystup: 0

    //auto value = contains(data, 104);

    //Uloha9    works
    //vector<string> datastring = {};

    //        vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno" -> 1}
    //
    //        vstup: data = ("pocitac", "")
    //        vystup: {"pocitac" -> 1, "" -> 1}
    //
    //        vstup: data = ()
    //        vystup: {}
    //

    //auto value = histogram(datastring);

    //Uloha10   works
    //        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
    //        vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" -> {2, 6}, "okno" -> {5}}
    //
    //        vstup: data = ("pocitac", "")
    //        vystup: {"pocitac" -> {0}, "" -> {1}}
    //
    //        vstup: data = ()
    //        vystup: {}

    //auto value = index(datastring);

    return 0;
}
