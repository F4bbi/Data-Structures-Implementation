#include <iostream>

#include "LinkedList.h"
#include "LinkedList.cpp"

int main(int argc, char const *argv[])
{
    srand(time(NULL)); //for random numbers
    LinkedList<int> list;
    list.insertOrder(2);
    list.insertOrder(1);
    list.print();
    list.reverse();
    list.print();
    return 0;
}
