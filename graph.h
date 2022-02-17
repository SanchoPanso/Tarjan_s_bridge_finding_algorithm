#ifndef TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H
#define TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H

// A class that represents an undirected graph
class Graph{
    int V;    // No. of vertices
    std::vector<std::vector<int>> adj; // A dynamic array of adjacency lists
    void bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[]);
public:
    Graph();
    explicit Graph(int V);
    explicit Graph(std::vector<std::vector<int>> &adj);
    void add_edge(int v, int w);
    int get_number_of_edges();
    bool edge_is_in_graph(int v, int w);
    void bridge();// prints all bridges
};

#endif
