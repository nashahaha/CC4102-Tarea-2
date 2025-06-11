#include <algorithm>    // std::sort
#include <queue>
#include "UnionFind.cpp"
#include "aux_f.cpp"


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
        int raiz_x = uf.find_no_opt(edge.n1->id);
        int raiz_y = uf.find_no_opt(edge.n2->id);
        if (raiz_x != raiz_y) { 
            uf.union_(raiz_x, raiz_y);
            result.push_back(edge);
            if (result.size() == n - 1) break; // cuando se encuentran las n-1 aristas se termina
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
        int raiz_x = uf.find(edge.n1->id);
        int raiz_y = uf.find(edge.n2->id);

        if (raiz_x != raiz_y) { 
            uf.union_(raiz_x, raiz_y);
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

        int raiz_x = uf.find_no_opt(edge.n1->id);
        int raiz_y = uf.find_no_opt(edge.n2->id);

        if (raiz_x != raiz_y) { 
            uf.union_(raiz_x, raiz_y);
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

        int raiz_x = uf.find(edge.n1->id);
        int raiz_y = uf.find(edge.n2->id);

        if (raiz_x != raiz_y) {
            uf.union_(raiz_x, raiz_y); 
            result.push_back(edge);
        }
    }

    return result;
}
