#include <iostream>

#include "Stack.h"

template <class T>
Stack<T>::Stack(const Stack& copyStack) {
    Node* newTop = this->top = new Node();
    
    for(auto tmp = copyStack.top; tmp != NULL; tmp = tmp->next) {
        newTop->next = new Node(tmp->data);
        newTop = newTop->next;
    }

    Node* tmp = this->top;
    this->top = this->top->next;
    delete tmp;
}

template <class T>
Stack<T>::~Stack() {
    this->clear();
}

template <class T>
void Stack<T>::initRandom(int size) {
    for(int i = 0; i < size; i++) {
            int random = rand() % 10;
            push(random);
    }
}

template <class T>
T Stack<T>::pop() {
    if(isEmpty())
        throw std::invalid_argument("The stack is empty!");
    Node *temp = this->top;
    this->top = this->top->next;
    int data = temp->data;
    delete temp;
    return data;
}

template <class T>
void Stack<T>::push(T value) {
    Node *newTop = new Node(value);
    newTop->next = this->top;
    top = newTop;
}

template <class T>
T Stack<T>::peek() const {
    if(!isEmpty())
        return top->data;
}

template <class T>
bool Stack<T>::isEmpty() const {
    return top == NULL; 
}

template <class T>
void Stack<T>::clear() {
    while (!isEmpty())
        pop();
}

template <class T>
void Stack<T>::print() const {
    std::cout << *this; 
}
 
template<typename T>
Stack<T>& Stack<T>::operator= (const Stack<T>& copyStack) {
    Stack<T> temp(copyStack);
    std::swap(temp.top, this->top);
    return *this;
    /* Since I swapped the heads, now temp destructor will be called, but temp now is the 
        original stack */
}

template <class T>
std::ostream& operator<< (std::ostream& out, const Stack<T>& stack) {
    for(auto current = stack.top; current != NULL; current = current->next)
        out << current->data << " -> ";
    out << "NULL" << std::endl;
    return out;
}