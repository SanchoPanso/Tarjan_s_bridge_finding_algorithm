#ifndef TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H
#define TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H

#include <vector>

// A class that represents an undirected graph
class Graph{
private:
    int V;    // No. of vertices
    std::vector<std::vector<int>> adj; // adjacency vector
    void bridge_dfs(int u,
                    std::vector<bool> &visited,
                    std::vector<int> &disc,
                    std::vector<int> &low,
                    std::vector<int> &parent);
public:
    Graph();
    explicit Graph(int V);
    explicit Graph(std::vector<std::vector<int>> &adj);
    void add_edge(int v, int w);
    int get_number_of_edges();
    bool edge_is_in_graph(int v, int w);
    void find_bridges();
};

Graph create_random_graph(int number_of_edges);

#endif
