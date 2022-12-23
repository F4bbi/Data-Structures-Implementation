#pragma once

#include <iostream> 
#include <vector>
  
class UndirectedGraph {
    private:
        std::vector<std::vector<int> > graph;
        int numVertices;
        void DFSHelperRecursive(int node, std::vector<bool>& visited);
        void printPathHelper(int from, int to, const std::vector<int>& parent);
        bool hasCycleHelper(int node, int parent, std::vector<bool>& visited);
        void cc_DFS(int node, std::vector<int> & id, int counter);
    public:
        UndirectedGraph(int V);
        int size();
        void addEdge(int src, int dest);
        void initRandom(int numEdges);
        void print();
        void DFS_iterative(int node);
        void DFS_recursive(int node);
        void BFS(int node);
        std::vector<int> erdosNumber(int node, bool getPath);
        void getPath(int src, int dest);
        bool hasCycle();
        int connectedComponents();
};