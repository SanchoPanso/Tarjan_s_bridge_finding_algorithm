// A C++ program to find bridges in a given undirected graph
#include<iostream>
#include <list>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>

#define NIL -1


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


// Driver program to test above function
int main()
{

    srand(123);

    Graph graph1 = create_random_graph(6);
    std::cout << graph1.get_number_of_edges() << '\n';


    // Create graphs given in above diagrams
    std::cout << "\nBridges in first graph \n";
    Graph g1(5);
    g1.add_edge(1, 0);
    g1.add_edge(0, 2);
    g1.add_edge(2, 1);
    g1.add_edge(0, 3);
    g1.add_edge(3, 4);
    g1.bridge();

    std::cout << "\nBridges in second graph \n";
    Graph g2(4);
    g2.add_edge(0, 1);
    g2.add_edge(1, 2);
    g2.add_edge(2, 3);
    g2.bridge();

    std::cout << "\nBridges in third graph \n";
    Graph g3(7);
    g3.add_edge(0, 1);
    g3.add_edge(1, 2);
    g3.add_edge(2, 0);
    g3.add_edge(1, 3);
    g3.add_edge(1, 4);
    g3.add_edge(1, 6);
    g3.add_edge(3, 5);
    g3.add_edge(4, 5);
    g3.bridge();

    return 0;
}









//#include <iostream>
//#include <vector>
//
//using std::pair;
//using std::vector;
//using std::min;
//
//// adj[u] = adjacent nodes of u
//// ap = AP = articulation points
//// p = parent
//// disc[u] = discovery time of u
//// low[u] = 'low' node of u
//// br = bridges, p = parent
//
//vector<pair<int, int>> br;
//
//int Time;
//vector<int> low;
//vector<int> disc;
//vector<vector<int>> adj = {{1, 2, 3},
//                           {0, 2},
//                           {0, 1},
//                           {0}};
//
//void dfsBR(int u, int p) {
//  low[u] = disc[u] = ++Time;
//  for (int & v : adj[u]) {
//    if (v == p) continue;   // we don't want to go back through the same path.
//                            // if we go back is because we found another way back
//    if (!disc[v]) {     // if V has not been discovered before
//      dfsBR(v, u);      // recursive DFS call
//      if (disc[u] < low[v]) // condition to find a bridge
//        br.emplace_back(u, v);
//      low[u] = min(low[u], low[v]);     // low[v] might be an ancestor of u
//    } else                              // if v was already discovered means that we found an ancestor
//      low[u] = min(low[u], disc[v]);    // finds the ancestor with the least discovery time
//  }
//}
//
//void BR() {
//  low = disc = vector<int>(adj.size());
//  Time = 0;
//  for (int u = 0; u < adj.size(); u++)
//    if (!disc[u])
//      dfsBR(u, u);
//}
//
//int main() {
//    BR();
//    for (auto & i : br)
//        std::cout << i.first << ' ' << i.second << '\n';
//    return 0;
//}
