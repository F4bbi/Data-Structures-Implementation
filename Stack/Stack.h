#pragma once

/* Forward declaration of the template, so that operator<< is regognized as a template */
template<class T>
class Stack;

template<class T>
std::ostream& operator<< (std::ostream& out, const Stack<T>& stack);

template<class T>
class Stack {
    class Node {
        public:
            T data;
            Node* next;
            
            // default constructor
            Node() = default;

            // constructor with data
            Node(const T& value) : data(value), next{NULL} {}
    };
    protected:
        Node* top;
    public:
        Stack() : top(NULL) {}
        Stack(const Stack& copySist);
        ~Stack();
        void initRandom(int size);
        T pop();
        void push(T value);
        T peek() const;
        bool isEmpty() const;
        void print() const;
        void clear();
        Stack<T>& operator= (const Stack<T>& stack);
        friend std::ostream& operator<< <> (std::ostream& out, const Stack<T>& stack);
};