#include <iostream>
#include <vector>

#include "UndirectedGraph.h"
#include "UndirectedGraph.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    UndirectedGraph graph(15);
    graph.initRandom(20);
    cout << "Graph:" << endl;
    graph.print();
    cout << endl << "Graph BFS:" << endl;
    graph.BFS(1);
    cout << endl << "Graph DFS recursive:" << endl;
    graph.DFS_recursive(1);
    cout << endl << "Graph DFS iterative:" << endl;
    graph.DFS_iterative(1);
    cout << endl <<"Distances from node 1:" << endl;
    vector<int> distances = graph.erdosNumber(1);
    for(size_t i = 0; i < distances.size(); i++) {
        int distance = distances.at(i);
        if(distance != -1)
            cout << "Node " << i << " is " << distance << " nodes away from 1" << std::endl;
        else
            cout << "Node " << i << " is unreachable" << std::endl;
    }
    cout << endl << "Path from node 1 to 11:" << endl;
    graph.getPath(1,11);
    cout << endl << "Has this graph a cycle inside? " << graph.hasCycle() << endl;
    cout << endl << "Number of connected components: " << graph.connectedComponents() << endl;
    return 0;
}
