#include <algorithm>    // std::sort
#include <queue>
#include "UnionFind.cpp"
#include "aux_f.cpp"

/**
 * @brief Implementación del algoritmo de Kruskal sin optimización en la operación find y utilizando un arreglo de aristas ordenado.
 *
 * Esta función construye un árbol de expansión mínima (MST) a partir de un grafo no dirigido.
 * Utiliza el algoritmo de Kruskal, ordenando previamente las aristas por peso en orden ascendente.
 * Las operaciones de unión y búsqueda se realizan mediante una estructura `UnionFind`, pero
 * la función `find_no_opt` no aplica compresión de caminos.
 *
 * @param G Grafo de entrada, que contiene un conjunto de nodos (`G.V`) y aristas (`G.E`).
 * @return Un vector con las aristas que conforman el árbol de expansión mínima del grafo.
 */
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

/**
 * @brief Implementación del algoritmo de Kruskal con optimización en la operación find y utilizando un arreglo de aristas ordenado.
 *
 * Esta función construye un árbol de expansión mínima (MST) a partir de un grafo no dirigido.
 * Utiliza el algoritmo de Kruskal, ordenando previamente las aristas por peso en orden ascendente.
 *
 * @param G Grafo de entrada, que contiene un conjunto de nodos (`G.V`) y aristas (`G.E`).
 * @return Un vector con las aristas que conforman el árbol de expansión mínima del grafo.
 */
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


/**
 * @brief Implementación del algoritmo de Kruskal sin optimización en la operación find y utilizando un heap.
 *
 * Esta función construye un árbol de expansión mínima (MST) a partir de un grafo no dirigido.
 * A diferencia de la versión basada en arreglo ordenado, aquí se utiliza un heap (`priority_queue`) 
 * para obtener iterativamente la arista de menor peso..
 *
 * Las búsquedas de raíces (`find_no_opt`) no están optimizadas, es decir, no utilizan compresión de caminos.
 *
 * @param G Grafo de entrada, que contiene un conjunto de nodos (`G.V`) y aristas (`G.E`).
 * @return Un vector con las aristas que conforman el árbol de expansión mínima del grafo.
 */
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

/**
 * @brief Implementación del algoritmo de Kruskal con optimización en la operación find y utilizando un heap.
 *
 * Esta función construye un árbol de expansión mínima (MST) a partir de un grafo no dirigido.
 * Utiliza una cola de prioridad (`std::priority_queue`) para seleccionar iterativamente la arista de menor peso
 * sin necesidad de ordenar completamente el conjunto de aristas. Además, emplea una versión optimizada de la operación `find`.
 *
 * @param G Grafo de entrada, que contiene un conjunto de nodos (`G.V`) y aristas (`G.E`).
 * @return Un vector con las aristas que conforman el árbol de expansión mínima del grafo.
 */
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
