#include "graph.cpp"

//Funciones auxiliares

/**
 * @brief Imprime las aristas de un grafo
 * 
 * Imprime las aristas de una lista con el formato de una lista de python.
 *
 * @param edgesList Lista de aristas por imprimir
 */
void printEdges(std::vector<Edge> edgesList){
    std::cout << "edges = [";
    for(size_t i = 0; i < edgesList.size(); ++i){
        Edge E = edgesList[i];
        std::cout << "(" << E.n1->id << "," << E.n2->id << "," << E.peso << ")";
        if (i < edgesList.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

/**
 * @brief Imprime los nodos de un grafo
 * 
 * Imprime los nodos de una lista con el formato de una lista de python.
 * 
 * Si se le entrega el parametro i se concatena al nombre de la variable.
 *
 * @param nodes Lista de nodos por imprimir
 * @param i Nombre de la variable por imprimir
 */
void printNodes(std::vector<Node> nodes, int i=-1) {
    if (i != -1)
        std::cout << "nodes" << i << " = [";
    else
        std::cout << "nodes = [";
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << "(" << nodes[i].x << "," << nodes[i].y << ")";
        if (i < nodes.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Comparador para ordenar aristas por peso en orden ascendente.
 *
 * Esta función se utiliza para ordenar un conjunto de aristas en orden creciente
 * según su atributo `peso`. Se utiliza para ordenar arsitas en el algoritmo de Kruskal.
 *
 * @param a1 Primera arista a comparar.
 * @param a2 Segunda arista a comparar.
 * @return true si `a1` tiene menor peso que `a2`, false en caso contrario.
 */
bool sortByWeight(Edge a1, Edge a2){
    return a1.peso<a2.peso;
}

/**
 * @brief Comparador para ordenar aristas por peso en orden descendente.
 *
 * Esta función permite ordenar aristas de mayor a menor peso, lo cual es útil
 * cuando se utiliza una estructura como un heap.
 *
 * @param a1 Primera arista a comparar.
 * @param a2 Segunda arista a comparar.
 * @return true si `a1` tiene mayor peso que `a2`, false en caso contrario.
 */
bool sortByWeightHeap(Edge a1, Edge a2){
    return a1.peso>a2.peso;
}

/**
 * @brief Verifica si cuatro conjuntos de aristas tienen el mismo peso total.
 *
 * Esta función compara la suma de los pesos de las aristas contenidas en
 * cuatro vectores distintos. Retorna `true` si el peso total de los cuatro
 * conjuntos es idéntico.
 *
 * @param A Primer conjunto de aristas.
 * @param B Segundo conjunto de aristas.
 * @param C Tercer conjunto de aristas.
 * @param D Cuarto conjunto de aristas.
 * @return true si todos los conjuntos tienen el mismo peso total, false en caso contrario.
 */
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

