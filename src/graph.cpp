// Definición de un grafo
#include <vector>
#include <random>
#include <iostream>
#include <cmath> // contiene pow


// Cada nodo es un par ordenado de enteros de 64 bits
class Node {
public:
    int64_t x;
    int64_t y;
    int id; // Lo asigna el grafo, se usa en UnionFind

    // Constructor: asigna los valores de (x,y) al nodo
    Node(int64_t x_val, int64_t y_val) : x(x_val), y(y_val) {} 

    // Constructor: si no se le dan los valores (x,y) crea valores aleatorios
    Node() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int64_t> dist(-5000, 5000);

        x = dist(gen);
        y = dist(gen);
    }
};


// Aristas con peso
class Edge {
public:

    const Node* n1; // puntero al nodo
    const Node* n2; // puntero al nodo
    int64_t peso;  // cuadrado de la distancia euclidiana

    // Constructor: calcula el peso de una arista al ser creada
    Edge(Node* nodo1, Node* nodo2) : n1(nodo1), n2(nodo2)
    { 
        peso = std::pow((nodo1->x - nodo2->x), 2) + std::pow((nodo1->y - nodo2->y), 2);
    }
};


// La idea es pasarle una lista de nodos y el grafo crea las N*(N-1)/2 aristas posibles entre ellos
class Graph{
public:
    // Parámetros de un grafo
    std::vector<Node> V; // lista de nodos
    std::vector<Edge> E; // lista de aristas

    Graph(std::vector<Node> Vertices): V(Vertices) { 
        for (int i=0; i<V.size(); i++) V[i].id = i; // Asigna un id a cada nodo
    }

    /**
     * Agrega una nueva arista al grafo.
     * 
     * IMPORTANTE: Para agregar aristas se debe dar la dirección al nodo en la lista de nodos de grafo. Por ningún motivo crear nodos nuevos.
     * Ejemplo: 
     *      std::vector<Node> nodos1 = { Node(1, 2), Node(4, 6), Node(-3, 7), Node(1,1), Node(2,3), Node(0,4) };
     *      Graph g1(nodos1);
     *      g1.addEdge(&g1.V[0], &g1.V[1]);
     */

    void addEdge(Node* n1, Node* n2){
        Edge a(n1, n2);
        E.push_back(a);
    }

    /**
     * Este método crea todas la aristas posibles para los nodos que tenga el grafo.
     * Si el grafo ya tenía aristas agregadas se vaciarán antes.
     */
    void addAllEdges(){
        E.clear();
        // Se asume que no hay self loops
        for (int i=0; i<V.size(); i++){
            for(int j=i+1; j<V.size(); j++){
                Edge a(&V[i], &V[j]);
                E.push_back(a);
            }
        }
    }

    /**
     * Este método imprime todos los nodos creados y las aristas creadas con sus respectivos pesos
        Ejemplo de uso:
            std::vector<Node> nodos1 = { Node(1, 2), Node(4, 6), Node(-3, 7) };
            Graph g1(nodos1);
            g1.addAllEdges();
            g1.print();
            
        Devuelve:
            Nodos:
                Nodo 0: (1, 2)
                Nodo 1: (4, 6)
                Nodo 2: (-3, 7)

            Aristas:
                (0, 1)  peso: 25
                (0, 2)  peso: 41
                (1, 2)  peso: 50
     */
    
    void print() const {
        std::cout << "\nNodos:" << std::endl;
        for (size_t i = 0; i < V.size(); ++i) {
            std::cout << "  Nodo " << V[i].id << ": (" << V[i].x << ", " << V[i].y << ")" << std::endl;
        }
    
        std::cout << "\nAristas:" << std::endl;
        for (const Edge& a : E) {
            std::cout << "  (" << a.n1->id << ", " << a.n2->id << ")  peso: " << a.peso << std::endl;
        }
    }
};

class UnionFind {
    std::vector<int> padre; // Arreglo que marca quien es el padre de cada nodo
    std::vector<int> rango; // Rango de cada nodo
public:
    UnionFind(int n): padre(n), rango(n, 1){
        for(int i=0; i<n; i++) padre[i] = i; // Cada nodo parte siendo su propio padre
    }

    int find(int x){
        if(padre[x] != x) padre[x] = find(padre[x]);
        return padre[x];
    }

    bool union_(int x, int y){
        int raiz_x = find(x);
        int raiz_y = find(y);
        if (raiz_x == raiz_y) return false;

        
        if ( rango[raiz_x]< rango[raiz_y]) std::swap(raiz_x, raiz_y); 

        padre[raiz_y] = raiz_x;
        
        rango[raiz_x]+= rango[raiz_y];
        
        return true;
    }
};
