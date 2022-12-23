#include <iostream>

#include "Queue.h"
#include "Queue.cpp"

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    Queue<int> queue;
    queue.initRandom(5);
    std::cout << queue;
    queue.remove();
    queue.remove();
    std::cout << queue;
    queue.add(3);
    std::cout << queue;
    queue.clear();
    queue.print();
    queue.remove();
    return 0;
}
