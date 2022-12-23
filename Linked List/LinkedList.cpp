#include <iostream>

#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& copyList) {
    Node<T>* newHead = this->head = new Node<T>();
    
    /* I could simply do this->insertlast() but it would be less efficient */
    for(auto tmp = copyList.head; tmp != NULL; tmp = tmp->next) {
        newHead->next = new Node<T>(tmp->data);
        newHead = newHead->next;
    }

    Node<T>* tmp = this->head;
    this->head = this->head->next;
    delete tmp;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    this->clear();
}

template <typename T>
void LinkedList<T>::insertLast(T value) {
    Node<T>* newNode = new Node<T>(value);
    if(this->head == NULL)
        this->head = newNode;
    else {
        Node<T>* current = head;
        for(; current->next != NULL; current = current->next);
        current->next = newNode; 
    }
}

template <typename T>
void LinkedList<T>::initRandom(int size) {
    for(int i = 0; i < size; i++) {
        int random = rand() % 10;
        insertLast(random);
    }
}

template <typename T>
void LinkedList<T>::insertFirst(T value) {
    Node<T>* newHead = new Node<T>(value);
    newHead->next = this->head;
    this->head = newHead;
}

template <typename T>
void LinkedList<T>::insertOrder(T value) {
    if((this->head == NULL) || (value < this->head->data)){
        insertFirst(value);
    }
    else {
        Node<T>* temp = head;
        Node<T>* node = new Node<T>(value);
        for(;(temp->next != NULL) && (value > temp->next->data); temp = temp->next);
        node->next = temp->next;
        temp->next = node;
    }
}

template <typename T>
int LinkedList<T>::length() const {
    int i = 0;
    for (auto current = this->head; current != NULL; current = current->next, i++);
    return i;
}

template <typename T>
void LinkedList<T>::deleteFirst() {
    if(this->head == NULL)
        return;
    Node<T>* temp = this->head;
    this->head = this->head->next;
    delete temp;
}

template <typename T>
void LinkedList<T>::deleteLast() {
    if(this->head == NULL)
        return;
    if(this->head->next == NULL) {
        delete head;
        return;
    }
    
    Node<T>* current = this->head;
    for (; (current->next->next != NULL); current = current->next);
    Node<T>* temp = current->next;
    current->next = current->next->next;
    delete temp;
}

template <typename T>
void LinkedList<T>::deleteElement(T value) {
    if(this->head == NULL)
        return;
    
    Node<T>* current = this->head;

    if (current->data == value)
        deleteFirst();
    
    for (; (current->next != NULL) && (value != current->next->data); current = current->next);
    
    if(current->next == NULL)
        return; 
    
    Node<T>* temp = current->next;
    current->next = current->next->next;
    delete temp;
}

template <typename T>
Node<T>* LinkedList<T>::get(int position) const{
    if(position < 0)
        throw std::out_of_range("Out Of Range!");

    Node<T>* current = this->head;
    int i = 0;
    while(i < position && current != NULL) {
        current = current->next;
        ++i;
    }
    if(current == NULL) throw std::out_of_range("Out Of Range!");
    return current;
}

template <typename T>
void LinkedList<T>::reverse() {
    if(this->head == NULL)
        return;

    Node<T> * previous = NULL, * current = this->head, * next = NULL;

    while(current != NULL){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    this->head = previous;    
}

template <typename T>
void LinkedList<T>::clear() {
    while (this->head != NULL)
        deleteFirst();
}

template <typename T>
void LinkedList<T>::print() const {
    std::cout << *this; 
}
 
template<typename T>
LinkedList<T>& LinkedList<T>::operator= (const LinkedList<T>& copyList) {
    LinkedList<T> temp(copyList);
    std::swap(temp.head, this->head);
    return *this;
    /* Since I swapped the heads, now temp destructor will be called, but temp now is the 
        original list */
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const LinkedList<T>& list) {
    for(auto current = list.head; current != NULL; current = current->next)
        out << current->data << " -> ";
    out << "NULL" << std::endl;
    return out;
}