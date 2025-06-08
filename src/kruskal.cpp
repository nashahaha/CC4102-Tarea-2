#include <vector>
#include <iostream>
#include <algorithm>    // std::sort
#include <queue>
#include "graph.cpp"

bool sortByWeight(Edge a1, Edge a2){
    return a1.peso<a2.peso;
}


bool sortByWeightHeap(Edge a1, Edge a2){
    return a1.peso>a2.peso;
}

// Algoritmo de Kruskal sin la optimización de find y usando un arreglo de aristas ordenado
// Retorna la lista de aristas que minimiza el costo
std::vector<Edge> kruskal_array(Graph& G){
    // Se ordenan las aristas por peso
    std::vector<Edge> sorted_edges = G.E;
    std::sort (sorted_edges.begin(), sorted_edges.end(), sortByWeight);

    int n = G.V.size();
    std::vector<Edge> result;

    std::vector<int> component(n);
    for (int i=0; i<n; ++i) component[i] = i; // cada nodo es parte de su propio bosque

    for (const Edge& e : sorted_edges) {
        int id1 = e.n1->id;
        int id2 = e.n2->id;

        if (component[id1] != component[id2]) {
            result.push_back(e);

            // Unir componentes: cambiar todos los nodos del componente viejo al nuevo
            int old_comp = component[id2];
            int new_comp = component[id1];

            for (int i=0; i<n; ++i) {
                if (component[i] == old_comp)
                    component[i] = new_comp;
            }

            if (result.size() == n-1) break;
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

    std::vector<int> component(n);
    for (int i=0; i<n; ++i) component[i] = i; // cada nodo es parte de su propio bosque

    while (result.size() < n-1) {
        Edge e = heap.top();
        heap.pop();

        int id1 = e.n1->id;
        int id2 = e.n2->id;

        if (component[id1] != component[id2]) {
            result.push_back(e);

            int old_comp = component[id2];
            int new_comp = component[id1];

            for (int i=0; i<n; ++i) {
                if (component[i] == old_comp)
                    component[i] = new_comp;
            }
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


