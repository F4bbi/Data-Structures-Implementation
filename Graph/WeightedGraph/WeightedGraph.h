#pragma once

using namespace std;
  
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class WeightedGraph {
    class Node {
        public:
            int index;
            int weight;
            // default constructor
            Node() = default;
            Node(int index, int weight) : index(index) , weight(weight) {} 
    };
    private:
        int numVertices;
        vector<vector<shared_ptr<Node> > > graph;
        void printPathHelper(int from, int to, const vector<int>& parent);
    public:
        WeightedGraph(int numVertices);
        void print();
        int size();
        void initRandom(int numEdges);
        void addEdge(int src, int dest, int weight);
        vector<int> dijkstra(int node, bool getPath);
        void getPath(int src, int dest);
};