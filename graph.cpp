#include<iostream>
#include <list>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "graph.h"

#define NIL -1

Graph::Graph() {
    V = 0;
}

Graph::Graph(int V){
    this->V = V;
    adj = std::vector<std::vector<int>>(V);
}

Graph::Graph(std::vector<std::vector<int>> &adj){
    this->V = (int) adj.size();
    this->adj = adj;
}

void Graph::add_edge(int v, int w){
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

int Graph::get_number_of_edges(){
    int num = 0;
    for (auto & it : adj){
        num += it.size();
    }
    return num / 2; // each edge counts twice
}

bool Graph::edge_is_in_graph(int v, int w){
    if (std::find(adj[v].begin(), adj[v].end(), w) != adj[v].end())
        return true;
    return false;
}

// A recursive function that finds and prints bridges using
// DFS traversal
// u --> The vertex to be visited next
// visited[] --> keeps track of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
void Graph::bridge_dfs(int u,
                       std::vector<bool> &visited,
                       std::vector<int> &disc,
                       std::vector<int> &low,
                       std::vector<int> &parent){
    // A static variable is used for simplicity, we can
    // avoid use of static variable by passing a pointer.
    static int time = 0;

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices adjacent to this
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it)
    {
        int v = *it;  // v is current adjacent of u

        // If v is not visited yet, then recur for it
        if (!visited[v])
        {
            parent[v] = u;
            bridge_dfs(v, visited, disc, low, parent);

            // Check if the subtree rooted with v has a
            // connection to one of the ancestors of u
            low[u]  = std::min(low[u], low[v]);

            // If the lowest vertex reachable from subtree
            // under v is  below u in DFS tree, then u-v
            // is a find_bridges
            if (low[v] > disc[u])
                std::cout << u <<" " << v << std::endl;
        }

            // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u]  = std::min(low[u], disc[v]);
    }
}

// DFS based function to find all bridges. It uses recursive
// function bridge_dfs()
void Graph::find_bridges()
{
    // Mark all the vertices as not visited
    std::vector<bool> visited(V);
    std::vector<int> disc(V);
    std::vector<int> low(V);
    std::vector<int> parent(V);

    // Initialize parent and visited arrays
    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
    }

    // Call the recursive helper function to find Bridges
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < V; i++)
        if (!visited[i])
            bridge_dfs(i, visited, disc, low, parent);
}


Graph create_random_graph(int number_of_edges){

    // number of vertexes when every vertex joins with all others vertexes
    int min_number_of_vertexes = (1 + (int) ceil(sqrt(1 + 8.0 * number_of_edges))) / 2;

    // number of vertexes when graph is a chain
    int max_number_of_vertexes = number_of_edges + 1;

    // number of vertexes is somewhere between max and min values
    int number_of_vertexes = min_number_of_vertexes + rand() % (max_number_of_vertexes - min_number_of_vertexes + 1);
    int number_of_added_vertexes = 0;

    Graph graph(number_of_vertexes);
    for (int v = 0; v < number_of_vertexes; v++){
        for (int w = 0; w < number_of_vertexes; w++){
            if (v != w && rand() % number_of_vertexes >= number_of_added_vertexes){
                graph.add_edge(v, w);
                number_of_added_vertexes++;
            }
            if (number_of_added_vertexes == number_of_vertexes){
                return graph;
            }
        }
    }

    if (number_of_added_vertexes != number_of_vertexes){
        for (int v = 0; v < number_of_vertexes; v++){
            for (int w = 0; w < number_of_vertexes; w++){
                if (!graph.edge_is_in_graph(v, w)){
                    graph.add_edge(v, w);
                    number_of_added_vertexes++;
                }
                if (number_of_added_vertexes == number_of_vertexes){
                    return graph;
                }
            }
        }
    }
    return graph;
}
