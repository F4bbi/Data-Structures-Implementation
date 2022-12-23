#pragma once

#include "Node.cpp"

/* Forward declaration of the template, so that operator<< is regognized as a template */
template<typename T>
class LinkedList;

template<typename T>
std::ostream& operator<< (std::ostream& out, const LinkedList<T>& list);

template<typename T>
class LinkedList {
    protected:
        Node<T>* head;
    public:
        LinkedList() : head(NULL) {}
        LinkedList(const LinkedList& copyList);
        ~LinkedList();
        void insertLast(T value);
        void initRandom(int size);
        void insertFirst(T value);
        void insertOrder(T value);
        int length() const;
        void deleteElement(T value);
        void deleteFirst();
        void deleteLast();
        Node<T>* get(int position) const;
        void reverse();
        void print() const;
        void clear();
        LinkedList<T>& operator= (const LinkedList<T>& list);
        friend std::ostream& operator<< <> (std::ostream& out, const LinkedList<T>& list);
};