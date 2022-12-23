#include <iostream>
#include <vector>

#include "WeightedGraph.h"
#include "WeightedGraph.cpp"

using namespace std;

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    WeightedGraph graph(15);
    graph.initRandom(30);
    cout << "Graph:" << endl;
    graph.print();
    cout << endl <<"Distances from node 1:" << endl;
    vector<int> distances = graph.dijkstra(1);
    for(size_t i = 0; i < distances.size(); i++) {
        int distance = distances.at(i);
        if(distance != -1)
            cout << "Node " << i << " is " << distance << " nodes away from 1" << std::endl;
        else
            cout << "Node " << i << " is unreachable" << std::endl;
    }
    cout << endl << "Path from node 1 to 14:" << endl;
    graph.getPath(1,14);
    return 0;
}
