#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>

#include "DirectedGraph.h"

using namespace std;

DirectedGraph::DirectedGraph(int V) {
    numVertices = V;
    graph.resize(V);
}

int DirectedGraph::size() {
    return numVertices;
}

void DirectedGraph::addEdge(int src, int dest) {
	graph.at(src).push_back(dest);
}

void DirectedGraph::initRandom(int numEdges) {
    vector<pair<int, int> > edges;
    for(int i = 0; i < numEdges; i++) {
        int src = rand() % numVertices;
        int dest = rand() % numVertices;
        if (src != dest && find(edges.begin(), edges.end(), make_pair(src, dest)) == edges.end()) {
            addEdge(src, dest);
            edges.push_back({src, dest});
        }
    }
}

void DirectedGraph::print() {
    for(int i = 0; i < numVertices; i++) {
        cout << i << " -> {";
        int j = 0, size = graph.at(i).size() - 1;
        for(j = 0; j < size; j++)
            cout << graph.at(i).at(j) << ", ";
        if(graph.at(i).size())
            cout << graph.at(i).at(j);
        cout << "}" << endl;
    }
}

// Recursive Depth-First Search
void DirectedGraph::DFS_recursive(int node) {
    vector<bool> visited(numVertices, false);
    DFSHelperRecursive(node, visited);
    cout << endl;
}

void DirectedGraph::DFSHelperRecursive(int node, vector<bool>& visited) {
    visited.at(node) = true;
    cout << node << " ";
    for(int adj : graph.at(node)) {
        if(!visited.at(adj))
            DFSHelperRecursive(adj, visited);
    }
}

// Iterative Depth-First Search (DFS)
void DirectedGraph::DFS_iterative(int node) {
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
void DirectedGraph::BFS(int node) {
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
vector<int> DirectedGraph::erdosNumber(int node, bool getPath = false) {
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
                if(getPath) parent.at(adj) = v;
                queue.push(adj);
            }
        }
    }
    return getPath ? parent : distance;
}

void DirectedGraph::getPath(int src, int dest) {
    vector<int> parent = erdosNumber(src, true);
    printPathHelper(src, dest, parent);
    cout << endl;    
}

void DirectedGraph::printPathHelper(int from, int to, const vector<int>& parent) {
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
bool DirectedGraph::hasCycle() {
    /* discovery time of every node */
    vector<int> dt(numVertices, 0);
    /* finish time of every node */
    vector<int> ft(numVertices, 0);
    int time = 0;
    for(int node = 0; node < numVertices; node++) {
        /* in case that graph is a forest */
        if(dt.at(node) == 0)
            if(hasCycleHelper(node, time, dt, ft))
                return true;
    }
    return false;
}

bool DirectedGraph::hasCycleHelper(int node, int& time, vector<int>& dt, vector<int>& ft) {
    ++time;
    dt.at(node) = time;
    for(int adj : graph.at(node)) {
        if(dt.at(adj) == 0) {
            if(hasCycleHelper(adj, time, dt, ft))
                return true;
        }
        /* back edge found */
        else if(dt.at(adj) < dt.at(node) && ft.at(adj) == 0)
            return true;
    }
    ++time;
    ft.at(node) = time;
    return false;
}

// Topological sort
stack<int> DirectedGraph::topologicalSort() {
    vector<bool> visited(numVertices, false);
    stack<int> stack;

    for(int node = 0; node < numVertices; node++) {
        if(!visited.at(node))
            ts_DFS(node, stack, visited);
    }
    return stack;
}

void DirectedGraph::ts_DFS(int node, stack<int>& stack, vector<bool>& visited) {
    visited.at(node) = true;
    for(int adj : graph.at(node)) {
        if(!visited.at(adj))
            ts_DFS(adj, stack, visited);
    }
    stack.push(node);
}

// Output the number of connected components
int DirectedGraph::connectedComponents() {
    stack<int> stack = topologicalSort();
    vector<vector<int> > transposed_graph = transpose();
    return cc_helper(transposed_graph, stack);
}

vector<vector<int> > DirectedGraph::transpose() {
    vector<vector<int> > transposed_graph(numVertices);
    for(int node = 0; node < numVertices; node++) {
        for(int adj : graph.at(node)) {
            transposed_graph.at(adj).push_back(node);
        }
    }
    return transposed_graph;
}

int DirectedGraph::cc_helper(vector<vector<int> >& transposed_graph, stack<int> stack) {
    vector<int> id(numVertices, 0);
    int counter = 0;
    while(!stack.empty()) {
        int node = stack.top();
        stack.pop();
        if(id.at(node) == 0) {
            ++counter;
            DFS_cc(transposed_graph, node, id, counter);
        }
    }
    return counter;
}

void DirectedGraph::DFS_cc(vector<vector<int> >& transposed_graph, int node, vector<int> & id, int counter) {
    id.at(node) = counter;
    for(int adj : transposed_graph.at(node)) {
        if(id.at(adj) == 0)
            DFS_cc(transposed_graph, adj, id, counter);
    }
}