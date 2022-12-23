#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>

#include "UndirectedGraph.h"

using namespace std;

UndirectedGraph::UndirectedGraph(int V) {
    numVertices = V;
    graph.resize(V);
}

int UndirectedGraph::size() {
    return numVertices;
}

void UndirectedGraph::addEdge(int src, int dest) {
	graph.at(src).push_back(dest);
	graph.at(dest).push_back(src);
}

void UndirectedGraph::initRandom(int numEdges) {
    vector<pair<int, int> > edges;
    for(int i = 0; i < numEdges; i++) {
        int src = rand() % numVertices;
        int dest = rand() % numVertices;
        if (src != dest && find(edges.begin(), edges.end(), make_pair(src, dest)) == edges.end()) {
            addEdge(src, dest);
            edges.push_back({src, dest});
            edges.push_back({dest, src});
        }
    }
}

/*void UndirectedGraph::print() {
    for(int i = 0; i < numVertices; i++) {
        cout << i << " -> {";
        int j = 0, size = graph.at(i).size() - 1;
        for(j = 0; j < size; j++)
            cout << graph.at(i).at(j) << ", ";
        if(graph.at(i).size())
            cout << graph.at(i).at(j);
        cout << "}" << endl;
    }
}*/

// Recursive Depth-First Search
void UndirectedGraph::DFS_recursive(int node) {
    vector<bool> visited(numVertices, false);
    DFSHelperRecursive(node, visited);
    cout << endl;
}

void UndirectedGraph::DFSHelperRecursive(int node, vector<bool>& visited) {
    visited.at(node) = true;
    cout << node << " ";
    for(int adj : graph.at(node)) {
        if(!visited.at(adj))
            DFSHelperRecursive(adj, visited);
    }
}

// Iterative Depth-First Search (DFS)
void UndirectedGraph::DFS_iterative(int node) {
    vector<bool> visited(graph.size(), false);
    stack<int> stack;
    stack.push(node);
    while(!stack.empty()) {
        int node = stack.top();
        stack.pop();
        if(!visited.at(node)) {
            cout << node << " ";
            visited.at(node) = true;
            for(int adj : graph.at(node)) {  
                stack.push(adj);
            }
        }
    }
    cout << endl;
}

// Iterative Breadth First Search
void UndirectedGraph::BFS(int node) {
    queue<int> queue;
    vector<bool> visited(numVertices, false);
    visited.at(node) = true;
    queue.push(node);
    while(!queue.empty()) {
        int v = queue.front();
	    queue.pop();
	    cout << v << " "; 
        for(int adj : graph.at(v)) {
            if(!visited.at(adj)) {
                visited.at(adj) = true;
                queue.push(adj);
            }
        }
    }
    cout << endl;
}

// Return all node distances from given node or the path between 2 nodes
vector<int> UndirectedGraph::erdosNumber(int node, bool getPath = false) {
    vector<int> distance(numVertices, -1);
    vector<int> parent(numVertices, -1);
    queue<int> queue;
    distance.at(node) = 0;
    parent.at(node) = node;
    queue.push(node);
    while(!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for(int adj : graph.at(v)) {
            if(distance.at(adj) == -1) {
                distance.at(adj) = distance.at(v) + 1;
                parent.at(adj) = v;
                queue.push(adj);
            }
        }
    }
    return getPath ? parent : distance;
}

void UndirectedGraph::getPath(int src, int dest) {
    vector<int> parent = erdosNumber(src, true);
    printPathHelper(src, dest, parent);
    cout << endl;    
}

void UndirectedGraph::printPathHelper(int from, int to, const vector<int>& parent) {
    if(from == to) {
        cout << from << " "; 
        return;
    }
    else if(parent.at(to) == -1) {
        cout << "The node " << to << " is unreachable" << endl; 
        return;
    }
    else {
        printPathHelper(from, parent.at(to), parent);
        cout << to << " ";
    }
}

// Check if a graph has a cycle
bool UndirectedGraph::hasCycle() {
    vector<bool> visited(numVertices, false);
    for(int node = 0; node < numVertices; node++) {
        /* In case that graph has more than 1 connected component */
        if(!visited.at(node))
            if(hasCycleHelper(node, -1, visited))
                return true;
    }
    return false;
}

bool UndirectedGraph::hasCycleHelper(int node, int parent, vector<bool>& visited) {
    visited.at(node) = true;
    for(int adj : graph.at(node)) {
        if(adj != parent) {
            if(visited.at(adj))
                return true;
            else if(hasCycleHelper(adj, node, visited))
                return true;
        }
    }
    return false;
}

// Output the number of connected components
int UndirectedGraph::connectedComponents() {
    /* id will map every node with his connected component */
    vector<int> id(numVertices, 0);
    int counter = 0;
    for(int node = 0; node < numVertices; node++) {
        if(id.at(node) == 0) {
            ++counter;
            cc_DFS(node, id, counter);
        }
    }
    return counter;
}

// DFS applied to connected components
void UndirectedGraph::cc_DFS(int node, vector<int> & id, int counter) {
    id.at(node) = counter;
    for(int adj : graph.at(node)) {
        if(id.at(adj) == 0)
            cc_DFS(adj, id, counter);
    }
}
