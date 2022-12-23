#include <iostream>

#include "Queue.h"

template<class T>
Queue<T>::Queue(const Queue& copyQueue) {
    Node* newFirst = this->first = new Node();
    
    for(auto tmp = copyQueue.first; tmp != NULL; tmp = tmp->next) {
        newFirst->next = new Node(tmp->data);
        newFirst = newFirst->next;
    }

    Node* tmp = this->first;
    this->first = this->first->next;
    delete tmp;
}

template<class T>
Queue<T>::~Queue() {
    this->clear();
}

template<class T>
void Queue<T>::initRandom(int size) {
    for(int i = 0; i < size; i++) {
            int random = rand() % 10;
            add(random);
    }
}

template<class T>
T Queue<T>::remove() {
    if(isEmpty())
        throw std::invalid_argument("The queue is empty!");
    Node *temp = this->first;
    this->first = this->first->next;
    int data = temp->data;
    delete temp;
    return data;
}

template<class T>
void Queue<T>::add(T value) {
    Node *node = new Node(value);
    if(isEmpty())
        this->first = this->last = node;
    else {
        this->last->next = node;
        this->last = this->last->next;
    }
}

template<class T>
T Queue<T>::peek() const {
    if(!isEmpty())
        return this->first->data;
}

template<class T>
bool Queue<T>::isEmpty() const {
    return this->first == NULL; 
}

template<class T>
void Queue<T>::clear() {
    while (!isEmpty())
        remove();
}

template<class T>
void Queue<T>::print() const {
    std::cout << *this; 
}
 
template<typename T>
Queue<T>& Queue<T>::operator= (const Queue<T>& copyQueue) {
    Queue<T> temp(copyQueue);
    std::swap(temp.top, this->top);
    return *this;
    /* Since I swapped the heads, now temp destructor will be called, but temp now is the 
        original queue */
}

template<class T>
std::ostream& operator<< (std::ostream& out, const Queue<T>& queue) {
    for(auto current = queue.first; current != NULL; current = current->next)
        out << current->data << " -> ";
    out << "NULL" << std::endl;
    return out;
}