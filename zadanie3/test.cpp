struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};


void insertionSort(List * list) {
    List NewList = {};
    NewList.first = list->first;

    Node *head = list->first;
    Node * NLhead = list->first;

    if ((head == nullptr) || (head->next == nullptr)){
        return;
    }

    Node *current = head;

    while (current != nullptr){
        if(current->data){
            current = current->next;
            previous = previous->next;
        } else {
            while (tmp->data > current->data){
                tmpprev = tmp;
                tmp = tmp->next;
            }
            previous->next = current->next;
            current->next = tmp;
            tmpprev->next = current;
        }
        list->first = tmpprev;
        tmp = tmpprev;
        current = previous->next;
    }
}