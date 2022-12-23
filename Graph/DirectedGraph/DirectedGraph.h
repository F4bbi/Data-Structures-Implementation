#pragma once

#include <iostream> 
#include <vector>
#include <stack>

using namespace std;
  
class DirectedGraph {
    private:
        vector<vector<int> > graph;
        int numVertices;
        void DFSHelperRecursive(int node, vector<bool>& visited);
        void printPathHelper(int from, int to, const vector<int>& parent);
        bool hasCycleHelper(int node, int& time, vector<int>& dt, vector<int>& ft);
        void ts_DFS(int node, stack<int>& stack, vector<bool>& visited);
        int cc_helper(vector<vector<int> >& transposed_graph, stack<int> stack);
        void DFS_cc(vector<vector<int> >& transposed_graph, int node, vector<int> & id, int counter);
    public:
        DirectedGraph(int V);
        int size();
        void addEdge(int src, int dest);
        void initRandom(int numEdges);
        void print();
        void DFS_iterative(int node);
        void DFS_recursive(int node);
        void BFS(int node);
        vector<int> erdosNumber(int node, bool getPath);
        void getPath(int src, int dest);
        bool hasCycle();
        stack<int> topologicalSort();
        int connectedComponents();
        vector<vector<int> > transpose();
};