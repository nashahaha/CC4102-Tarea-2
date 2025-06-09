#include <vector>
#include <iostream>
#include <algorithm>    // std::sort
#include <queue>
#include "graph.cpp"
#include "UnionFind.cpp"

bool sortByWeight(Edge a1, Edge a2){
    return a1.peso<a2.peso;
}


bool sortByWeightHeap(Edge a1, Edge a2){
    return a1.peso>a2.peso;
}

bool mismosPesos(const std::vector<Edge>& A,
    const std::vector<Edge>& B,
    const std::vector<Edge>& C,
    const std::vector<Edge>& D) {

    auto suma = [](const std::vector<Edge>& edges) -> double {
        double total = 0;
        for (const Edge& e : edges) total += e.peso;
        return total;
    };

    double pesoA = suma(A);
    double pesoB = suma(B);
    double pesoC = suma(C);
    double pesoD = suma(D);

    return (pesoA == pesoB) && (pesoB == pesoC) && (pesoC == pesoD);
}

// Algoritmo de Kruskal sin la optimización de find y usando un arreglo de aristas ordenado
// Retorna la lista de aristas que minimiza el costo
std::vector<Edge> kruskal_array(Graph& G){
    // Se ordenan las aristas por peso
    std::vector<Edge> sorted_edges = G.E;
    std::sort (sorted_edges.begin(), sorted_edges.end(), sortByWeight);

    int n = G.V.size();
    std::vector<Edge> result;

    UnionFind uf(n);

    for (auto& edge : sorted_edges){
        if (uf.union_no_opt(edge.n1->id, edge.n2->id)) { 
            result.push_back(edge);
            if (result.size() == n - 1) break; // cuando se encuentran n-1 aristas se termina
        }
    }


    return result;
}

// Algoritmo de Kruskal con la optimización de find y usando un arreglo de aristas ordenado
// Retorna la lista de aristas que minimiza el costo
std::vector<Edge> kruskal_array_Opti(Graph& G){
    
    // Se ordenan las aristas por peso
    std::vector<Edge> sorted_edges = G.E;
    std::sort (sorted_edges.begin(), sorted_edges.end(), sortByWeight);
    
    int n = G.V.size();
    std::vector<Edge> result;

    UnionFind uf(n);

    for (auto& edge : sorted_edges){
        if (uf.union_(edge.n1->id, edge.n2->id)) { 
            result.push_back(edge);
            if (result.size() == n - 1) break; // cuando se encuentran n-1 aristas se termina
        }
    }

    return result;
}




// ------------------------------------------------------------------------------------------------


// Algoritmo de Kruskal sin la optimización de find y usando un heap
// Retorna la lista de aristas que minimiza el costo
std::vector<Edge> kruskal_heap(Graph& G){
    // Se ordenan las aristas por peso
    std::vector<Edge> sorted_edges = G.E;
    std::priority_queue heap(sorted_edges.begin(), sorted_edges.end(), sortByWeightHeap);

    int n = G.V.size();
    std::vector<Edge> result;

    UnionFind uf(n);

    while(result.size() < n-1 ){
        Edge edge = heap.top();
        heap.pop();
        if (uf.union_no_opt(edge.n1->id, edge.n2->id)) { 
            result.push_back(edge);
        }
    }

    return result;
}

// Algoritmo de Kruskal con la optimización de find y usando un heap
// Retorna la lista de aristas que minimiza el costo
std::vector<Edge> kruskal_heap_Opti(Graph& G){
    // Se ordenan las aristas por peso
    std::vector<Edge> sorted_edges = G.E;
    std::priority_queue heap(sorted_edges.begin(), sorted_edges.end(), sortByWeightHeap);
    
    int n = G.V.size();
    std::vector<Edge> result;

    UnionFind uf(n);

    while(result.size() < n-1 ){
        Edge edge = heap.top();
        heap.pop();
        if (uf.union_(edge.n1->id, edge.n2->id)) { 
            result.push_back(edge);
        }
    }

    return result;
}

//Funcion auxiliar para ver que aristas se escogieron como optimas
void printEdges(std::vector<Edge> edgesList){
    std::cout << "Las aristas que minimizan el peso son: ";
    for(auto a :edgesList){
        std::cout << "(" << a.n1->id << "," << a.n2->id << ")" << "->w:" << a.peso << "  ";
    }
    std::cout << "\n";
}


