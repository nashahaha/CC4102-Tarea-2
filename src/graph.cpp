#include <vector>
#include <random>
#include <iostream>
#include <cmath> // contiene pow


/**
 * @class Node
 * @brief Representa un nodo
 *
 * La clase Node representa un nodo como un par ordenado de reales de 64 bits (x, y).
 * Se puede crear el nodo con valores definidos o asignarlos aleatoriamente en el rango [0, 1].
 */
class Node {
public:
    int id; // Lo asigna el grafo, se usa en UnionFind
    double x;
    double y;
    
    /**
     * @brief Constructor con valores definidos.
     * 
     * Crea un nodo con coordenadas (x_val, y_val).
     * 
     * @param x_val Valor de la coordenada X.
     * @param y_val Valor de la coordenada Y.
     */
    Node(double x_val, double y_val) : x(x_val), y(y_val) {} 

    /**
     * @brief Constructor por defecto.
     * 
     * Crea un nodo con coordenadas aleatorias en el rango [0, 1].
     */
    Node() {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        x = dist(gen);
        y = dist(gen);
    }
};


/**
 * @class Edge
 * @brief Representa una arista con peso entre dos nodos.
 *
 * La clase Edge modela una arista entre dos nodos
 * El peso de la arista es el cuadrado de la distancia euclidiana entre los dos nodos.
 */
class Edge {
public:
    const Node* n1; // puntero al nodo
    const Node* n2; // puntero al nodo
    double peso;   // cuadrado de la distancia euclidiana

    /**
     * @brief Constructor de la clase Edge.
     *
     * Crea una arista entre dos nodos y calcula automáticamente su peso.
     *
     * @param nodo1 Puntero al primer nodo.
     * @param nodo2 Puntero al segundo nodo.
     */
    Edge(Node* nodo1, Node* nodo2) : n1(nodo1), n2(nodo2){ 
        peso = std::pow((nodo1->x - nodo2->x), 2) + std::pow((nodo1->y - nodo2->y), 2);
    }
};


/**
 * @class Graph
 * @brief Representa un grafo completo no dirigido con aristas ponderadas.
 *
 * Dado un conjunto de nodos la clase Graph permite crear todas las aristas posibles entre ellos.
 * También proporciona una función para imprimir la estructura del grafo.
 */
class Graph{
public:
    std::vector<Node> V; // Lista de nodos
    std::vector<Edge> E; // Lista de aristas

    /**
     * @brief Constructor del grafo.
     *
     * Inicializa el grafo con una lista de nodos, asignando un identificador único a cada uno.
     * Crea las N(N-1)/2 aristas posibles entre los nodos existentes.
     * No se crean self-loops.
     *
     * @param Vertices Vector de nodos que compondrán el grafo.
     */
    Graph(std::vector<Node> Vertices): V(Vertices) { 
        for (int i=0; i<V.size(); i++){
            V[i].id = i; // Asigna un id a cada nodo
            
            for(int j=i+1; j<V.size(); j++){ // Crea las aristas
                Edge arista(&V[i], &V[j]);
                E.push_back(arista);
            }
        } 
    }


    /**
     * @brief Imprime los nodos y aristas del grafo.
     *
     * Muestra los nodos con sus coordenadas e identificadores, y las aristas con sus pesos.
     *
     * ### Ejemplo de uso:
     * @code
     * std::vector<Node> nodos1 = { Node(1, 2), Node(4, 6), Node(-3, 7) };
     * Graph g1(nodos1);
     * g1.print();
     * @endcode
     *
     * ### Salida esperada:
     * @verbatim
     * Nodos:
     *   Nodo 0:(1, 2)  Nodo 1:(4, 6)  Nodo 2:(-3, 7)
     *
     * Aristas:
     *   (0, 1)  peso: 25
     *   (0, 2)  peso: 41
     *   (1, 2)  peso: 50
     * @endverbatim
     */
    
    void print() const {
        std::cout << "\nNodos:" << std::endl;
        for (size_t i = 0; i < V.size(); ++i) {
            std::cout << "  Nodo " << V[i].id << ":(" << V[i].x << ", " << V[i].y << "), ";
        }
    
        std::cout << "\nAristas:" << std::endl;
        for (const Edge& a : E) {
            std::cout << "  (" << a.n1->id << ", " << a.n2->id << ")  peso: " << a.peso << std::endl;
        }
    }
};


