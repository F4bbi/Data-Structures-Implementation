#include <iostream>
#include <vector>
#include <stack>

#include "DirectedGraph.h"
#include "DirectedGraph.cpp"

using namespace std;

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    DirectedGraph graph(5);
    graph.initRandom(6);
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
    cout << endl << "Path from node 1 to 4:" << endl;
    graph.getPath(1,4);
    cout << endl << "Has this graph a cycle inside? " << graph.hasCycle() << endl;
    cout << endl << "Topological sort: " << endl;
    stack<int> stack = graph.topologicalSort();
    while (!stack.empty()) {
        int val = stack.top();
        cout << val << " ";
        stack.pop();
    }
    cout << endl;
    cout << endl << "Number of connected components: " << graph.connectedComponents() << endl;
    return 0;
}
