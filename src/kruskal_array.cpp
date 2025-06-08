#include <vector>
#include <iostream>
#include <algorithm>    // std::sort
#include "graph.cpp"

bool sortByWeight(Edge a1, Edge a2){
    return a1.peso<a2.peso;
}

// Algoritmo de Kruskal sin la optimización de find y usando un arreglo de aristas ordenado
// Retorna la lista de aristas que minimiza el costo
std::vector<Edge> kruskal_array(Graph g){
    // Se ordenan las aristas por peso
    std::vector<Edge> sorted_edges = g.E;
    std::sort (sorted_edges.begin(), sorted_edges.end(), sortByWeight);

    int N = g.V.size();

    for (auto& edge : sorted_edges){
        
    }

    return sorted_edges;
}

// Algoritmo de Kruskal con la optimización de find y usando un arreglo de aristas ordenado
// Retorna la lista de aristas que minimiza el costo
std::vector<Edge> kruskal_array_Opti(Graph& G){
    // Se ordenan las aristas por peso
    std::vector<Edge> sorted_edges = G.E;
    std::sort (sorted_edges.begin(), sorted_edges.end(), sortByWeight);
    
    int n = G.V.size(); // contador de aristas
    std::vector<Edge> result;

    UnionFind uf(n);

    for (auto& edge : sorted_edges){
        int idx1 = -1, idx2 = -1;

        if (uf.union_(edge.n1->id, edge.n2->id)) { 
            result.push_back(edge);
            if (result.size() == n - 1) break; // cuando se encuentran n-1 aristas se termina
        }
    }


    return result;
}

//Duncion auxiliar para ver que aristas se escogieron como optimas
void printEdges(std::vector<Edge> edgesList){
    std::cout << "Las aristas que minimizan el peso son: ";
    for(auto a :edgesList){
        std::cout << "(" << a.n1->id << "," << a.n2->id << ")" <<
        " -> w:" << a.peso << "  ";
    }
    std::cout << "\n";
}

int main(){
    std::vector<Node> nodos1 = { Node(1, 2), Node(4, 6), Node(-3, 7), Node(1,1), Node(2,3), Node(0,4) };
    Graph g1(nodos1);
    g1.addAllEdges();
    g1.print();

    std::vector<Edge> aristasOpt = kruskal_array_Opti(g1);
    printEdges(aristasOpt);

    std::vector<Node> nodos2 = { Node(-2, 2), Node(8, 2), Node(6, 4), Node(-6,2), Node(2, -2), Node(0,-4) };
    Graph g2(nodos2);
    g2.addAllEdges();
    g2.print();

    std::vector<Edge> aristasOpt2 = kruskal_array_Opti(g2);
    printEdges(aristasOpt2);

    std::vector<Node> nodos3 = { Node(), Node(), Node(), Node()};
    Graph g3(nodos3);
    g3.addAllEdges();
    g3.print();

    std::vector<Edge> aristasOpt3 = kruskal_array_Opti(g3);
    printEdges(aristasOpt3);

    return 0;
}