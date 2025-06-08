#include <vector>
#include <iostream>
#include "graph.cpp"
#include "kruskal.cpp"

int main(){
    std::vector<Node> nodos1 = { Node(1, 2), Node(4, 6), Node(-3, 7), Node(1,1), Node(2,3), Node(0,4) };
    Graph g1(nodos1);
    g1.addAllEdges();
    g1.print();

    std::vector<Edge> aristasOpt = kruskal_array_Opti(g1);
    printEdges(aristasOpt);
    std::vector<Edge> aristas = kruskal_array(g1);
    printEdges(aristas);
    std::vector<Edge> aristasHeap1 = kruskal_heap(g1);
    printEdges(aristasHeap1);
    std::vector<Edge> aristasHeapOpti1 = kruskal_heap_Opti(g1);
    printEdges(aristasHeapOpti1);

    std::vector<Node> nodos2 = { Node(-2, 2), Node(8, 2), Node(6, 4), Node(-6,2), Node(2, -2), Node(0,-4) };
    Graph g2(nodos2);
    g2.addAllEdges();
    g2.print();

    std::vector<Edge> aristasOpt2 = kruskal_array_Opti(g2);
    printEdges(aristasOpt2);
    std::vector<Edge> aristas2 = kruskal_array(g2);
    printEdges(aristas2);
    std::vector<Edge> aristasHeap2 = kruskal_heap(g2);
    printEdges(aristasHeap2);
    std::vector<Edge> aristasHeapOpti2 = kruskal_heap_Opti(g2);
    printEdges(aristasHeapOpti2);

    std::vector<Node> nodos3 = { Node(), Node(), Node(), Node()};
    Graph g3(nodos3);
    g3.addAllEdges();
    g3.print();

    std::vector<Edge> aristasOpt3 = kruskal_array_Opti(g3);
    printEdges(aristasOpt3);
    std::vector<Edge> aristas3 = kruskal_array(g3);
    printEdges(aristas3);
    std::vector<Edge> aristasHeap3 = kruskal_heap(g3);
    printEdges(aristasHeap3);
    std::vector<Edge> aristasHeapOpti3 = kruskal_heap_Opti(g3);
    printEdges(aristasHeapOpti3);

    return 0;
}