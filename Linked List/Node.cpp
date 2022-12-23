#pragma once

template<typename T>
class Node {
    public:
        T data;
        Node* next;
        
        // default constructor
        Node() = default;

        // constructor with data
        Node(const T& value) : data(value), next{NULL} {}
};