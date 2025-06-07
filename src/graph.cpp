// Definición de un grafo
#include <vector>
#include <random>
#include <iostream>
#include <cmath> // contiene pow



// Cada nodo es un par ordenado de enteros de 64 bits
class Nodo {
public:
    int64_t x;
    int64_t y;

    // Constructor: asigna los valores de (x,y) al nodo
    Nodo(int64_t x_val, int64_t y_val) : x(x_val), y(y_val) {} 

    // Constructor: si no se le dan los valores (x,y) crea valores aleatorios
    Nodo() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int64_t> dist(-5000000, 5000000);

        x = dist(gen);
        y = dist(gen);
    }
};


// Aristas con peso
class Arista {
public:

    const Nodo* n1; // puntero al nodo
    const Nodo* n2; // puntero al nodo
    int64_t peso;  // cuadrado de la distancia euclidiana

    // Constructor: calcula el peso de una arista al ser creada
    Arista(Nodo* nodo1, Nodo* nodo2) : n1(nodo1), n2(nodo2)
    { 
        peso = std::pow((nodo1->x - nodo2->x), 2) + std::pow((nodo1->y - nodo2->y), 2);
    }
};


// La idea es pasarle una lista de nodos y el grafo crea las N*(N-1)/2 aristas posibles entre ellos
class Graph{
public:
    // Parámetros de un grafo
    std::vector<Nodo> V; // lista de nodos
    std::vector<Arista> E; // lista de aristas

    Graph(std::vector<Nodo> Vertices): V(Vertices) { 
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
                Arista a(&V[i], &V[j]);
                E.push_back(a);
            }
        }
    }

    /*
        Este método imprime todos los nodos creados y las aristas creadas con sus respectivos pesos
        Ejemplo de uso:
            std::vector<Nodo> nodos1 = { Nodo(1, 2), Nodo(4, 6), Nodo(-3, 7) };
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
            std::cout << "  Nodo " << i << ": (" << V[i].x << ", " << V[i].y << ")" << std::endl;
        }
    
        std::cout << "\nAristas:" << std::endl;
        for (const Arista& a : E) {
            int idx1 = -1, idx2 = -1;
            for (size_t i = 0; i < V.size(); ++i) {
                if (&V[i] == a.n1) idx1 = i;
                if (&V[i] == a.n2) idx2 = i;
            }
    
            std::cout << "  (" << idx1 << ", " << idx2 << ")  peso: " << a.peso << std::endl;
        }
    }
};


