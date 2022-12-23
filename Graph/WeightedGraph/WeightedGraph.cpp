#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <climits>
#include <algorithm>
#include "WeightedGraph.h"

using namespace std;

#define INF INT_MAX

// Initialize graph
WeightedGraph::WeightedGraph(int V) {
    numVertices = V;
    graph.resize(V);
}

int WeightedGraph::size() {
    return numVertices;
}
// example of print:
// 0 -> {4:12, 5:1}
// means 0 has 2 adjacent nodes:
// node 4 with weight 12 and node 5 with weight 1 
void WeightedGraph::print() {
    for(int i = 0; i < numVertices; i++) {
        cout << i << " -> {";
        int j = 0, size = graph.at(i).size() - 1;
        for(j = 0; j < size; j++)
            cout << graph.at(i).at(j)->index << ":" << graph.at(i).at(j)->weight << ", ";
        if(graph.at(i).size())
            cout << graph.at(i).at(j)->index << ":" << graph.at(i).at(j)->weight;
        cout << "}" << endl;
    }
}

void WeightedGraph::initRandom(int numEdges) {
    vector<pair<int, int> > edges;
    for(int i = 0; i < numEdges; i++) {
        int src = rand() % numVertices;
        int dest = rand() % numVertices;
        int weight = rand() % 20;
        if (src != dest && find(edges.begin(), edges.end(), make_pair(src, dest)) == edges.end()) {
            addEdge(src, dest, weight);
            edges.push_back({src, dest});
        }
    }
}

// Add edges
void WeightedGraph::addEdge(int src, int dest, int weight) {
    shared_ptr<Node> node = make_shared<Node>(dest, weight);
    graph.at(src).push_back(node);
}

vector<int> WeightedGraph::dijkstra(int node, bool getPath = false) {
    vector<int> distance(numVertices, INF);
    vector<int> parent(numVertices, -1);
    // We use an ordered set to keep track of the visited vertices.
    // The ordering is applied to the first element of the tuple, so 
    // we store the weight in the first element and the node number in the second element.
    set<pair<int, int> > set;
    // We insert the starting node into the set.
    set.insert(make_pair(0, node));
    // The starting node has a distance of 0 from itself.
    distance.at(node) = 0;
    parent.at(node) = node;
 
    /* Finchè il set non diventa vuoto */
    while (!set.empty()) {
        // We take the first element from the set, which 
        // will be the edge with the minimum distance due to the internal 
        // ordering of the set.
        pair<int, int> tmp = *(set.begin());
        set.erase(set.begin());
        int u = tmp.second;
        // we start iterating through all the children of the current node.
        for (auto& node : graph.at(u)) {
            // We get the index of that child node and its weight.
            int v = node->index;
            int weight = node->weight;

            // and we check if there is shorter path to v through u
            if(distance.at(u) + weight < distance.at(v)) {
                // if the child node was previously inserted into the set 
                // with a greater weight, we remove it and update its path to go 
                // through the current node.
                if(distance.at(v) != INF)
                    set.erase(set.find(make_pair(distance.at(v), v)));

                // We update the distance and 
                // parent vector for the child node and insert it into the set.
                distance.at(v) = distance.at(u) + weight; 
                
                parent.at(v) = u;
                set.insert(make_pair(distance.at(v), v));
            }
        }
    }
    return getPath ? parent : distance;
}

// print the path between two nodes
void WeightedGraph::getPath(int src, int dest) {
    vector<int> parent = dijkstra(src, true);
    printPathHelper(src, dest, parent);
    cout << endl;
}

void WeightedGraph::printPathHelper(int from, int to, const vector<int>& parent) {
    if(from == to) {
        cout << from << " "; 
        return;
    }
    else if(parent.at(to) == -1) {
        cout << "The node " << to << " is unreachable"; 
        return;
    }
    else {
        printPathHelper(from, parent.at(to), parent);
        cout << to << " ";
    }
}