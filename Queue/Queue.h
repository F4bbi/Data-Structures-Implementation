#pragma once

#include <iostream> 

/* Forward declaration of the template, so that operator<< is regognized as a template */
template<class T>
class Queue;

template<class T>
std::ostream& operator<< (std::ostream& out, const Queue<T>& queue);

template<class T>    
class Queue {
    class Node {
        public:
            T data;
            Node* next;
            
            // default constructor
            Node() = default;
            // constructor with data
            Node(const T& value) : data(value), next(NULL) {}
    };
    protected:
        Node* first;
        Node* last;
    public:
        Queue() : first(NULL), last(NULL) {}
        Queue(const Queue& copyQueue);
        ~Queue();
        void initRandom(int size);
        T remove();
        void add(T value);
        T peek() const;
        bool isEmpty() const;
        void print() const;
        void clear();
        Queue<T>& operator= (const Queue<T>& queue);
        friend std::ostream& operator<< <> (std::ostream& out, const Queue<T>& queue);
};