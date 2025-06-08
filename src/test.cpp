#include <vector>
#include <iostream>
#include <algorithm>    // std::sort
#include "graph.cpp"
// Este main es para probar las funcionalidades del grafo, se debe eliminar

int main(){
    std::vector<Node> nodos1 = { Node(1, 2), Node(4, 6), Node(-3, 7), Node(1,1), Node(2,3), Node(0,4) };
    Graph g1(nodos1);
    g1.print();

    g1.addAllEdges();
    g1.print();
    
    return 1;
}