#include <iostream>

#include "Stack.h"
#include "Stack.cpp"

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    Stack<int> stack;
    stack.initRandom(5);
    std::cout << stack;
    stack.pop();
    stack.pop();
    std::cout << stack;
    stack.push(3);
    std::cout << stack;
    stack.clear();
    stack.print();
    stack.pop();
    return 0;
}
